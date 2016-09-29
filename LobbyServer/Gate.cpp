/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Gate.h"
#include "ParseQueue.h"

Gate::Gate()
{
    ConfigMgr mgr;
}
Gate::~Gate()
{
    
    
}

int32_t 
Gate::dispatch()
{
    BaseMsg *q = NULL;
    for(;;)
    {
        q = ParseQueue::getInstance()->pop();
        
        _LOG(_WARN, "get msg parsed");
        //暂时不知道如何解析外部消息 
        //dealMsg(q);
        if(NULL == q)
        {
            ParseQueue::getInstance()->lockQ();
            //没消息来时, 会阻塞在这
            ParseQueue::getInstance()->waitQ();            
            ParseQueue::getInstance()->unlockQ();
        }        
        
    }
    return 0;
}

void 
Gate::dealMsg(BaseMsg* q)
{
    InerMsg *m;
    ContextMgr* ctx = ContextMap::getInstance()->find(m->service);
    if(NULL == ctx)
    {
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "can not find service name[%s]!", m->service.c_str());
        return;
        
    }
    
    ctx->putMsg(m);
    
}
