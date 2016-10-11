/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MutexLock.h"

MutexLock::MutexLock()
{
    int32_t ret = pthread_mutex_init(&m_lock, NULL);
    if(0 != ret)
    {
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "init mutext lock fail [%d]!", ret);
    }

}
MutexLock::~MutexLock()
{
    unlock();
    int32_t ret = pthread_mutex_destroy(&m_lock);
    if(0 != ret)
    {
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "destroy mutext lock fail [%d]!", ret);
    }    
}

int32_t
MutexLock::lock()
{
    int32_t ret =  pthread_mutex_lock(&m_lock);
    if(0 != ret)
    {
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "lock mutext lock fail [%d]!", ret);
    }
    return ret;

}
int32_t
MutexLock::unlock()
{
    int32_t ret = pthread_mutex_unlock(&m_lock);
    if(0 != ret)
    {
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "unlock mutext lock fail [%d]!", ret);
    }
    return ret;

}
pthread_mutex_t *
MutexLock::get()
{
    return &m_lock;
}
