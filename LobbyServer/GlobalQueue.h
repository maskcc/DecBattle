/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GlobalQueue.h
 * Author: admin
 *
 * Created on 2016年9月12日, 下午7:12
 */

#ifndef GLOBALQUEUE_H
#define GLOBALQUEUE_H
#include <queue>
#include <pthread.h>

#include "GameDef.h"
#include "utils.h"
#include "MQueue.h"
#include "MutexLock.h"

using namespace std;
/**
 * 全局队列
 */

class MQueue;
class GlobalQueue
{
public:
    static GlobalQueue* getInstance();
    void push(MQueue* msg);
    MQueue* pop();
    void lockQ();
    void unlockQ();
    void waitQ();
    
     
 
protected:
    ~GlobalQueue();
     static GlobalQueue* m_instance;
     queue<MQueue*> m_msgQueue; 
     
    MutexLock m_lock;
     
    pthread_cond_t m_conditoin;
    
     
     
    
   
private:
    GlobalQueue();
    
    
    
    
};

#endif /* GLOBALQUEUE_H */

