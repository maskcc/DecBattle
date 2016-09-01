/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContextMgr.h
 * Author: admin
 *
 * Created on 2016年9月1日, 下午4:56
 */

#ifndef CONTEXTMGR_H
#define CONTEXTMGR_H
#include <string>
#include "lua.hpp"
#include "MQueue.h"
using namespace std;

/**
 c struct 里面只保存指向类的指针
 */
typedef struct Context_t
{
    uint32_t  handle;
    lua_State *state;
    MQueue    *queue;    
    
}Context;

class ContextMgr
{
public:
    //启动 script name
    ContextMgr(string sname);
    int Init();
    int getHandle();
    lua_State* getLuaState();
    
protected:
    int loadScript();
    
protected:
    Context *m_Ctx;
    
    //脚本名称
    string scriptName;
    
    //ctx 唯一标识符基数
    static int HANDLEID;
    
    
};



#endif /* CONTEXTMGR_H */

