/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "LuaService.h"


int32_t
llaunch(lua_State *L)
{
    const char *file = luaL_checkstring(L, 1);
    const char *name = luaL_checkstring(L, 2);
    if(NULL == file)
    {        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "get script file name error");
        lua_pushinteger(L, -1);
        return 1;
    }
    if(NULL == name)
    {        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "get script file reg name error");
        lua_pushinteger(L, -1);
        return 1;
    }
    ContextMgr *mgr = ContextMap::getInstance()->newContext(static_cast<string>(file), static_cast<string>(name));
    if(NULL == mgr)
    {        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "load script ctx fail");
        lua_pushinteger(L, -1);
        return 1;        
    }
    
    lua_pushinteger(L, 0);
    return 1;  
}


int32_t
lcall(lua_State *L)
{
    const char *svc = luaL_checkstring(L, 1);
    if(NULL == svc)
    {        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "get script file name error");
        lua_pushinteger(L, -1);
        return 1;
    }
    ContextMgr *mgr = ContextMap::getInstance()->find(static_cast<string>(svc));
    if(NULL == mgr)
    {        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "get script file name error");
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

int lsend(lua_State *L)
{
 
    const char *service = luaL_checkstring(L, 1);
    const char *source = luaL_checkstring(L, 2);
    int32_t type = luaL_checkinteger(L, 3);
    int32_t sz = luaL_checkinteger(L, 4);
    const char *msg = luaL_checkstring(L, 5);
    //reader.parse(str, root);
    
    InerMsg *m = new InerMsg;
    memset(m, 0, sizeof(InerMsg));
    m->sz = sz;
    m->type = type;
    memcpy(m->service, service, SERVICE_NAME_LENGTH);
    memcpy(m->source, source, SERVICE_NAME_LENGTH);
    m->msg = (char*)malloc(m->sz);
    memset(m->msg, 0, m->sz);
    memcpy(m->msg, msg, m->sz);
    
    __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "send msg sz[%d] type[%d] service[%s] source[%s]",
                    sz, type, m->service, m->source);
    //GlobalQueue::getInstance()->push(m);
    
    ContextMgr* ctx = ContextMap::getInstance()->find(m->service);
    if(NULL != ctx)
    {
        ctx->putMsg(m);
    }
    else
    {
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "can not find service name[%s]!", m->service);
    }
    
    
    
    
    return 1;
}


int lexit(lua_State *L)
{
    exit(0);
    return 0;
}
extern "C" int32_t 
luaopen_lobbylib_core(lua_State *L)
{
    luaL_Reg l[] = {
        { "launch", llaunch }, 
        { "call", lcall }, 
        { "send", lsend }, 
        { "exit", lexit },
        
        { NULL, NULL },
    };
      
    luaL_newlibtable(L, l);         
    luaL_setfuncs(L, l, 0);
    return 1;
}
