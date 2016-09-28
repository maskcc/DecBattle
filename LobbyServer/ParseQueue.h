/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParseQueue.h
 * Author: admin
 *
 * Created on 2016年9月28日, 上午11:19
 */

#ifndef PARSEQUEUE_H
#define PARSEQUEUE_H
#include <queue>
#include <pthread.h>

#include "GameDef.h"
#include "utils.h"
#include "MutexLock.h"

using namespace std;
/**
 * 全局队列
 */

class MQueue;
class ParseQueue
{
public:
    static ParseQueue* getInstance();
    void push(BaseMsg* msg);
    BaseMsg* pop();
    void lockQ();
    void unlockQ();
    void waitQ();
    ~ParseQueue();
    
     
 
protected:
    ParseQueue();
     static ParseQueue* m_instance;
     queue<BaseMsg*> m_msgQueue; 
     
    MutexLock m_lock;
     
    pthread_cond_t m_conditoin;
    
     
     
    
   
private:
    
    
    
    
    
};



#endif /* PARSEQUEUE_H */

