/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SockStream.h
 * Author: admin
 *
 * Created on 2016年9月5日, 上午9:42
 */

#ifndef SOCKSTREAM_H
#define SOCKSTREAM_H

#include <unistd.h>
#include "GameDef.h"
#include "utils.h"

const uint32_t MSG_SIZE_LENGTH = 4;
const uint32_t STEP_READ_SIZE = 1;
const uint32_t STEP_READ_BODY = 2;
const uint32_t BUFF_LENGTH = 8192;

class SockStream
{
public:
    SockStream();
    int32_t reciveMsg(int32_t fd, BaseMsg *msg);
    int32_t reset();
    virtual ~SockStream();
protected:
    int32_t m_bodySize; //需要读取的包体长度
    int32_t m_readSize;   //已经读取的长度
    int32_t m_readStep;   //当前读取进度
    
    
    char m_stream[BUFF_LENGTH];  //最大缓冲区, 8KB
};


#endif /* SOCKSTREAM_H */

