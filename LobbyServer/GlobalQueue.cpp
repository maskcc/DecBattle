/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "GlobalQueue.h"

GlobalQueue* GlobalQueue::m_instance = new GlobalQueue;

GlobalQueue* 
GlobalQueue::getInstance()
{

    return m_instance;
        
    
}

 void 
GlobalQueue::push(MQueue* q)
 {    
    lockQ();
    m_msgQueue.push(q);
    pthread_cond_signal(&m_conditoin);
    unlockQ();
 }


 
 MQueue* 
 GlobalQueue::pop()
 {
    lockQ();
    MQueue *q = NULL;
    if(!m_msgQueue.empty())
    {
        q = m_msgQueue.front();
        m_msgQueue.pop();
        
    }
    unlockQ(); 
    return q;
 }
 
 void
 GlobalQueue::lockQ()
 {
     
    m_lock.lock();
     
 }
 
 void
 GlobalQueue::unlockQ()
 {     
    m_lock.unlock(); 
     
 }
 
 void 
 GlobalQueue::waitQ()
 {       
   // __log(_WARN, __FILE__, __LINE__, __FUNCTION__, "I am waiting here");
    pthread_cond_wait(&m_conditoin, m_lock.get());
    //__log(_WARN, __FILE__, __LINE__, __FUNCTION__, "stop wait");
    //当没有消息时, 会阻塞在这
     
 }
 
 GlobalQueue::GlobalQueue()
 {
    
    if(0 != pthread_cond_init(&m_conditoin, NULL))
     {        
         __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "init global queue cond fail");
     }
 }
 
GlobalQueue:: ~GlobalQueue()
 {
     if(0 != pthread_cond_destroy(&m_conditoin))
     {         
         __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "init global queue cond fail");
     }
 }
