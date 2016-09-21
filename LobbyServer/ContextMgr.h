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
struct Context_t;
typedef int(*callback)(Context_t* ctx, int type, void* msg, int sz);

typedef struct Context_t
{
    uint32_t  handle;   //标识符
    lua_State *state;   //虚拟机
    MQueue    *queue;   //消息队列
    callback  cb;       //回调函数
    
}Context;


class ContextMgr
{
public:
    //启动 script name
    ContextMgr(string sname);
    ~ContextMgr();
    int32_t Init();
    int32_t getHandle();
    int32_t putMsg(InerMsg *m);
    lua_State* getLuaState();
    int32_t call(int32_t type, void *msg, int32_t sz);
    
protected:
    int32_t loadScript();
    
protected:
    Context *m_Ctx;
    
    //脚本名称
    string scriptName;
    
    //ctx 唯一标识符基数
    static int32_t HANDLEID;
    
    
};



#endif /* CONTEXTMGR_H */

