/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "MQueue.h"

MQueue::MQueue()
{
    
    this->Init();
}
void
MQueue::Init()
{
    this->isBusy = false;
    
}

//推入队列尾端 
void MQueue::push(BaseMsg_t *msg)
{
    m_MQ.push(msg);
    if(m_MQ.size() >= MESSAGEQUEUE_WARN_LENGTH)
    {
        this->isBusy = true;
        char buff[128] = {0};
        snprintf(buff, 128, "MQueue is busy now!, size is %d", m_MQ.size());
       // _LOG(buff, _WARN);
    }
}
    
    //从队头弹出
BaseMsg_t* MQueue::pop()
{
    
}
