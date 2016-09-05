/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Socket.h
 * Author: admin
 *
 * Created on 2016年9月2日, 下午6:02
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <stdint.h>
#include <sys/socket.h>
#include "SockStream.h"

using namespace std;
class Socket
{
public:
    int32_t init(int connfd);
    int32_t readHandle();
    int32_t writeHandle();
    int32_t closeHandle();
    int32_t getFD();
    
    
protected:
    SockStream m_stream;
protected:
    string   m_addr;   //地址
    uint16_t m_port;   //端口号
    int32_t  m_fd;     //连接信息
    
    uint64_t m_lastRecvTime; //上次接收或发送消息的时间戳
    
    
    
};


#endif /* SOCKET_H */

