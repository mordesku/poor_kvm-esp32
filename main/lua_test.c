//
// Created by mordesku on 11/1/2021.
//

#include "lua_test.h"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int l_println(lua_State *L) {
    const char *a = luaL_checklstring(L, 1, NULL);
    printf("[LUA] %s\n", a);
    return 1;
}

void do_magic() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_println);
    lua_setglobal(L, "lprintln");
    char * code = "lprintln('Hello, World from lua')";

    if (luaL_loadstring(L, code) == LUA_OK) {
        if (lua_pcall(L, 0, 0, 0) == LUA_OK) {
            lua_pop(L, lua_gettop(L));
        }
    }
    lua_close(L);
}