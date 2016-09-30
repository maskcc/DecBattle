/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gate.h
 * Author: admin
 *
 * Created on 2016年9月27日, 上午10:18
 */

#ifndef GATE_H
#define GATE_H
#include <queue>
#include "Socket.h"
#include "InerMsg.h"
#include "ParseQueue.h"
#include "ContextMgr.h"
#include "ContextMap.h"
#include "ConfigMgr.h"
#include "NetMessageManager.h"


class Gate
{
public:
    Gate();
    ~Gate();
    int32_t dispatch();
    void dealMsg(PMsgBase q);
     
 
    
protected:
    
    
    
};


#endif /* GATE_H */

