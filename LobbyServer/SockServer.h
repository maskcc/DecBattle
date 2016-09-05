/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SockServer.h
 * Author: admin
 *
 * Created on 2016年9月5日, 下午5:48
 */

#ifndef SOCKSERVER_H
#define SOCKSERVER_H

#include <sys/epoll.h>
#include "ConnectionMgr.h"
#include "utils.h"
class SockServer
{
public:
    int32_t initServer(char* listenip, int32_t port);
    int32_t connectServer();
    
    int32_t semdMsg();
    
protected:
    //和客户端的连接管理
    ConnectionMgr m_clientConn;
    
    //和服务器的连接管理
    ConnectionMgr m_serverConn;
};


#endif /* SOCKSERVER_H */

