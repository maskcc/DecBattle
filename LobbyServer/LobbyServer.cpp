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
    
    SockServer svr;
    if(0 != svr.initServer("0.0.0.0", 10077))
    {
        _LOG("Init Server failed", _ERROR);
        return;
    }
    if(0 != svr.run())
    {
        _LOG("run Server failed", _ERROR);
        return;
    }
    
}

void 
LobbyServer::newContext()
{
    ContextMgr *ctx = new ContextMgr(this->config);
    
    ctx->Init();
    m_CtxMap.insert(make_pair(ctx->getHandle(), ctx));
    
    
    
}
