/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LuaService.h
 * Author: admin
 *
 * Created on 2016年9月13日, 下午1:58
 */

#ifndef LUASERVICE_H
#define LUASERVICE_H
#include <lua.hpp>
#include "ContextMgr.h"
#include "NameService.h"
#include "ContextMap.h"
#include "ContextMgr.h"

extern "C" int luaopen_lobbylib_core(lua_State *L);

int llaunch(lua_State *L);
int lcall(lua_State *L);



#endif /* LUASERVICE_H */

