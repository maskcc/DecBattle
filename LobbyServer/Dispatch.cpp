/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Dispatch.h"

Dispatch::Dispatch()
{
    count = 0;
}
Dispatch::~Dispatch()
{
    
    
}

int32_t 
Dispatch::dispatch()
{
    MQueue *q = NULL;
    for(;;)
    {
        q = dealMsg(q);
        if(NULL == q)
        {
            GlobalQueue::getInstance()->lockQ();
            //没消息来时, 会阻塞在这
            GlobalQueue::getInstance()->waitQ();            
            GlobalQueue::getInstance()->unlockQ();
        }        
        
    }
    return 0;
}

MQueue* 
Dispatch::dealMsg(MQueue* q)
{
    if(NULL == q)
    {
         q = GlobalQueue::getInstance()->pop();
    }
    if(NULL == q)
    {
        return q;
    }
    
    InerMsg* msg = q->pop();
    while(NULL != msg)
    {
        ContextMgr *ctxMgr = ContextMap::getInstance()->find(msg->service);
        if(NULL == ctxMgr)
        {
            _LOG(_ERROR, "cannot find context");
            msg = q->pop();
            //还需要一些其他处理
            continue;
        }
        //__log(_WARN, __FILE__, __LINE__, __FUNCTION__, "get msg type[%d]  msg[%s] sz[%d]", msg->type, msg->msg, msg->sz);
        ctxMgr->call(msg->type, msg->msg, msg->sz);
  
        
        SAFEDEL(msg);
        ++count;        
        msg = q->pop();
    }
    
   
    
    
    return GlobalQueue::getInstance()->pop();
}
