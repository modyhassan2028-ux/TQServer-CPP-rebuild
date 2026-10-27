#pragma once
#include <string>
#include <vector>

// Lua 5.4 bridge for NPC scripts (original Conquer NPC logic is scripted;
// this ports the pattern). One global VM, scripts loaded from data/lua/npc/.

class CUser;

class CLuaVM {
public:
    static CLuaVM& Instance();

    bool Init();                       // create the state and register the API
    void Shutdown();
    bool IsReady() const { return m_pState != nullptr; }

    // load+run a script file (data/lua/<name>.lua); on false returns the error
    bool LoadScript(const std::string& strName, std::string& strError);
    // call a global function from the last loaded chunk with the user bound
    bool CallUserFunc(const std::string& strFunc, CUser* pUser, std::string& strError);
    // list of script names loaded into the VM (for /luarun)
    const std::vector<std::string>& LoadedScripts() const { return m_scripts; }

private:
    CLuaVM() = default;
    void* m_pState{nullptr};           // lua_State* kept opaque to headers
    std::vector<std::string> m_scripts;
    friend struct LuaBridge;
};
