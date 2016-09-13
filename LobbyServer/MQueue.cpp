/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "MQueue.h"



MQueue::MQueue(int s)
{
    this->isBusy = false;
    this->service = s;
}

//推入队列尾端 
void 
MQueue::push(InerMsg_t *msg)
{
    if(msg->service != this->service)
    {
        char buff[128] = {0};
        snprintf(buff, 128, "Push the wrong msg into msg queue[%d] wrongqueue[%d] source[%d] ", 
                                                        this->service, msg->service, msg->source);
        _LOG(buff, _ERROR);
        return;
        
    }
    if(m_MQ.size() >= MESSAGEQUEUE_WARN_LENGTH)
    {
        this->isBusy = true;
        char buff[128] = {0};
        snprintf(buff, 128, "MQueue is busy now!, size is %d", m_MQ.size());
        _LOG(buff, _WARN);
        //队列超标该如何处理???
    }
    m_MQ.push(msg);
   
}
    
    //从队头弹出
InerMsg_t* MQueue::pop()
{
}

    
int32_t MQueue::getService() const
{
    return this->service;
}

