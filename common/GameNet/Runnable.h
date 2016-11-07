/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Runable.h
 * Author: admin
 *
 * Created on 2016年11月4日, 下午3:51
 */

#ifndef RUNABLE_H
#define RUNABLE_H

#include "Thread.h"
class CThread;
class Runnable
{
public:
    Runnable(){};
    virtual ~Runnable() = 0;
    virtual void run(CThread *thread, void *arg) = 0;
    
};


#endif /* RUNABLE_H */

