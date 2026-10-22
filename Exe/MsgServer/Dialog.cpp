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
    if (!pDB) return 0;
    if (!pDB->Query("SELECT id, parent_id, id_next, type, param, text FROM cq_action")) {
        printf("[DIALOG] cq_action load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 6) continue;
        Node n;
        n.dwId      = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        n.dwParent  = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
        n.dwNext    = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        n.dwType    = (uint32_t)strtoul(row[3].c_str(), nullptr, 10);
        n.strParam  = row[4];
        n.strText   = row[5];
        if (n.dwId) m_nodes[n.dwId] = n;
    }
    printf("[DIALOG] cq_action loaded: %zu node(s).\n", m_nodes.size());
    return (uint32_t)m_nodes.size();
}

const CDialogEngine::Node* CDialogEngine::GetNode(uint32_t dwId) const {
    auto it = m_nodes.find(dwId);
    return (it != m_nodes.end()) ? &it->second : nullptr;
}

std::vector<CDialogEngine::Option> CDialogEngine::GetOptions(uint32_t dwNodeId) const {
    std::vector<Option> out;
    for (auto& kv : m_nodes) {
        if (kv.second.dwParent == dwNodeId) {
            Option o;
            o.dwTargetNode = kv.first;
            o.strText = kv.second.strText;
            out.push_back(o);
        }
    }
    return out;
}
