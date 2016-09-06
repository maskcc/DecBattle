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
#include "ConnectionMgr.h"
#include "utils.h"


typedef struct  event_t {
	void * s; //每个event附带的信息
	bool read;
	bool write;
}event;

typedef struct epoll_event EPOOL_EV; 

class SockServer
{
public:
    SockServer();
    int32_t initServer(char* listenip, int32_t port);
    int32_t initSock(char* listenip, int32_t port);
    int32_t initEPoll();
    int32_t connectServer();
    
    int32_t semdMsg();
    
    int32_t epollWait();
    int32_t run();
    
protected:
    //和客户端的连接管理
    //int32_t m_sockFD;        //接收连接的fd
    int32_t m_epollFD;
    Socket m_sock;           //服务器监听的socket信息
    event  m_ev[MAX_EVENTS];
    ConnectionMgr m_connMgr;
    bool m_stop;
    
};


#endif /* SOCKSERVER_H */

