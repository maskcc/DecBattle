/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Thread.h
 * Author: admin
 *
 * Created on 2016年11月4日, 下午3:49
 */

#ifndef THREAD_H
#define THREAD_H
#include <stdint.h>
#include <pthread.h>

#include "Runnable.h"
#include "utils.h"


class CThread
{
public:
    CThread();
   
    ~CThread();
    
public:
    bool start(Runnable *a, void *arg);
    pid_t getPid();
    pthread_t getTid();
    Runnable *getRunnable();
    void wait();
    
private:
    static void* hook(void *args);
    
private:
    void *m_args;
    
    pthread_t m_tid;
    Runnable *m_runnable;
    
    
};


#endif /* THREAD_H */

