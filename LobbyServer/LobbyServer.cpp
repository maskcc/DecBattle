/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "LobbyServer.h"
#include "utils.h"
#include "SockServer.h"

void 
LobbyServer::loadConfig()
{
    config = string("bootstrap.lua");
}
void 
LobbyServer::start()
{
    _LOG("------------- main LobbyServer started!-----", _WARN);
    
    this->loadConfig();
    this->newContext();
    for(int c = 0; c < 100; c++)
     m_threads.spawn(runLuaEngin, NULL);
     
    //this->runLuaEngin();
    
    this->runSockServer();
    
    
   m_threads.join();
    
}

void 
LobbyServer::newContext()
{
    ContextMgr *ctx = new ContextMgr(this->config);
    
    ctx->Init();
    m_CtxMap.insert(make_pair(ctx->getHandle(), ctx));
    
    
    
}


void 
LobbyServer::runSockServer()
{
    Addr *addr = (Addr*) malloc(sizeof(Addr));
    memset(addr, 0, sizeof(Addr));
    char *ip = "0.0.0.0";
    strncpy(addr->ip, ip, strlen(ip) + 1);
    addr->port = 10077;
    m_threads.spawn(sockServer, (void*)addr);
    
}

void LobbyServer::sockServer(void *argc)
{
    if(NULL == argc)
    {
        _LOG("the argc is null, can not run sock server", _ERROR);
        
    }
    Addr *addr = (Addr *)argc;
    SockServer svr;
    if(0 != svr.initServer(addr->ip, addr->port))
    {
        free(addr);
        _LOG("Init Server failed", _ERROR);
        return;
    }
    free(addr);
    if(0 != svr.run())
    {
        _LOG("run Server failed", _ERROR);
        return;
    }
    
}

void LobbyServer::runLuaEngin(void *)
{
 //   sleep(rand()%3);
    ContextMgr *ctx = new ContextMgr("bootstrap.lua");
    
    ctx->Init();
    _LOG("lua enigin init succeed", _WARN);
    sleep(30);
}
