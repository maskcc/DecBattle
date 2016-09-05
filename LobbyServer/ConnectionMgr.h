/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientConnection.h
 * Author: admin
 *
 * Created on 2016年9月2日, 下午5:50
 */

#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <map>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "GameDef.h"
#include "Socket.h"

using namespace std;
/**
 * 管理客户端连接
 * @param connfd
 * @return 
 */

typedef map<int32_t, Socket*>  CONN_MAP;
typedef map<int32_t, Socket*>::iterator  CONN_MAP_ITER;

class ConnectionMgr
{
public:
    ConnectionMgr();
    
    
    //默认连接属性时连接和发送到客户端...
    //添加新连接
    int32_t addConnection(int32_t connfd, int32_t type=CONN_TYPE_CLIENT);
    //接受连接
    int32_t acceptPeer(int32_t connfd);
    //主动连接服务器
    int32_t connectPeer(const char* serverip, int32_t port);
    
    //主动断开连接
    int32_t disconnect(int32_t connfd, int32_t type=CONN_TYPE_CLIENT);
    //接收到消息
    int32_t receiveMsg(int32_t connfd, int32_t type=CONN_TYPE_CLIENT);
    //发送消息
    int32_t sendMsg(int32_t connfd, int32_t type=CONN_TYPE_CLIENT);
    Socket* getPeer(int32_t id, int32_t type=CONN_TYPE_CLIENT);
    
protected:    
    CONN_MAP m_clientMap;              //客户端连接上来 
    CONN_MAP m_serverMap;              //连接连到其他服务器
    uint32_t m_svrCount;            //当前连接到服务器的数量    
    uint32_t m_cliCount;            //连接到客户端的数量
    
};


#endif /* CLIENTCONNECTION_H */

