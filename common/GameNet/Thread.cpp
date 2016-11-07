/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Thread.h"

CThread::CThread()
 {    
    m_tid = 0;
    m_args = nullptr;
    m_runnable = nullptr;
}

bool CThread::start(Runnable *a, void *arg)
{
    m_runnable = a;
    m_args = arg;
    int ret = pthread_create(&m_tid, NULL, hook, this);
    return ret == 0; 
    
}

void* CThread::hook(void *args)
{
    CThread *thread = static_cast<CThread*> (args);
    if(nullptr == thread)
    {
        _LOG(_ERROR, "thread is a nullptr");
        exit(-1);
    }
    
    if(thread->getRunnable())
    {
        //类成员的静态函数获取了其他成员的私有变量. ???
        thread->getRunnable()->run(thread, thread->m_args);
    }
    return (void*)nullptr;
}

Runnable *CThread::getRunnable()
{
    return m_runnable;
}

pthread_t CThread::getTid()
{
    return m_tid;
}

void CThread::wait()
{
    if(m_tid)
    {
        pthread_join(m_tid, NULL);
    }
    m_tid = 0;
    
}