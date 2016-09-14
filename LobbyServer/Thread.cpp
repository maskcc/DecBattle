/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Thread.h" 

Thread::Thread()
{
    for(int c = 0;  c < MAX_THREAD_COUNT; ++c )
    {        
        pool[c].init(NULL, -1);
    }
    
}

int32_t 
Thread::spawn(worker w, void* argc)
{    
    int c = 0;
    for( c = 0;  c < MAX_THREAD_COUNT; ++c )
    {        
        if(-1 == pool[c].getIdx())
        {
            pool[c].init(w, c);
            break;
        }        
    }    
    if(c >= MAX_THREAD_COUNT)
    {
        //_LOG("all thread is in use.", _WARN);
        __log(_WARN, __FILE__, __LINE__, __FUNCTION__, "all thread is in use.");
        return ERROR_TYPE_NONE_THREAD;
    }
    
    pool[c].start(argc);
    ++this->m_threadCount;
    
}

void
Thread::join()
{
    for(int c = 0;  c < MAX_THREAD_COUNT; ++c )
    {        
        if(-1 != pool[c].getIdx())
        {
            pool[c].joinThread();
        }
    }
    
}
