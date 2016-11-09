/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerSocket.h
 * Author: admin
 *
 * Created on 2016年11月8日, 上午11:19
 */

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <sys/socket.h>
#include <memory>
#include "Socket.h"

//backlog 设置成256, 当多个连接同时到来时, 处理速度快
const int32_t LISTEN_BACKLOG = 256;

using namespace std;
class ServerSocket
: public Socket {
public:
    ServerSocket();
    ~ServerSocket();

    //监听某个fd
    void listen(int32_t fd);
    
    //返回智能指针, 不用担心内存泄漏问题, 失败返回nullptr
    //接收对面的连接, 返回connfd, 填充peer为对面的ip
    shared_ptr<Socket> accept(int32_t sockfd, string &peer);

};

#endif /* SERVERSOCKET_H */

