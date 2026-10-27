#pragma once
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class CMySQLClient;

// ORIGINAL 6159 cq_action chain engine (real schema, real semantics):
//   cq_action: id, id_next, id_nextfail, type, data, param
//     101  = dialog text      (param holds the text, '~' encodes space)
//     102  = menu option      (param = "text target_action_id")
//     1001 = condition        (param = "field op value"; id_next = true branch)
//   cq_task:  id -> id_next (entry action of the task tree)
//   cq_npc:   task0 -> cq_task.id
class CDialogEngine {
public:
    struct Node {
        uint32_t dwId{0};
        uint32_t dwNext{0};      // id_next: true branch / chain continue
        uint32_t dwNextFail{0};  // id_nextfail: false branch
        uint32_t dwType{0};      // original action type
        uint32_t dwData{0};      // data column
        std::string strParam;    // param column
    };
    struct Option {
        uint32_t dwTargetNode{0}; // action id run when the player picks it
        std::string strText;
    };

    static CDialogEngine& Instance();

    // loads cq_action + cq_task from MySQL; returns action count (0 = no data)
    uint32_t LoadFromDB(CMySQLClient* pDB);

    bool HasNode(uint32_t dwId) const { return m_nodes.count(dwId) != 0; }
    const Node* GetNode(uint32_t dwId) const;
    // cq_task id -> first action id of the tree (0 = unknown task)
    uint32_t TaskEntry(uint32_t dwTaskId) const;
    // options from a 102 action: follows id_next while the chain stays 102
    std::vector<Option> GetOptions(uint32_t dwOptionNodeId) const;
    bool IsLoaded() const { return !m_nodes.empty(); }
    size_t NodeCount() const { return m_nodes.size(); }

private:
    CDialogEngine() = default;
    std::map<uint32_t, Node> m_nodes;
    std::map<uint32_t, uint32_t> m_taskEntry;
};

// built-in roster task library (data/tasks.ini); DB mode uses cq_task instead
struct DbTaskDef {
    uint32_t dwId{0};
    std::string strName;
    uint32_t dwNpcId{0};
    uint32_t dwMonsterType{0};
    uint32_t dwCount{0};
    uint32_t dwMoney{0};
    uint32_t dwCp{0};
    uint32_t dwMinLevel{1};
};
