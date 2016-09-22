/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContextMap.h
 * Author: admin
 *
 * Created on 2016年9月13日, 下午2:08
 */

#ifndef CONTEXTMAP_H
#define CONTEXTMAP_H
#include <map>
#include "ContextMgr.h"
using namespace std;

class  ContextMap
{
public:
    ~ContextMap();
    static ContextMap* getInstance();
    //新脚本, scriptName, 脚本名字, name, 服务名字
    ContextMgr* newContext(string scriptName, string name);
    ContextMgr* find(string svcName);
    
public:
    static ContextMap *m_ins;
protected:
    //保存lua虚拟机
    //<handle, Ctx>
    map<int, ContextMgr*> m_CtxMap;    
    
    ContextMap();
};

#endif /* CONTEXTMAP_H */

