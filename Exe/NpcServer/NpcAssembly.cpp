#include "NpcAssembly.h"
#include <cstdio>
#include <cstring>

namespace npc {

// ===== Boot: the CSocketKernel::Create order =====
bool CNpcServerApp::Boot() {
    if (!m_fnTime) return false;
    m_idSource.m_pAllocator = &m_idAlloc;
    m_idAlloc.m_dwCounter = 0x61a81;    // TBD boot value

    // libevent base init: "libevent method: %s"
    // (FUN_010d80 = event_get_method on the +0x58 base)
    char buf[0x200];
    std::snprintf(buf, sizeof buf, "libevent method: %s",
                  m_strEventMethod.c_str());
    Console(buf);

    // CNpcWorld::Create: operator_new(0x838) + ctor
    // FUN_140001210; socket = FUN_140001ba0; the literal
    // failure log of the ORIGINAL:
    if (!m_bSocketOk) {
        Console("CNpcWorld::Create, cannot create NpcServer "
                 "client socket.");
        return false;
    }
    // libevent worker thread FUN_1400024f0 +
    // "thread %u created libevent worker thread %u"
    // (GetThreadId / GetCurrentThreadId seams)
    std::snprintf(buf, sizeof buf,
                  "thread %u created libevent worker thread %u",
                  1u, 2u);
    Console(buf);
    // CThreadBase::CreateThread(..., "NPC Server
    // KernelThread", ...) - the KernelTick loop below is
    // that thread body (1 Hz timer seam).

    // ---- world wiring (seams = ORIGINAL callees) ----
    m_world.m_fnTime = m_fnTime;              // tq::TimeGet
    m_world.m_fnPrint = [this](const char* sz){
        Console(sz); };                        // +0x10 sink
    m_world.m_fnAuth = [this](uint32_t dwKey,
                              const char*, const char*){
        // FUN_140048da0 license check (seam: accepted)
        return true; };
    m_world.m_fnConnect = [this](int, void*){
        // FUN_14001c5f0: start the connection; the
        // MsgServer login reply arrives over the socket
        // (seam) -> FUN_14001c700 OnConnectOK
        if (m_fnServerReply) m_fnServerReply();
        else m_world.OnConnectOK(); };
    m_world.m_fnTick = [this]{ WorldTick(); }; // family
    m_world.m_fnGenStats = [this]{ return GenStats(); };

    // ---- manager wiring ----
    m_mgr.m_fnLog = [this](const char* szName,
                           const char* szFile){
        char b[0x100];
        std::snprintf(b, sizeof b, "CHECKF in %s, %s", szName,
                      szFile);
        Console(b); };
    // FUN_140028820 / FUN_140057cf0: skip guards (seam:
    // fresh in-game monsters pass both)
    m_mgr.m_fnGuardA = [](NpcObj*){ return false; };
    m_mgr.m_fnGuardB = [](NpcObj*){ return false; };
    return true;
}

// ===== "NPC Server KernelThread" body =====
void CNpcServerApp::KernelTick() {
    m_world.OnTimer();            // FUN_14001d390
}

// ===== the state-2 tick family =====
// ORIGINAL order (FUN_14001d390 case 2): FUN_14003c520,
// FUN_140037f80 (+0x38 walk), FUN_14002b380 (+0x30 walk =
// CNpcManager::ProcessGenerators, ported), FUN_14001d230,
// FUN_1400489b0. Only the +0x30 walk is ported so far;
// the others are TBD seams.
void CNpcServerApp::WorldTick() {
    m_mgr.ProcessGenerators();    // FUN_14002b380
}

// ===== the generator spawn loop-back =====
// The real cadence is CNpcGenerator::Generator
// (FUN_14005fc90, unit 12). Its FUN_14001c5f0 send is
// the socket loop-back seam: the built CMsgAiNpcInfo
// arrives as a message and runs the unit-9 Process path
// (find / new / CNpc::Create / register). The generator
// needs the record its Generator() built, so the send
// seam captures it per spawn.

// ===== LiveNpc seam wiring (all seams = ORIGINAL
// callees; in-memory kernel objects stand in for the
// FUN_14001c7a0/14001c790 singletons) =====
void CNpcServerApp::WireNpc(LiveNpc* p) {
    // ---- unit 10: CNpcObject::Create seams ----
    p->obj.m_fnFindType = [this](uint32_t dwType){
        return dwType != 0 ? &m_typeRec
                           : (NpcTypeRecord*)nullptr; };
    p->obj.m_fnRecVal = [](NpcTypeRecord*, uint32_t idx){
        return idx == 4 ? 400u : idx == 5 ? 500u
            : idx == 0x12 ? 1000u : 0u; };
    p->obj.m_fnTimeGet = m_fnTime;
    p->obj.m_fnFindMap = [this](uint32_t dwId){
        auto it = m_mapMaps.find(dwId);
        return it != m_mapMaps.end() ? it->second
                                     : nullptr; };
    p->obj.m_fnNameLookup = [](const void*&,
                               void** ref,
                               uint8_t const* pr[2]){
        *ref = nullptr; pr[0] = nullptr; pr[1] = nullptr; };
    p->obj.m_fnNameInit = [](CNpcObject*, const void*,
                            uint64_t){};
    p->obj.m_fnNameRelease = [](void*){};
    p->obj.m_fnRecVt18 = [](NpcTypeRecord*){};
    p->obj.m_fnMapEnter = [](void*){};
    p->obj.m_fnNpcGetX = [](CNpcObject* o){
        return o->At<int32_t>(0x34); };
    p->obj.m_fnNpcGetY = [](CNpcObject* o){
        return o->At<int32_t>(0x38); };
    p->obj.m_fnMapPosFree = [](void*, int, int){
        return true; };
    p->obj.m_fnCreateGenerator = [](uint32_t, uint32_t, int,
                                   int, int, int){
        return (void*)nullptr; };
    p->obj.m_fnReportGenFail = [](int, int, int){
        return 0ULL; };
    p->obj.m_fnFindGenerator = [this](int nId){
        auto it = m_mapGens.find(nId);
        return it != m_mapGens.end() ? it->second
                                     : nullptr; };
    p->obj.m_fnCheckId = [](uint32_t){ return true; };
    p->obj.m_fnNpcVt8 = [](CNpcObject* o){
        return (uint64_t)o->At<uint32_t>(0x80); };
    p->obj.m_fnGenVt90 = [](void*, uint64_t){};
    p->obj.m_fnGlobalRegister = [](){};
    p->obj.m_fnNpcPostCreate = [](CNpcObject*, int){
        return 0ULL; };

    // ---- unit 8: the transform pair ----
    p->tr.m_fnTimeGet = m_fnTime;
    p->tr.m_fnReady50 = []{ return true; };
    // gates closed by default (m_pA0 null), so the tick
    // takes the dispatch branch - faithful to a fresh
    // non-transform monster
    // ---- unit 7: the +0xe0 tick ----
    p->tick.m_fnTimeGet = m_fnTime;
    p->tick.m_pProcessor = (void*)p;   // +0xb0 obj
    // arrival: FUN_140086430 transfers the accepted
    // chain into the +0x68 step list (the wander queue is
    // the accepted path - assembly glue)
    p->wand.m_fnArrive = [p]{
        ++p->nArrivals;
        StepNode* pPrev = nullptr;
        StepNode* pHead = nullptr;
        for (const WanderStep& w : p->wand.m_vecQueue) {
            auto* pn = new StepNode();
            pn->m_nData = w.nX;
            if (pPrev) pPrev->m_pNext = pn;
            else pHead = pn;
            pPrev = pn;
        }
        if (pHead) {
            p->steps.m_fnLock = []{};
            p->steps.m_fnUnlock = []{};
            p->steps.AppendChain(pHead);
        }
    };
    p->tick.m_fnDispatch = [p](void*){
        // vcall+0x20: movement dispatch -> FUN_140087d50
        ++p->nWanderSteps;
        p->wand.Step(&p->anchor);
    };
    p->tick.BindTransform(&p->tr);
    // ---- unit 4: the wander probe ----
    p->wand.m_fnWalkable = [](int, int){ return true; };
    p->wand.m_fnCellFree = [](int, int){ return true; };
    p->wand.m_fnDist = [](int dx, int dy){
        return dx > dy ? dx : dy; };   // chebyshev seam
    p->wand.m_fnOccupied = [](int, int){ return false; };
    p->wand.m_fnSetOccupied = [](int, int){};
    // ---- manager registration: vtable +0xe0 = Tick ----
    p->mgrNpc.m_fnAITick = [p]{
        ++p->nAICalls;
        p->tick.Tick(); };
}

// ===== FUN_14002b270 (CNpcManager::SpawnNewNpcID) =====
uint32_t CNpcServerApp::NextNpcId() {
    return m_idSource.SpawnNewNpcID_External();
}

// ===== the +0x30 stats walk for the OnTimer display =====
std::vector<GenStat> CNpcServerApp::GenStats() {
    std::vector<GenStat> v;
    for (uint32_t i = 0; i < m_vecGens.size(); ++i) {
        GenStat g;
        // vcall+0x30: in-game count (+0x20)
        g.nCur = (uint32_t)m_vecGens[i]->m_nMonsters20;
        // vcall+0x48: the 0xf cap (0 = unlimited mode)
        g.nAct = m_vecGens[i]->m_dwFieldF;
        // vcall+0x20 slot
        g.nLim = (uint32_t)m_vecGens[i]->m_nMonsters20;
        v.push_back(g);
    }
    return v;
}

// ===== generator registration =====
// The ORIGINAL boot path (FUN_140032800) loads the
// cq_generator rows, calls CNpcGenerator::CreateNpc once
// per row and registers the object in the generator set.
// The assembly mirrors that: CreateNpc once here, the
// cap lives in +0x14 (the ORIGINAL writer of +0x14 is
// not in FUN_140061040 - likely the +0x38 world walk),
// and the per-tick cadence is the real FUN_14005fc90
// (unit 12) wired to the real CMsgAiNpcInfo path.
void CNpcServerApp::AddGenerator(uint32_t dwMap,
                                 uint32_t dwType,
                                 uint32_t dwCap) {
    auto p = std::make_unique<CNpcGenerator>();
    // +0x50 = the generator's own id (vtable+8 /
    // rec+0x08 / the findGenerator key), +0x54 = the
    // map id (the map-object lookup key in CreateNpc)
    uint32_t dwGenIdNext = m_dwNextGenId;
    p->m_fnCurrentGenId = [dwGenIdNext]{ return dwGenIdNext; };
    p->m_fnRandomGenId = [dwGenIdNext]{ return dwGenIdNext; };
    p->m_fnFindMap = [this](uint32_t dwId){
        auto it = m_mapMaps.find(dwId);
        return it != m_mapMaps.end() ? it->second
                                     : nullptr; };
    p->m_fnRand = [](int n){ return n > 0 ? n / 2 : 0; };
    p->m_fnTime = m_fnTime;
    p->m_fnLog = [this](const char* sz){ Console(sz); };
    // GenConfig GetInt seam (ORIGINAL indices of
    // FUN_140061040 / FUN_14005fc90): 1 type, 9 the
    // record type word, 0xf cap (0 = the unlimited
    // spawner mode FUN_14005fc90 runs in), 2/4 + 3/5
    // the random spawn rect (and the probe attempt
    // count max(1, 5*4)), 0xc/0xd the fixed point
    // (0xc = 0 -> random), 8 restock batch,
    // 0x11 cluster flag (0 = skip the DB cluster),
    // 0x12 random-map mode (0 = fixed)
    p->m_cfg.m_fnGetInt = [dwType, dwMap](int idx){
        // GetInt(1) = the MAP id (+0x54 in fixed mode),
        // GetInt(9) = the record type word,
        // GetInt(6) = the geo step -> grid-cell cap
        // (30/20)*(40/20) = 2, GetInt(7) = 1s spawn
        // interval, GetInt(8) = restock batch 1/tick
        return idx == 1 ? (int)dwMap
             : idx == 9 ? (int)dwType
             : idx == 0xf ? 0
             : idx == 0x10 ? 0
             : idx == 0x12 ? 0
             : idx == 0x11 ? 0
             : idx == 2 ? 500
             : idx == 3 ? 300
             : idx == 4 ? 40
             : idx == 5 ? 30
             : idx == 6 ? 20
             : idx == 7 ? 1
             : idx == 8 ? 1
             : idx == 0xc ? 0
             : idx == 0xd ? 0
             : 0; };
    m_mapGens[(int)m_dwNextGenId] = p.get();
    uint32_t dwGenId = m_dwNextGenId;
    ++m_dwNextGenId;
    m_vecGenSpawned.push_back(0);
    // ---- FUN_14005fc90 seams ----
    // FUN_14004cc70 / FUN_140049310 stubs
    p->m_fnCellOk = [](void*, int, int){ return true; };
    p->m_fnPosValid = [](void*, int, int){
        return false; };
    p->m_fnSpawnNewNpcId = [this]{ return NextNpcId(); };
    p->m_fnGetMapId = [dwMap]{ return dwMap; };
    p->m_fnGetId = [dwGenId]{ return dwGenId; };
    // FUN_140061220 + FUN_1400613a0: the real
    // CMsgAiNpcInfo assembly from the 0x38 record
    p->m_fnBuildSpawnMsg =
        [](const AiNpcInfoRecord& r){
            CMsgAiNpcInfo m;
            return m.CreateFromBuffer(&r); };
    // FUN_14001c5f0 send: socket loop-back seam -> the
    // unit-9 Process path (find/new/CNpc::Create/
    // register) exactly as a wire-delivered message
    p->m_fnSendMsg = [this](const AiNpcInfoRecord& r){
        HandleAiNpcInfo(r); };
    // ---- boot load: CreateNpc once (FUN_140032800
    // pattern; map object lookup by the +0x54 TYPE
    // slot - the map table must hold it) ----
    if (!p->CreateNpc(nullptr, 0)) return;
    p->m_dwFieldF = 0;        // GetInt(0xf) = 0 above
    // +0x14: written by Process (FUN_140060b00) from
    // GetInt(8) on each due timer - no seeding
    // manager registration: vcall +0x80 = Process
    // (FUN_140060b00 wraps the Generator FUN_14005fc90)
    NpcGenerator* pReg = new NpcGenerator();
    uint32_t i = (uint32_t)(m_vecGens.size());
    pReg->m_fnProcess = [this, i](uint32_t dwBudget){
        return m_vecGens[i]->Process(dwBudget); };
    m_mgr.m_vecGenSet.push_back(pReg);
    m_vecGens.push_back(std::move(p));
}


CNpcServerApp::LiveNpc* CNpcServerApp::FindNpc(uint32_t dwId) {
    for (auto& p : m_vecNpcs)
        if (p->dwId == dwId) return p.get();
    return nullptr;
}

// ===== unit 9 -> 10: the message receive path =====
// FUN_1400614f0 (Process) with the app as the kernel:
// find by id (vtable+0x40), new CNpc (FUN_14005d9c0),
// CNpc::Create (FUN_14005e2e0), fail -> vtable+0xf0,
// register (vtable+0x28), +0x34 flag -> vtable+0x98.
bool CNpcServerApp::HandleAiNpcInfo(
        const AiNpcInfoRecord& rec) {
    CMsgAiNpcInfo msg;
    LiveNpc* pCreated = nullptr;
    msg.m_fnFindNpcById = [this](uint32_t dwId){
        return (void*)FindNpc(dwId); };
    msg.m_fnNewNpc = [&, this]{
        pCreated = new LiveNpc();
        pCreated->dwId = rec.dw[0];
        WireNpc(pCreated);
        static CNpcObj carrier;
        carrier.m_pSub10 =
            pCreated->obj.m_ab + 0x10;
        return &carrier; };
    msg.m_fnNpcCreate = [&, this](CNpcObj*,
                                const AiNpcInfoRecord& r){
        uint64_t rr = NpcCreateFromAiRecord(&pCreated->obj,
                                            r);
        return (rr & 0xFF) == 1; };
    msg.m_fnNpcFailF0 = [&, this](CNpcObj*){
        delete pCreated; pCreated = nullptr; };
    msg.m_fnNpcRegister = [&, this](CNpcObj*){
        pCreated->anchor.nX =
            pCreated->obj.At<int32_t>(0x34);
        pCreated->anchor.nY =
            pCreated->obj.At<int32_t>(0x38);
        m_mgr.m_mapNpcSet[pCreated->dwId] =
            &pCreated->mgrNpc;
        m_vecNpcs.emplace_back(pCreated);
        pCreated = nullptr; };
    msg.m_fnNpcNotify98 = [this](CNpcObj*){
        Console("notify98"); };   // vtable+0x98 seam TBD
    if (!msg.CreateFromBuffer(&rec)) return false;
    msg.Process((void*)1);        // pConn != 0
    return FindNpc(rec.dw[0]) != nullptr;
}

} // namespace npc
