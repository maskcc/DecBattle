/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ContextMgr.h"
#include "utils.h"
#include <assert.h>


int ContextMgr::HANDLEID = 0; 

static int 
traceback (lua_State *L) {
	const char *msg = lua_tostring(L, 1);
	if (msg)
		luaL_traceback(L, L, msg, 1);
	else {
		lua_pushliteral(L, "(no error message)");
	}
	return 1;
}

ContextMgr::ContextMgr(string sname)
{    
    this->scriptName = sname;    
   
    
}
int 
ContextMgr::Init()
{
    m_Ctx = new Context;
    m_Ctx->state = luaL_newstate();
    m_Ctx->queue = new MQueue();
    m_Ctx->handle = ++HANDLEID;
    
    return this->loadScript();
    
}

int ContextMgr::loadScript()
{
    lua_State *L = this->getLuaState();
    lua_gc(L, LUA_GCSTOP, 0);
    luaL_openlibs(L);
    lua_pushlightuserdata(L, this->m_Ctx);
    lua_setfield(L, LUA_REGISTRYINDEX, "Context");
    //lua_pushcfunction(L, traceback);
    
    assert(lua_gettop(L) == 0);
    
    //可以在这加个loader, 用lua来控制读取的文件以及其他信息
    int r = luaL_dofile(L, this->scriptName.c_str());    
    //int r = luaL_loadfile(L, this->scriptName.c_str());
   //lua_pcall(L, 0,0,0);
    
    if (r != LUA_OK) 
    {
        //char buff[1024] = {0};
        //snprintf(buff, 1024, "load script load file fail[%s]", this->scriptName.c_str());
        const char *buff;
        buff = lua_tostring(L, -1);
        _LOG(buff, _ERROR);
        return -1;
    }
    
    lua_gc(L, LUA_GCRESTART, 0);
    return 0;
    
}
int
ContextMgr::getHandle()
{
    return this->m_Ctx->handle;
    
}
lua_State*
ContextMgr::getLuaState()
{
    return this->m_Ctx->state;
    
}
