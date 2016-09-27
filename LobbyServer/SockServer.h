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
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <vector>
#include "ConnectionMgr.h"
#include "utils.h"
#include "SocketEPoll.h"
using namespace std;

class SockServer
{
public:
    SockServer();
    ~SockServer();
    int32_t initServer(const char* listenip, int32_t port);
   // int32_t initSock(const char* listenip, int32_t port);
    int32_t addListen(const char* listenip, int32_t port);
    bool    isListener(const Socket*);
    int32_t initEPoll();
    int32_t connectServer();
    
    int32_t semdMsg();
    
    int32_t epollWait();
    int32_t run();
    void disconnect(Socket *s);    
    
    static uint32_t HANDLER;
protected:
    //和客户端的连接管理
    //它有自己的一套idx
    
    int32_t m_epollFD;
    //Socket m_sock;           //服务器监听的socket信息
    event  m_ev[MAX_EVENTS];
    EPOLL_EV m_tmpev[MAX_EVENTS];
    ConnectionMgr m_connMgr;
    vector<Socket> m_listenSock;
    bool m_stop;
    
};


#endif /* SOCKSERVER_H */

