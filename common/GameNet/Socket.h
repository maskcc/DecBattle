/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Socket.h
 * Author: admin
 *
 * Created on 2016年11月8日, 上午9:53
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <utils.h>
#include <errno.h>
#include <memory>
#include <fcntl.h>

#include "Stats.h"
#include "IOComponent.h"
using namespace std;
class IOComponent;
class Socket {
public:
    Socket();
    ~Socket();

public:
    //连接服务端, 返回connfd
    bool connect(const string& addr, unsigned short port);
    bool setSoBlocking(bool block);
    void close();
    void shutdown();
    
public:
    int32_t write(const void *data, int len);
    int32_t read(void *data, int len);    
    
public:
    int32_t getLastError();
    int32_t getSockFD();
    void getAddr(string &addr);
    void setUp(int32_t fd, struct sockaddr_in addr);
    shared_ptr<IOComponent> getIOComponent();
    
protected:
    struct sockaddr_in m_addr; //地址
    int32_t m_sock; //socket文件描述符
    shared_ptr<IOComponent> m_ioComponent;  //io操作组成       
private:
    //初始化socket, 返回fd
    void init();

};


#endif /* SOCKET_H */

