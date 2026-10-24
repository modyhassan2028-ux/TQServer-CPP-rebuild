#include "MsgMagicEffect.h"
#include <cstring>
#include <cstdio>
#include "Log.h"

// Payload layout (all offsets relative to the payload start, i.e. after the
// 4-byte tq::MsgHead - the ORIGINAL this+0x428 buffer):
//   +0x00 attacker id (u32)      param_2
//   +0x04 target id  (u32)       param_6 / 800-variant
//   +0x08 magic type (u16)       param_3
//   +0x0a level      (u16)       param_4
//   +0x0e direction  (u8)        param_5
//   +0x0f target count (u8)      starts 0
//   +0x10 extra flag (u8)        param_7 / param_13
//   +0x14 first target entry (0x20 stride)
CMsgMagicEffect::CMsgMagicEffect() = default;

static const char* szEffectErr = "Create MagicEffect packet failed."; // ORIGINAL DAT_1406d9c10

bool CMsgMagicEffect::Create(uint32_t dwAttacker, uint32_t dwTarget, uint16_t usType,
                             uint16_t usLevel, uint8_t byDir, uint8_t byFlag) {
    // ORIGINAL: (attacker == 0 || target == 0) -> log + 0
    if (dwAttacker == 0 || dwTarget == 0) {
        tq::MyLogSave("gmlog/all", "%s", szEffectErr);
        return false;
    }
    m_dwSizeField = BASE_SIZE;
    m_byCount = 0;
    // the ORIGINAL writes the payload buffer directly; the 4-byte tq head
    // is emitted by the base class at send time.
    m_buffer.assign(BASE_SIZE, 0);
    auto w32 = [&](uint32_t off, uint32_t v) { std::memcpy(m_buffer.data() + off, &v, 4); };
    auto w16 = [&](uint32_t off, uint16_t v) { std::memcpy(m_buffer.data() + off, &v, 2); };
    auto w8  = [&](uint32_t off, uint8_t v)  { m_buffer.data()[off] = (char)v; };
    w32(0x00, dwAttacker);
    w32(0x04, dwTarget);
    w16(0x08, usType);
    w16(0x0a, usLevel);
    w8 (0x0e, byDir);
    w8 (0x0f, 0);      // ORIGINAL: count starts 0
    w8 (0x10, byFlag);
    m_nType = OPCODE;
    m_nSize = (uint16_t)m_dwSizeField;
    return true;
}

bool CMsgMagicEffect::CreateWithTarget(uint32_t dwAttacker, uint32_t dwTarget, uint16_t usType,
                                       uint16_t usLevel, uint8_t byDir, uint32_t dwDamage,
                                       uint32_t dwData2, uint32_t dwData6, uint8_t byFlag) {
    // ORIGINAL FUN_1403868f0: target==0 -> fall into the error log branch
    if (dwTarget == 0) {
        tq::MyLogSave("gmlog/all", "%s", szEffectErr);
        return false;
    }
    if (!Create(dwAttacker, dwTarget, usType, usLevel, byDir, byFlag))
        return false;
    // ORIGINAL: size += 0x20; entry0 at payload + 0x14
    m_dwSizeField += TARGET_STRIDE;
    m_buffer.resize(m_dwSizeField, 0);
    auto w32 = [&](uint32_t off, uint32_t v) { std::memcpy(m_buffer.data() + off, &v, 4); };
    w32(0x14 + 0x00, dwTarget);   // entry +0: id (param_6)
    w32(0x14 + 0x04, dwDamage);   // entry +4 (param_7)
    w32(0x14 + 0x08, dwData2);    // entry +8 (param_8)
    w32(0x14 + 0x1c, dwData6);    // entry +0x1c = 0x30 (param_9)
    w32(0x14 + TARGET_STRIDE, 0); // ORIGINAL: terminator 0 at the next entry
    m_buffer.data()[0x0f] = 1;    // count++
    m_nSize = (uint16_t)m_dwSizeField;
    return true;
}

bool CMsgMagicEffect::AppendTarget(uint32_t dwId, uint32_t dwDamage,
                                   uint32_t dwData2, uint32_t dwData6) {
    // ORIGINAL FUN_140386d00: id == 0 -> log; size + 0x20 < 0x400 gate
    if (dwId == 0) {
        tq::MyLogSave("gmlog/all", "%s", szEffectErr);
        return false;
    }
    if (m_dwSizeField + TARGET_STRIDE >= MAX_SIZE) return false; // ORIGINAL gate
    uint32_t base = 0x14 + (uint32_t)m_byCount * TARGET_STRIDE;
    m_dwSizeField += TARGET_STRIDE;
    m_buffer.resize(m_dwSizeField, 0);
    auto w32 = [&](uint32_t off, uint32_t v) { std::memcpy(m_buffer.data() + off, &v, 4); };
    w32(base + 0x00, dwId);
    w32(base + 0x04, dwDamage);
    w32(base + 0x08, dwData2);
    w32(base + 0x1c, dwData6);
    w32(base + TARGET_STRIDE, 0); // terminator
    m_byCount++;
    m_buffer.data()[0x0f] = (char)m_byCount;
    m_nSize = (uint16_t)m_dwSizeField;
    return true;
}

bool CMsgMagicEffect::CreateFull(uint32_t dwAttacker, uint32_t dwTarget, uint16_t usType,
                                 uint16_t usLevel, uint8_t byDir, uint32_t dwDamage,
                                 uint32_t dwData2, uint32_t dwData3, uint32_t dwData4,
                                 uint32_t dwData5, uint32_t dwData6, uint8_t byFlag) {
    // ORIGINAL FUN_140386e00: zero attacker/target -> log + 0
    if (dwAttacker == 0 || dwTarget == 0) {
        tq::MyLogSave("gmlog/all", "%s", szEffectErr);
        return false;
    }
    if (!Create(dwAttacker, dwTarget, usType, usLevel, byDir, byFlag))
        return false;
    m_dwSizeField += TARGET_STRIDE;
    m_buffer.resize(m_dwSizeField, 0);
    auto w32 = [&](uint32_t off, uint32_t v) { std::memcpy(m_buffer.data() + off, &v, 4); };
    w32(0x14 + 0x00, dwTarget);   // entry +0 (param_6: id)
    w32(0x14 + 0x04, dwDamage);   // entry +4 (param_7: dmg)
    w32(0x14 + 0x08, dwData2);    // entry +8 (param_8)
    w32(0x14 + TARGET_STRIDE, dwData3); // ORIGINAL QUIRK: param_9 lands at the
                                        // NEXT entry base (literal 140386e00)
    w32(0x14 + 0x10, dwData4);    // +0x24 (param_10)
    w32(0x14 + 0x1c, dwData5);    // +0x30 (param_11)
    w32(0x14 + 0x18, dwData6);    // +0x2c (param_12)
    m_buffer.data()[0x0f] = 1;
    m_nSize = (uint16_t)m_dwSizeField;
    return true;
}

void CMsgMagicEffect::Process(uint32_t) {
    // ORIGINAL CMsgMagicEffect is server->client only; the receive path
    // logs "invalid msg CMsgMagicEffect." and drops it (FUN_1403872c0,
    // vtable slot 3).
    tq::MyLogSave("gmlog/all", "invalid msg CMsgMagicEffect.");
}
