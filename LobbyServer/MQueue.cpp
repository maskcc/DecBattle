/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "MQueue.h"
#include "GlobalQueue.h"
#include "NameService.h"


MQueue::MQueue(int s, string sname)
{
    this->m_isBusy = false;
    this->m_service = s;
    this->m_inGlobal = false;
    this->m_svcName = sname;
}

//推入队列尾端 
void 
MQueue::push(InerMsg *msg)
{
    m_lock.lock();
    if(msg->service != this->m_svcName)   
    {     
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "Push the wrong msg into msg queue[%d] wrongqueue[%d] source[%d] ", 
                                                        this->m_service, msg->service.c_str(), msg->source.c_str());
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
InerMsg* MQueue::pop()
{
    m_lock.lock();
    InerMsg *m = NULL;
    if(!m_MQ.empty())
    {
        m = m_MQ.front();
        m_MQ.pop();
    }
    else
    {
        m_inGlobal = false;
    }
    std::cout<< "msg count is" << m_MQ.size() <<std::endl;
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
