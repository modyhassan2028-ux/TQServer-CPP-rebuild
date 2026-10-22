#include "Dialog.h"
#include "MySQLClient.h"
#include <cstdlib>
#include <cstdio>

CDialogEngine& CDialogEngine::Instance() {
    static CDialogEngine s_instance;
    return s_instance;
}

uint32_t CDialogEngine::LoadFromDB(CMySQLClient* pDB) {
    m_nodes.clear();
    m_taskEntry.clear();
    if (!pDB) return 0;
    // ORIGINAL cq_action schema: id, id_next, id_nextfail, type, data, param
    if (!pDB->Query("SELECT id, id_next, id_nextfail, type, data, param FROM cq_action")) {
        printf("[DIALOG] cq_action load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 6) continue;
        Node n;
        n.dwId       = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        n.dwNext     = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
        n.dwNextFail = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        n.dwType     = (uint32_t)strtoul(row[3].c_str(), nullptr, 10);
        n.dwData     = (uint32_t)strtoul(row[4].c_str(), nullptr, 10);
        n.strParam   = row[5];
        if (n.dwId) m_nodes[n.dwId] = n;
    }
    // ORIGINAL cq_task: id -> id_next (first action of the tree)
    if (pDB->Query("SELECT id, id_next FROM cq_task")) {
        for (auto& row : pDB->GetRows()) {
            if (row.size() < 2) continue;
            uint32_t id  = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
            uint32_t nxt = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
            if (id) m_taskEntry[id] = nxt ? nxt : id;
        }
    }
    printf("[DIALOG] cq_action loaded: %zu action(s), %zu task(s).\n",
           m_nodes.size(), m_taskEntry.size());
    return (uint32_t)m_nodes.size();
}

const CDialogEngine::Node* CDialogEngine::GetNode(uint32_t dwId) const {
    auto it = m_nodes.find(dwId);
    return (it != m_nodes.end()) ? &it->second : nullptr;
}

uint32_t CDialogEngine::TaskEntry(uint32_t dwTaskId) const {
    auto it = m_taskEntry.find(dwTaskId);
    return (it != m_taskEntry.end()) ? it->second : 0;
}

std::vector<CDialogEngine::Option> CDialogEngine::GetOptions(uint32_t dwFromNodeId) const {
    // ORIGINAL engine: walking the tree collects every 102 it passes;
    // conditions branch (1020 etc. continue id_next until ported fully)
    std::vector<Option> out;
    const Node* n = GetNode(dwFromNodeId);
    uint32_t guard = 0;
    while (n && ++guard < 64) {
        if (n->dwType == 102) {
            Option o;
            o.dwTargetNode = n->dwNext;
            std::string text = n->strParam;
            // original param format: "option text target_action_id"
            size_t sp = text.find_last_of(' ');
            if (sp != std::string::npos) {
                const std::string tail = text.substr(sp + 1);
                char* end = nullptr;
                unsigned long v = strtoul(tail.c_str(), &end, 10);
                if (end && *end == '\0' && v) {
                    o.dwTargetNode = (uint32_t)v;
                    text = text.substr(0, sp);
                }
            }
            o.strText = text;
            out.push_back(o);
        }
        n = GetNode(n->dwNext);
    }
    return out;
}
