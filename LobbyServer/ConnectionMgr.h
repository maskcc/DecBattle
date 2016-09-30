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
#include "SocketEPoll.h"

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
    ~ConnectionMgr();
    
    //默认连接属性时连接和发送到客户端...
    //添加新连接
    int32_t addConnection(Socket *s);
    //接受连接
    int32_t acceptPeer(Socket* s, Socket*& client);
    //主动连接服务器
    int32_t connectPeer(const char* serverip, int32_t port);
    
    //主动断开连接
    void disconnect(Socket *s);
    //接收到消息
    int32_t receiveMsg(Socket *s, PMsgBase &msg);
    //发送消息
    int32_t sendMsg(Socket *s);
    Socket* getPeer(int32_t idx);
    Socket* newSock(int32_t fd, int32_t type, const char* addr);
    int32_t getConnectionCount();
    uint32_t getOnlineCount();
    
    static uint32_t HANDLER;
    
protected:    
    //CONN_MAP m_connMap;              //连接
    //可以添加一个用来表示已经连接和还未连接id的位示图, 寻找时找到空闲连接的时间为O(1)
    Socket m_connMap[MAX_SOCKET_COUNT];
    uint32_t m_connCount;            //连接数量
    
};


#endif /* CLIENTCONNECTION_H */

