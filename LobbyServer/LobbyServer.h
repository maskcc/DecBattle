/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LobbyServer.h
 * Author: admin
 *
 * Created on 2016年9月1日, 下午2:55
 */

#ifndef LOBBYSERVER_H
#define LOBBYSERVER_H
#include <map>
#include <string>
#include "GameDef.h"
#include "ContextMgr.h"
#include "SockServer.h"
#include "Thread.h"

using namespace std;

class LobbyServer
{
public:
    void loadConfig();
    void start();
    void newContext();
    void runSockServer();
    static void runLuaEngin(void *);
    static void sockServer(void *);
    
    
    
    
    
    
protected:
    //保存lua虚拟机
    //<handle, Ctx>
    map<int, ContextMgr*> m_CtxMap; 
    string config;
    Thread m_threads;
    
    
    
};


#endif /* LOBBYSERVER_H */

