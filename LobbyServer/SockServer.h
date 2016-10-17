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
#include "ParseQueue.h"
using namespace std;

//在此线程做了对连接的心跳检测, 在 MAX_TIMEOUT_KICK * TIME_OUT_SECONDS 时间内没有收到心跳包就断开连接
class SockServer
{
public:
   
    ~SockServer();
    int32_t initServer(Addr *addr);
   // int32_t initSock(const char* listenip, int32_t port);
    int32_t addListen(const char* listenip, int32_t port);
    
    //返回0 表示不是监听者,1表示是监听, 小于0 错误
    int32_t    isListener(const Socket*);
    int32_t initEPoll();
    int32_t connectServer();
    
    int32_t semdMsg();
    
    int32_t timeOut(int32_t tm);//超过了定时时间, 自动踢掉没有发送消息的连接, 默认30秒
    int32_t epollWait(int32_t);
    int32_t run();
    int32_t getSendFD();
    void disconnect(Socket *s); 
    bool hasCmd();
    void ctrlCmd();    
    void blockReadpipe(void *buffer, int sz);
    
    static SockServer *getInstance();
    static SockServer *ins;
    static uint32_t HANDLER;
protected:
    //和客户端的连接管理
    //它有自己的一套idx
     SockServer();
    
    int32_t m_epollFD;
    int32_t m_sendctrFD;
    int32_t m_readctrFD;
    fd_set m_rfds;
    bool m_checkCtr;
    
    
    event  m_ev[MAX_EVENTS];
    EPOLL_EV m_tmpev[MAX_EVENTS];
    ConnectionMgr m_connMgr;
    vector<Socket*> m_listenSock;
    bool m_stop;
    
};


#endif /* SOCKSERVER_H */

