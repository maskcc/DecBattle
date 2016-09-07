/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Thread.h
 * Author: admin
 *
 * Created on 2016年9月7日, 下午2:35
 */

#ifndef THREAD_H
#define THREAD_H
#include "utils.h"
#include "ThreadBase.h" 

/***
 * 使用 spawn  来创建线程, 创建的函数原型 worker, 在类中要是静态函数, 当线程退出时, 应该将线程状态置为 -1
 */
const int32_t MAX_THREAD_COUNT = 100;
class Thread
{
public:
    Thread();
    int32_t spawn(worker w, void* agrc);
    void join();

protected:
    ThreadBase pool[MAX_THREAD_COUNT];
    int32_t m_threadCount;//线程线程数量
};


#endif /* THREAD_H */

