/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetWork.h
 * Author: admin
 *
 * Created on 2016年11月4日, 下午4:51
 */

#ifndef NETWORK_H
#define NETWORK_H
#include <signal.h>

#include "Thread.h"
#include "Runnable.h"

class CNetWork 
: public Runnable
{
public:
    CNetWork();
    ~CNetWork();
    
public:
    bool start();
    

private:
    void run(CThread* thread, void* arg) ;
private:
    //超时踢人线程
    CThread m_timeoutThread;
    
    //读写线程
    CThread m_rwThread;
    
    
    
};

#endif /* NETWORK_H */

