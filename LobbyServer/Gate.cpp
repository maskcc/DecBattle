/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Gate.h"
#include "ParseQueue.h"

Gate::Gate()
{
    NetMessageManager::getInstance()->loadCfg("NJZnetMessage");
}
Gate::~Gate()
{
    
    
}

int32_t 
Gate::dispatch()
{
     MsgBase* q = NULL;
    for(;;)
    {
        q = ParseQueue::getInstance()->pop();
        
        dealMsg(q);
        if(NULL == q)
        {
            ParseQueue::getInstance()->lockQ();
            //没消息来时, 会阻塞在这
            ParseQueue::getInstance()->waitQ();            
            ParseQueue::getInstance()->unlockQ();
        }               
        SAFEDEL( q );
        q = NULL;
        
    }
    return 0;
}

void 
Gate::dealMsg( MsgBase* q)
{
    if(NULL == q)
    {
        return;
    }
    
    string msg;    
    msg = NetMessageManager::getInstance()->writeMessageToJson(q);    
    _LOGX(_DEBUG, "read ok msg[%s]", msg.c_str());
   
    
    InerMsg *m = new InerMsg;
    if(NULL == m)
    {
        _LOG(_ERROR, "malloc InerMsg fail");
    }
    
    m->sz = msg.size();
    m->type = 3;
    m->service = "gate";
    m->source = "";
    m->msg = msg;
     
   
     
    ContextMgr* ctx = ContextMap::getInstance()->find(m->service);
    if(NULL == ctx)
    {
        _LOGX(_ERROR,  "can not find service name[%s]!", m->service.c_str());
        return;
    }
    
    ctx->putMsg(m);
    
    return;
    
    
}
