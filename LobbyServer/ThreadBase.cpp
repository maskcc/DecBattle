/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "ThreadBase.h"

void
ThreadBase::start(void *argc)
{
    this->m_argc =argc;
    
    //pthread_attr_t  attr;
    //pthread_attr_init(&attr);
    //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    int ret = pthread_create(&m_threadID, NULL, proc, (void*)this);
    if(0 != ret)
    {
        _LOG("create thread fail!", _ERROR);
        
    }
    
    
}

void
ThreadBase::init(const worker& w, const int32_t& index)
{
    this->m_worker = w;
    this->m_idx = index;
}

void *
ThreadBase::proc(void *argc)
{
    ThreadBase *obj;
    obj = static_cast<ThreadBase*>(argc);
    obj->m_worker(obj->m_argc);
    
}

int32_t 
ThreadBase::getIdx() const
{
    return this->m_idx;
}

int32_t
ThreadBase::joinThread()
{
    pthread_join(m_threadID, NULL);
}
