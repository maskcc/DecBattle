/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ParseQueue.h"

ParseQueue* ParseQueue::m_instance = new ParseQueue;

ParseQueue* 
ParseQueue::getInstance()
{
    return m_instance;
    
}

 void 
ParseQueue::push(BaseMsg* q)
 {    
    lockQ();
    m_msgQueue.push(q);
    pthread_cond_signal(&m_conditoin);
    unlockQ();
 }


 
 BaseMsg* 
 ParseQueue::pop()
 {
    lockQ();
    BaseMsg *q = NULL;
    if(!m_msgQueue.empty())
    {
        q = m_msgQueue.front();
        m_msgQueue.pop();
        
    }
    unlockQ(); 
    return q;
 }
 
 void
 ParseQueue::lockQ()
 {
     
    m_lock.lock();
     
 }
 
 void
 ParseQueue::unlockQ()
 {     
    m_lock.unlock(); 
     
 }
 
 void 
 ParseQueue::waitQ()
 { 
    pthread_cond_wait(&m_conditoin, m_lock.get());
    
    //当没有消息时, 会阻塞在这     
 }
 
 ParseQueue::ParseQueue()
 {
    
    if(0 != pthread_cond_init(&m_conditoin, NULL))
     {        
         __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "init global queue cond fail");
     }
 }
 
ParseQueue:: ~ParseQueue()
 {
     if(0 != pthread_cond_destroy(&m_conditoin))
     {         
         __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "init global queue cond fail");
     }
 }
 