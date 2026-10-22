#!/usr/bin/env python3
"""Generate faithful module skeletons from the decompiled original DLLs.

For each <System>.dll.decompiled.c we extract, verbatim:
  - the <ns>::CModule class name from ModuleCreate / ctor vftable writes
  - the CModule allocation size (field layout hint)
  - the init function's kernel calls: RegisterProcess(msgId, module) list
    (decompiled as kernel->vt+8 / vt+0x10 calls) and SetProcess(mode)
    (kernel->vt+0x18 call)
and emit Modules/<Folder>/<Name>.{h,cpp} that compile as the real DLL with the
original ABI (extern "C" ModuleCreate(kernel, index, r1, r2)).

Run from the repo root:  python3 tools/modules/gen_module_skeletons.py
"""
import re, os, sys, json

DEC = "../conquer-online-v6159-decompiled/Native-Decompiled"

# folder -> (dll, key, description, db tables)
SYSTEMS = {
    "AntiCheat":       ("AntiCheat.dll",       "anticheat", "Speed/fly/attack-rate cheat detection and kicks", "-"),
    "Arena/Arenic":    ("Arenic.dll",          "arenic",    "Solo PK arena: signup, honor, bonus", "cq_arenic, cq_arenic_bonus, cq_arenic_honor"),
    "Arena/TeamArenic": ("TeamArenic.dll",     "team_arenic", "Team PK arena battles", "cq_arenic*"),
    "Arena/ClanPKArenic": ("ClanPKArenic.dll", "clan_pk_arenic", "Clan (guild) PK arena", "cq_arenic*"),
    "Arena/ElitePKArenic": ("ElitePKArenic.dll","elite_pk_arenic", "Elite PK tournament arena", "cq_arenic*"),
    "Arena/FamilyArenic": ("FamilyArenic.dll", "family_arenic", "Family PK arena", "cq_arenic*"),
    "Arena/PopPKArenic": ("PopPKArenic.dll",   "pop_pk_arenic", "Popular PK arena (open signup)", "cq_arenic*"),
    "Arena/CrossFlagWar": ("CrossFlagWar.dll", "cross_flag_war", "Cross-server flag war event", "cq_flag_war, cq_flag_war_user"),
    "Arena/FrontierFlagWar": ("FrontierFlagWar.dll","frontier_flag_war", "Frontier (border) flag war", "cq_flag_war*"),
    "Arena/VexillumArenic": ("VexillumArenic.dll","vexillum_arenic", "Vexillum (cross-server banner) war arena", "cq_cross_vexillum"),
    "Booth":           ("Booth.dll",           "booth",     "Player market stalls (booth selling)", "-"),
    "Competion":       ("Competion.dll",        "competion", "Weekly competition ranking rewards", "cq_syncompeterank, cq_competesponsor"),
    "CrossStatus":     ("CrossStatus.dll",      "cross_status", "Cross-server status/buff sync channel", "cq_cross_merit"),
    "DetainEquip":     ("DetainEquip.dll",      "detain_equip", "Detained equipment (jail item holding)", "cq_itemstatus, cq_itemstatus_timeout"),
    "FactionMatch":    ("FactionMatch.dll",     "faction_match", "Faction matching battles (CGameAction::ProcessActionFactionMatch)", "cq_fate_*"),
    "Family":          ("Family.dll",           "family",    "Family system (create/level/attr/battle shares)", "family, family_attr, family_battle_effect_share_limit"),
    "Flower":          ("Flower.dll",           "flower",    "Flower gifting/ranking system", "flower"),
    "Guide":           ("Guide.dll",            "guide",     "Beginner guide/wizard tracking", "-"),
    "LeaveWord":       ("LeaveWord.dll",        "leaveword", "Offline messages left for players", "cq_leaveword, cq_sys_leaveword"),
    "Lottery":         ("Lottery.dll",          "lottery",   "Lucky lottery draws (prize table)", "cq_lottery"),
    "Peerage":         ("Peerage.dll",          "peerage",   "Nobility/peerage (knight/baron donations)", "cq_user.nobility"),
    "Pigeon":          ("Pigeon.dll",           "pigeon",    "In-game mail system (carrier pigeon)", "cq_mail, cq_operating_mail_record"),
    "Rank":            ("Rank.dll",             "rank",      "Dynamic rank ladders", "cq_dyna_rank_rec, cq_dyna_rank_type, dyna_rank_rec, dyna_rank_type, cq_fate_rank"),
    "Relation":        ("Relation.dll",         "relation",  "Friends/enemies lists (add/delete/notify)", "cq_friend, cq_friend_timeout, cq_enemy, cq_enemy_timeout"),
    "Sponsor":         ("Sponsor.dll",          "sponsor",   "Event sponsorship (NPC sponsorships)", "cq_sponsor, cq_competesponsor"),
    "Status":          ("Status.dll",           "status",    "Buff/status effects (types + timeouts)", "cq_status, cq_status_timeout, cq_statustype"),
    "Storage":         ("Storage.dll",          "storage",   "Warehouse/storage boxes", "cq_depot"),
    "TaskDetail":      ("TaskDetail.dll",       "task_detail", "Quest log details/progress UI", "cq_task"),
    "Team":            ("Team.dll",             "team",      "Party/team system", "-"),
    "Title":           ("Title.dll",            "title",     "Player titles (CTitle/CTitleMgr)", "-"),
    "Totem":           ("Totem.dll",            "totem",     "Clan totem poles (attributes)", "cq_totem_add"),
    "Training":        ("Training.dll",         "training",  "Training/vitality (CTrainingVitalityMgr)", "cq_user"),
    "Wanted":          ("Wanted.dll",           "wanted",    "Bounty board (players post rewards)", "cq_wanted"),
}

def fn_body(src, name):
    m = re.search(r"// Function: %s @.*?\n// =+\n(.*?)(?=\n// Function:|\Z)" % re.escape(name), src, re.S)
    return m.group(1) if m else None

def kernel_calls(body):
    """Return (msgs, modes, mode_from_index). Faithful to decompile shapes."""
    if not body: return [], [], False
    # RegisterProcess(msgId, module): kernel->vt+8 or vt+0x10, last arg = param_1
    msgs = [int(x, 0) for x in re.findall(
        r"\+ (?:8|0x10)\)\)(?:(?!\};).)*?,\s*(0x[0-9a-f]+|\d+)\s*,\s*param_1\)", body, re.S)]
    modes = [int(x, 0) for x in re.findall(
        r"\+ 0x18\)\)(?:(?!\};).)*?\(param_1 \+ 0x[0-9a-f]+\)\s*,\s*(0x[0-9a-f]+|\d+)", body, re.S)]
    mode_from_index = bool(re.search(
        r"\+ 0x18\)\)(?:(?!\};).)*?\(param_1 \+ 0x[0-9a-f]+\),\s*\*\(undefined4 \*\)\(param_1 \+ 8\)", body, re.S))
    return msgs, modes, mode_from_index

def parse(path):
    src = open(path, encoding="utf-8", errors="replace").read()
    mc = fn_body(src, "ModuleCreate")
    if not mc: return None
    size = re.search(r"operator_new\((0x[0-9a-f]+|\d+)\)", mc)
    cls = re.search(r"(\w+)::CModule\w*::vftable", mc)
    best = None
    for f in dict.fromkeys(re.findall(r"(FUN_[0-9a-f]+)\(", mc)):
        b = fn_body(src, f)
        if not b: continue
        msgs, modes, mfi = kernel_calls(b)
        if msgs or modes or mfi:
            c2 = cls or re.search(r"(\w+)::CModule\w*::vftable", b)
            best = {"ns": (c2.group(1) if c2 else "module").split("::")[0],
                    "size": int(size.group(1), 0) if size else 0,
                    "msgs": msgs, "modes": modes, "mode_from_index": mfi}
            break
    if best is not None and (not cls):
        # vftable written in the ctor (Title shape): take the first
        # <ns>::CModule::vftable anywhere in the file
        any_cls = re.search(r"(\w+)::CModule\w*::vftable", src)
        if any_cls: best["ns"] = any_cls.group(1).split("::")[0]
    if best is None:
        # CrossStatus shape: SetProcess(mode, proc) inline in ModuleCreate,
        # kernel reached through puVar2[1] instead of a param_1 field
        inline = re.findall(r"\+ 0x18\)\)\(\(longlong \*\)puVar2\[1\],\s*(0x[0-9a-f]+|\d+)", mc)
        if inline:
            best = {"ns": (cls.group(1) if cls else "module").split("::")[0],
                    "size": int(size.group(1), 0) if size else 0,
                    "msgs": [], "modes": [int(x, 0) for x in inline], "mode_from_index": False}
    if best is None:
        # generic fallback: registration inline in ModuleCreate itself
        msgs, modes, mfi = kernel_calls(mc)
        if not (msgs or modes or mfi): return None
        best = {"ns": (cls.group(1) if cls else "module").split("::")[0],
                "size": int(size.group(1), 0) if size else 0,
                "msgs": msgs, "modes": modes, "mode_from_index": mfi}
    return best

def cxx_ident(key): return key.replace("/", "_")
def class_name(key): return "".join(p.capitalize() for p in key.replace("_", " ").split())

def emit(folder, key, dll, desc, tables, info, lines_meta):
    ns = info["ns"]; guard = key.upper().replace("/", "_") + "_H"
    cls = class_name(key) + "Module"
    reg = []
    for mid in info["msgs"]:
        reg.append(f"pKernel->RegisterProcess({mid}, pModule);")
    if info["mode_from_index"]:
        reg.append("pKernel->SetProcess(pModule->GetModuleIndex(), pModule->GetProcessor());")
    for mode in info["modes"]:
        reg.append(f"pKernel->SetProcess({mode}, pModule->GetProcessor());")
    reg_code = "\n        ".join(reg) if reg else "// (no kernel registration observed in ModuleCreate)"
    h = f"""// {cls} - {desc}
// Original: {dll} (cqserver-78.0.11-1204/modules/{key.split('/')[-1]}/src/)
// Original DB tables: {tables}
// Decompiled ABI: CModule size {hex(info['size'])}; RegisterProcess msgs: {info['msgs']}; SetProcess modes: {info['modes']}{' (module index)' if info['mode_from_index'] else ''}
#pragma once
#include "Common/IModule.h"

namespace {ns} {{

class C{cls} : public gs::IModule {{
public:
    C{cls}(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {{}}

    bool Initialize() override {{ return true; }}
    void Shutdown() override {{}}
    void OnProcess() override {{}}
    const char* GetModuleName() const override {{ return "{key.split('/')[-1]}"; }}

    gs::IWorldKernel* GetKernel() const {{ return m_pKernel; }}
    uint32_t GetModuleIndex() const {{ return m_dwModuleIndex; }}
    void* GetProcessor() {{ return &m_oProcessor; }}

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from {dll}.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{{}};
}};

}} // namespace {ns}
"""
    cpp = f"""// {cls} module implementation - faithful ABI rebuild of {dll}
// Registration sequence extracted verbatim from the decompiled ModuleCreate.
#include "{key.split('/')[-1]}.h"
#include <new>

EXPORT_MODULE_FULL({ns}::C{cls},
{reg_code})
"""
    os.makedirs(f"Modules/{folder}", exist_ok=True)
    name = key.split("/")[-1]
    open(f"Modules/{folder}/{name}.h", "w", encoding="utf-8", newline="\n").write(h)
    open(f"Modules/{folder}/{name}.cpp", "w", encoding="utf-8", newline="\n").write(cpp)
    lines_meta.append((folder, name, dll, ns, info))

def main():
    meta = []
    for folder, (dll, key, desc, tables) in SYSTEMS.items():
        p = os.path.join(DEC, dll + ".decompiled.c")
        info = parse(p) if os.path.exists(p) else None
        if info is None:
            print(f"WARN: no ABI found for {dll}", file=sys.stderr)
            info = {"ns": key.replace("/", "_"), "size": 0, "msgs": [], "modes": [], "mode_from_index": False}
        emit(folder, key, dll, desc, tables, info, meta)
    # ABI manifest for tests + docs
    json.dump([{ "folder": f, "name": n, "dll": d, "namespace": ns, **info}
               for f, n, d, ns, info in meta],
              open("tools/modules/abi.json", "w"), indent=1)
    print(f"generated {len(meta)} modules")

if __name__ == "__main__":
    main()
