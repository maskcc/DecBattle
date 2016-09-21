/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MutexLock.h
 * Author: admin
 *
 * Created on 2016年9月21日, 下午4:12
 */

#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H
#include <pthread.h>
#include <iostream>
#include <queue>
#include <stdint.h>

#include "GameDef.h"
#include "utils.h"
using namespace std;

class MutexLock
{
public:
    MutexLock();
    ~MutexLock();
    int32_t lock();
    int32_t unlock();
    pthread_mutex_t *get();


protected:
    pthread_mutex_t m_lock;

};



#endif /* MUTEXLOCK_H */

