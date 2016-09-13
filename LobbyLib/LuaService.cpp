/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "LuaService.h"


int32_t
llaunch(lua_State *L)
{
    const char *file = luaL_checkstring(L, -1);
    if(NULL == file)
    {
        _LOG("get script file name error", _ERROR);
        lua_pushinteger(L, -1);
        return 1;
    }
    ContextMgr *mgr = ContextMap::getInstance()->newContext(static_cast<string>(file));
    if(NULL == mgr)
    {
        _LOG("load script ctx fail", _ERROR);
        lua_pushinteger(L, -1);
        return 1;        
    }
    
    lua_pushinteger(L, 0);
    return 1;  
}


int32_t
lcall(lua_State *L)
{
    const char *file = luaL_checkstring(L, 1);
    if(NULL == file)
    {
        _LOG("get script file name error", _ERROR);
        lua_pushinteger(L, -1);
        return 1;
    }
    ContextMgr *mgr = ContextMap::getInstance()->find(static_cast<string>(file));
    if(NULL == mgr)
    {
        _LOG("find script ctx fail", _ERROR);
        lua_pushinteger(L, -1);
        return 1;        
    }
    
    int32_t type = luaL_checkinteger(L, -3);
    const char *msg = luaL_checkstring(L, -2);
    int32_t sz = luaL_checkinteger(L, -1);
    int32_t ret = mgr->call(type, (void*)msg, sz);
    
    lua_pushinteger(L, ret);
    return 1;  
}

extern "C" int32_t 
luaopen_lobbylib_core(lua_State *L)
{
    luaL_Reg l[] = {
        { "launch", llaunch }, 
        { "call", lcall }, 
        
        { NULL, NULL },
    };
      
    luaL_newlibtable(L, l);         
    luaL_setfuncs(L, l, 0);
    return 1;
}
