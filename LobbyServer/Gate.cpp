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
        delete q;
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
    return;
    
    //将外部消息转换成内部消息
    InerMsg *m;
    ContextMgr* ctx = ContextMap::getInstance()->find(m->service);
    if(NULL == ctx)
    {
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "can not find service name[%s]!", m->service.c_str());
        return;
        
    }
    
    ctx->putMsg(m);
    
}
