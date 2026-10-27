#pragma once
#include "Msg.h"
#include <vector>

#pragma pack(push, 1)
struct AttribPair {
    uint32_t dwType;
    uint64_t qwValue;
};
#pragma pack(pop)

class CMsgUserAttrib : public tq::CMsg {
public:
    enum AttribType {
        Attrib_Life = 0,
        Attrib_MaxLife = 1,
        Attrib_Mana = 2,
        Attrib_MaxMana = 3,
        Attrib_Money = 4,
        Attrib_Exp = 5,
        Attrib_Pk = 6,
        Attrib_Profession = 7,
        Attrib_Level = 11,
        Attrib_ConquerPoints = 30,
        Attrib_Stamina = 31, // CO stamina bar (jump/fatigue gate)
    };

    CMsgUserAttrib();
    bool Create(uint32_t dwId, const std::vector<AttribPair>& attribs);
    void Process(uint32_t dwSender) override;
};