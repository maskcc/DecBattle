/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameDef.h
 * Author: admin
 *
 * Created on 2016年9月1日, 下午2:58
 */


/**
 * 注意:
 *写头文件时, 和类紧密相关的数据结构写在类里面,
 * 方便查找, 而且不会出现引用交叉问题
 *该数据结构的相关处理最好只和这个类相关
 */
#ifndef GAMEDEF_H
#define GAMEDEF_H
#include "lua.hpp"
#include "stdint.h"


/*
 Log Color define
 */
const int _DEBUG = 1;   // green
const int _WARN = 2;  //yellow
const int _ERROR = 4; //red


/**
 * MQueue的警报长度
 */
const int MESSAGEQUEUE_WARN_LENGTH = 100;
//messagequeue 的前置声明



typedef struct BaseMsg_t
{
    void *msg;
    uint32_t sz;
    
}BaseMsg;





#endif /* GAMEDEF_H */

