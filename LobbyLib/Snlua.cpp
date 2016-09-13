/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Snlua.h"

static int 
_cb(Context *ctx, int type, void* msg, int sz)
{
    lua_State *l = ctx->state;
    lua_rawgetp(l, LUA_REGISTRYINDEX, (void*)_cb);
 
    lua_pushinteger(l, type);
    lua_pushlstring(l, static_cast<const char*>(msg), sz);
    lua_pushinteger(l, sz);
    
     int r = lua_pcall(l, 3, 0, 0);
    if(LUA_OK != r)
    {
        const char *buff;
        buff = lua_tostring(l, -1);
        _LOG(buff, _ERROR); 
        _LOG(static_cast<const char*>(msg), _ERROR); 
        return -1;       
    }

    _LOG("callback sucess!", _DEBUG);    
    return 0;
}

int 
lcallback(lua_State *L)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "Context");
    Context *ctx = static_cast<Context*>(lua_touserdata(L, -1));
    if(NULL ==ctx)
    {
        _LOG("ctx is null, please init first!", _ERROR); 
        lua_pushinteger(L, -1);
        return 1;
    }
    
    
    luaL_checktype(L,1,LUA_TFUNCTION);
    lua_settop(L, 1); //将函数压栈
    lua_rawsetp(L, LUA_REGISTRYINDEX, (void*)(_cb));
    ctx->cb = _cb;    
    
    char buff[1024];
    snprintf(buff, 1024, "callback ctx registed, handler is:%d" , ctx->handle);
    _LOG(buff, _DEBUG);
    lua_pushinteger(L, 0);
    return 1;
    
}


extern "C" int 
luaopen_lobbylib_snlua(lua_State *L)
{
    luaL_Reg l[] = {
        { "callback", lcallback },        
        
        { NULL, NULL },
    };
      
    luaL_newlibtable(L, l);         
    luaL_setfuncs(L, l, 0);
    return 1;
}
