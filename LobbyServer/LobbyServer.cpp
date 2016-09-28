/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "LobbyServer.h"
#include "utils.h"
#include "SockServer.h"
#include "GlobalQueue.h"
#include "Dispatch.h"
#include "Gate.h"

void 
LobbyServer::loadConfig()
{
    config = string("bootstrap.lua");
}
void 
LobbyServer::start()
{    
    __log(_WARN, __FILE__, __LINE__, __FUNCTION__, "------------- main LobbyServer started!-----");
    
     for(int c = 0; c < 3; c++)
        m_threads.spawn(dispatchMessage, NULL);
    this->runSockServer();
     
    
    //等sock服务器启动完成后再启动bootstrap(应该有更好的方法)
    sleep(1);
    this->loadConfig();
    ContextMap::getInstance()->newContext(this->config, "bootstrap");
    
     m_threads.spawn(gateServer, NULL);
    //多线程处理逻辑
   m_threads.join();
    
}



void 
LobbyServer::runSockServer()
{
    Addr *addr = (Addr*) malloc(sizeof(Addr));
    memset(addr, 0, sizeof(Addr));
    const char *ip = "0.0.0.0";
    strncpy(addr->ip, ip, strlen(ip) + 1);
    addr->port = 10077;
    if(pipe(addr->fd))
    {
        close(addr->fd[0]);
        close(addr->fd[1]);
        _LOG(_ERROR, "pipe fail");
        exit(-1);
    }     
    
    SockServer *svr = SockServer::getInstance();
    if(0 != svr->initServer(addr))
    {
        free(addr);        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "Init Sock Server failed");
        return;
    }
    free(addr);
    m_threads.spawn(sockServer, (void*)svr);
    
    
}

void 
LobbyServer::sockServer(void *argc)
{
     if(NULL == argc)
    {        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "the argc is null, can not run sock server");
        
    }    
     
    SockServer *svr = (SockServer *)argc;
    __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "Init sock server success");
    if(0 != svr->run())
    {       
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "run Server failed");
        return;
    }
    
}

void 
LobbyServer::dispatchMessage(void *)
{
    Dispatch *dis = new Dispatch;

    dis->dispatch();
    
    _LOG(_ERROR, "dispatch has been shutdown");

    
}

void 
LobbyServer::gateServer(void *argc)
{ 
    Gate *gate = new Gate();
    __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "Gate Init success");
    gate->dispatch();
    
    _LOG(_ERROR, "gate has been shutdown");
    
    
    
}
