#include "LuaVM.h"
#include <cstdio>

CLuaVM& CLuaVM::Instance() {
    static CLuaVM s;
    return s;
}
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "../User.h"
#include "../Item.h"
#include "../MapManager.h"
#include "../MsgTalk.h"

// user bound for the current call (single-threaded chat processing)
static CUser* g_pLuaUser = nullptr;

static int lua_say(lua_State* L) {           // say(text)
    if (!g_pLuaUser || lua_gettop(L) < 1 || !lua_isstring(L, 1)) return 0;
    g_pLuaUser->SendSysMsg(lua_tostring(L, 1));
    return 0;
}
static int lua_get_level(lua_State* L) {     // get_level() -> number
    lua_pushinteger(L, g_pLuaUser ? g_pLuaUser->GetLevel() : 0);
    return 1;
}
static int lua_get_money(lua_State* L) {     // get_money() -> number
    lua_pushinteger(L, g_pLuaUser ? (lua_Integer)g_pLuaUser->GetMoney() : 0);
    return 1;
}
static int lua_give_item(lua_State* L) {    // give_item(type, amount)
    if (!g_pLuaUser || lua_gettop(L) < 2) return 0;
    uint32_t t = (uint32_t)luaL_checkinteger(L, 1);
    uint32_t n = (uint32_t)luaL_checkinteger(L, 2);
    if (n == 0) n = 1;
    auto* pDef = CItemLibrary::Instance().Lookup(t);
    if (!pDef) { lua_pushboolean(L, 0); return 1; }
    ItemInfo item;
    item.dwType = t; item.dwAmount = n;
    CItemLibrary::Instance().Apply(item);
    g_pLuaUser->GetInventory().push_back(item);
    g_pLuaUser->SendSysMsg("Received: " + item.strName + " x" + std::to_string(n));
    lua_pushboolean(L, 1);
    return 1;
}
static int lua_teleport(lua_State* L) {      // teleport(map, x, y)
    if (!g_pLuaUser || lua_gettop(L) < 3) return 0;
    g_pLuaUser->Teleport((uint32_t)luaL_checkinteger(L, 1),
                         (uint16_t)luaL_checkinteger(L, 2),
                         (uint16_t)luaL_checkinteger(L, 3));
    return 0;
}
static int lua_rand(lua_State* L) {          // rand(min, max) -> number
    lua_Integer lo = (lua_Integer)luaL_optinteger(L, 1, 0);
    lua_Integer hi = (lua_Integer)luaL_optinteger(L, 2, 99);
    if (hi < lo) { lua_Integer t = lo; lo = hi; hi = t; }
    lua_pushinteger(L, lo + rand() % (hi - lo + 1));
    return 1;
}
static int lua_broadcast(lua_State* L) {    // broadcast(text)
    if (lua_gettop(L) < 1 || !lua_isstring(L, 1)) return 0;
    CMsgTalk note;
    if (note.Create("SYSTEM", "", lua_tostring(L, 1), CMsgTalk::Channel_Broadcast))
        CMapManager::Instance().BroadcastToAll(note.GetBuf(), note.GetSize());
    return 0;
}

bool CLuaVM::Init() {
    if (m_pState) return true;
    m_pState = luaL_newstate();
    if (!m_pState) return false;
    luaL_openlibs((lua_State*)m_pState);
    lua_State* L = (lua_State*)m_pState;
    lua_register(L, "say", lua_say);
    lua_register(L, "get_level", lua_get_level);
    lua_register(L, "get_money", lua_get_money);
    lua_register(L, "give_item", lua_give_item);
    lua_register(L, "teleport", lua_teleport);
    lua_register(L, "rand", lua_rand);
    lua_register(L, "broadcast", lua_broadcast);
    printf("[LUA] VM ready (Lua %s). Scripts: data/lua/*.lua\n", LUA_RELEASE);
    return true;
}

void CLuaVM::Shutdown() {
    if (m_pState) { lua_close((lua_State*)m_pState); m_pState = nullptr; }
}

bool CLuaVM::LoadScript(const std::string& strName, std::string& strError) {
    if (!m_pState && !Init()) return false;
    // guard names against path traversal: [a-zA-Z0-9_] only
    for (char c : strName) {
        bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                  (c >= '0' && c <= '9') || c == '_';
        if (!ok) { strError = "bad script name"; return false; }
    }
    std::string path = "data/lua/" + strName + ".lua";
    lua_State* L = (lua_State*)m_pState;
    if (luaL_dofile(L, path.c_str()) != LUA_OK) {
        strError = lua_tostring(L, -1) ? lua_tostring(L, -1) : "load failed";
        lua_pop(L, 1);
        printf("[LUA] %s: %s\n", path.c_str(), strError.c_str());
        return false;
    }
    for (auto& s : m_scripts) if (s == strName) return true;
    m_scripts.push_back(strName);
    printf("[LUA] loaded script: %s\n", strName.c_str());
    return true;
}

bool CLuaVM::CallUserFunc(const std::string& strFunc, CUser* pUser, std::string& strError) {
    if (!m_pState) { strError = "vm not initialized"; return false; }
    lua_State* L = (lua_State*)m_pState;
    lua_getglobal(L, strFunc.c_str());
    if (!lua_isfunction(L, -1)) { lua_pop(L, 1); strError = "no function: " + strFunc; return false; }
    g_pLuaUser = pUser;
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        strError = lua_tostring(L, -1) ? lua_tostring(L, -1) : "call failed";
        lua_pop(L, 1);
        printf("[LUA] %s failed: %s\n", strFunc.c_str(), strError.c_str());
        g_pLuaUser = nullptr;
        return false;
    }
    g_pLuaUser = nullptr;
    return true;
}
