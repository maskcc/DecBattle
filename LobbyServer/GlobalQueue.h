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

#include "GameDef.h"
#include "MQueue.h"
using namespace std;
/**
 * 全局队列
 */
class GlobalQueue
{
public:
     static GlobalQueue* getInstance();
     
 
protected:
    ~GlobalQueue();
     static GlobalQueue* m_instance;
private:
    GlobalQueue();
    
    
    
    
};

#endif /* GLOBALQUEUE_H */

