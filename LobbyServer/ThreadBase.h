/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThreadBase.h
 * Author: admin
 *
 * Created on 2016年9月7日, 下午2:09
 */

#ifndef THREADBASE_H
#define THREADBASE_H
#include <pthread.h>
#include <stdint.h>
#include "utils.h"
typedef void (*worker)(void* argc);

class ThreadBase
{
public:
    void init(const worker& w, const int32_t& index);
    void start(void *argc);
    int32_t getIdx() const;
    int32_t joinThread();
    static void* proc(void* args);    
    

protected:
    worker  m_worker;     //线程函数
    pthread_t m_threadID; 
    int32_t m_idx;
    void* m_argc;    //传入的参数
    
    
};


#endif /* THREADBASE_H */

