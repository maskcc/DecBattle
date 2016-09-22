/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "MQueue.h"
#include "GlobalQueue.h"
#include "NameService.h"


MQueue::MQueue(int s)
{
    this->m_isBusy = false;
    this->m_service = s;
    this->m_inGlobal = false;
}

//推入队列尾端 
void 
MQueue::push(InerMsg_t *msg)
{
    m_lock.lock();
    //if(NameService::getInstance()->search(msg->service) != this->m_service)
    //域名查找暂时屏蔽
    if(false)
    {     
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "Push the wrong msg into msg queue[%d] wrongqueue[%d] source[%d] ", 
                                                        this->m_service, msg->service, msg->source);
        m_lock.unlock();
        return;
        
    }
    if(m_MQ.size() >= MESSAGEQUEUE_WARN_LENGTH)
    {
        this->m_isBusy = true;
  
        __log(_WARN, __FILE__, __LINE__, __FUNCTION__, "MQueue is busy now!, size is %d", m_MQ.size());
        //队列超标该如何处理???
    }
    m_MQ.push(msg);
    if(!m_inGlobal)
    {
        GlobalQueue::getInstance()->push(this);
    }
    m_inGlobal = true;
    m_lock.unlock();
   
}
    
    //从队头弹出
InerMsg_t* MQueue::pop()
{
    m_lock.lock();
    InerMsg_t *m = NULL;
    if(!m_MQ.empty())
    {
        m = m_MQ.front();
        m_MQ.pop();
    }
    else
    {
        m_inGlobal = false;
    }
    m_lock.unlock();
    return m;
}

    
int32_t MQueue::getService() const
{
    return this->m_service;
}

void 
MQueue::setOutGlobal()
{
    this->m_inGlobal = false;
}
