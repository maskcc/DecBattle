/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dispatch.h
 * Author: admin
 *
 * Created on 2016年9月2日, 下午5:51
 */

#ifndef DISPATCH_H
#define DISPATCH_H

#include <pthread.h>

#include "ContextMap.h"
#include "MQueue.h"
#include "ContextMap.h"
#include "GlobalQueue.h"
#include "utils.h"

class Dispatch
{
public:
    Dispatch();
    ~Dispatch();
    int32_t dispatch();
    MQueue* dealMsg(MQueue* q);
    int32_t count;
    
protected:

};


#endif /* DISPATCH_H */

