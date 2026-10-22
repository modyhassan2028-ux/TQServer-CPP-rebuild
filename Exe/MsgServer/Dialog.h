#pragma once
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class CMySQLClient;

// cq_action-style dialog tree engine (original 6159 structure):
// each row = one node; option rows reference their parent node id.
//  parent_id=0 with id=npc.action_id => the NPC's greeting node.
class CDialogEngine {
public:
    struct Node {
        uint32_t dwId{0};
        uint32_t dwParent{0};
        uint32_t dwNext{0};      // node shown after this option is chosen
        uint32_t dwType{0};      // 1=say, 2=accept task, 3=turn-in task, 4=teleport, 0=plain option
        std::string strParam;    // "task_id" or "map,x,y"
        std::string strText;
    };
    struct Option {
        uint32_t dwTargetNode{0}; // option's own node id (its dwNext says what to show)
        std::string strText;
    };

    static CDialogEngine& Instance();

    // loads cq_action + cq_task from MySQL; returns node count (0 = no data)
    uint32_t LoadFromDB(CMySQLClient* pDB);

    bool HasNode(uint32_t dwId) const { return m_nodes.count(dwId) != 0; }
    const Node* GetNode(uint32_t dwId) const;
    // numbered options in insertion order for a node
    std::vector<Option> GetOptions(uint32_t dwNodeId) const;
    const std::map<uint32_t, Node>& GetNodes() const { return m_nodes; }
    bool IsLoaded() const { return !m_nodes.empty(); }

private:
    CDialogEngine() = default;
    std::map<uint32_t, Node> m_nodes;
};

// cq_task-style task definition mirrored from the DB (same shape as data/tasks.ini)
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
