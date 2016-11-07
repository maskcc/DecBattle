/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThreadLock.h
 * Author: admin
 *
 * Created on 2016年11月7日, 上午11:08
 */

#ifndef THREADLOCK_H
#define THREADLOCK_H
#inclulde <pthread.h>
#inclulde <assert.h>

class CThreadLock
{
public:
    CThreadLock()
    {
        int ret = pthread_mutex_init(&m_mutex, nullptr);
        assert(ret == 0);
    }
    ~CThreadLock()
    {
        pthread_mutex_destroy(&m_mutex);
    }
public:
    void lock()
    {
        pthread_mutex_lock(&m_mutex);
    }
    int trylock()
    {
        return pthread_mutex_trylock(&m_mutex);
    }
    void unlock()
    {
        pthread_mutex_unlock(&m_mutex);
    }
private:
    pthread_mutex_t m_mutex;
    
};

class CThreadGuard
{
public:
    CThreadGuard(CThreadLock *mutex)
    {
        m_mutex = nullptr;
        if(mutex)
        {
            m_mutex = mutex;
            m_mutex.lock();
        }
    }
    ~CThreadGuard()
    {
        if(m_mutex)
        {
            m_mutex.unlock();
        }
    }
private:
    CThreadLock *m_mutex;
};

#endif /* THREADLOCK_H */

