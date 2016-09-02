/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Snlua.h
 * Author: admin
 *
 * Created on 2016年9月2日, 下午1:51
 */

#ifndef SNLUA_H
#define SNLUA_H
#include "ContextMgr.h"

/**
 * 执行回调函数
 * 加载回调函数的参数, pcall回调函数
 * @param ctx
 * @param type
 * @param msg
 * @param sz
 * @return 
 */
static int 
_cb(Context *ctx, int type, void* msg, int sz);



/**
 * 注册函数, 在lua 中调用 callback(start_func)
 * 调用callback 只能与自己的虚拟机关联
 * @param L
 * @return 
 */
int 
lcallback(lua_State *L);


class Snlua
{
public:
    
    
    
protected:
    
};




#endif /* SNLUA_H */

