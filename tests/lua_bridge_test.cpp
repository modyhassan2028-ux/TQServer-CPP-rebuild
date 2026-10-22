// E2E: embed Lua, run a script that calls back into C++ and checks math
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include <cassert>
#include <cstdio>
#include <string>

static int c_double(lua_State* L) {           // c_double(x) -> 2x
    lua_Integer x = luaL_checkinteger(L, 1);
    lua_pushinteger(L, x * 2);
    return 1;
}
static int c_add(lua_State* L) {              // c_add(a, b) -> a+b
    lua_Integer a = luaL_checkinteger(L, 1);
    lua_Integer b = luaL_checkinteger(L, 2);
    lua_pushinteger(L, a + b);
    return 1;
}

int main() {
    lua_State* L = luaL_newstate();
    assert(L);
    luaL_openlibs(L);
    lua_register(L, "c_double", c_double);
    lua_register(L, "c_add", c_add);

    // script exercises: pure Lua math, tables, a loop, and C callbacks
    const char* script =
        "function compute(n)\n"
        "  local sum = 0\n"
        "  for i = 1, n do sum = sum + i end\n"           // 1..n triangular
        "  return c_double(n) + c_add(sum, n * (n + 1) / 2)\n"
        "end\n"
        "answers = {}\n"
        "answers['doubled'] = c_double(21)\n";
    if (luaL_dostring(L, script) != LUA_OK) {
        printf("script error: %s\n", lua_tostring(L, -1));
        return 1;
    }
    // compute(5): c_double(5)=10; add(sum=15, 5*6/2=15) = 30 -> 40
    lua_getglobal(L, "compute");
    assert(lua_isfunction(L, -1));
    lua_pushinteger(L, 5);
    assert(lua_pcall(L, 1, 1, 0) == LUA_OK);
    assert(lua_tointeger(L, -1) == 40);
    lua_pop(L, 1);

    lua_getglobal(L, "answers");
    lua_getfield(L, -1, "doubled");
    assert(lua_tointeger(L, -1) == 42);
    lua_pop(L, 2);

    // load error path: syntax errors must be reported, not crash
    assert(luaL_dostring(L, "this is not lua(") != LUA_OK);
    std::string err = lua_tostring(L, -1);
    assert(err.find("syntax error") != std::string::npos);
    lua_pop(L, 1);

    lua_close(L);
    printf("LUA_BRIDGE_OK: C->Lua->C callbacks, loop+table math, error reporting\n");
    return 0;
}
