/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "ConnectionMgr.h"

ConnectionMgr::ConnectionMgr() 
{
    m_connCount = 0;
}

int32_t
ConnectionMgr::addConnection(Socket *s) 
{

    if (m_connCount >= MAX_CLIENT_CONNECTION) 
    {
        _LOG("connection is more than 1000", _ERROR);
        return -1;
    }

    Socket *client = getPeer(s->getFD());
    if (NULL != client) 
    {//客户端已经连接.不可能走到这来.连接没关闭, 应该不会生成到新连接的fd
        _LOG("Client socket has been connected!", _ERROR);

        s->closeHandle();
        return -1;
    }


    ++m_connCount;
    m_connMap.insert(make_pair(s->getFD(), s));
    return 0;

}

/**
 * 
 * @param s
 *  表示服务器监听的端口
 * @return 
 */
Socket*
ConnectionMgr::acceptPeer(Socket *s) 
{
    int connfd = accept(s->getFD(), NULL, NULL);
    if (connfd <= 0) {
        _LOG("accept client fail!", _ERROR);
        return NULL;
    }
    Socket *client = new Socket();
    client->init(connfd, CONN_TYPE_CLIENT);
    int ret = addConnection(client);
    if(0 != ret)
    {
        return NULL;
    }
    return client;
}

int32_t
ConnectionMgr::connectPeer(const char* serverip, int32_t port) 
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(serverip);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    int connfd = connect(sockfd, (struct sockaddr *) &addr, sizeof (struct sockaddr_in));
    if (-1 == connfd) 
    {
        _LOG("Connect to server failed!", _ERROR);
        return -1;
    }
    Socket *client = new Socket();
    client->init(connfd, CONN_TYPE_SERVER);
    return addConnection(client);

}

void
ConnectionMgr::disconnect(Socket *s) 
{
    Socket *client = getPeer(s->getFD());
    if (NULL == client) 
    {//客户端或服务没连接
        _LOG("socket is not connected!", _ERROR);
        return;
    }

    CONN_MAP_ITER iter;
    iter = m_connMap.find(client->getFD());

    if (m_connMap.end() == iter) 
    {
        _LOG("can not find client connection, disconnect failed!", _ERROR);
        if (NULL != client) 
        {
            client->closeHandle();
        }
        return;
    }

    m_connMap.erase(iter);
    client->closeHandle();
    --m_connCount;

}

int32_t
ConnectionMgr::receiveMsg(Socket *s, BaseMsg *msg) 
{
    Socket *client = getPeer(s->getFD());
    if (NULL == client) 
    {//客户端没连接
        _LOG("Client socket is not connected!", _ERROR);
        return ERROR_TYPE_NULL_SOCKET;
    }
    return client->readHandle(msg);
   
   
}

int32_t
ConnectionMgr::sendMsg(Socket *s) 
{
    Socket *client = getPeer(s->getFD());
    if (NULL == client) 
    {//客户端没连接
        _LOG("Client socket is not connected!", _ERROR);
        return -1;
    }
    return client->writeHandle();
    
}

Socket*
ConnectionMgr::getPeer(int32_t id) 
{
    CONN_MAP_ITER iter;

    iter = m_connMap.find(id);
    if (m_connMap.end() == iter) {
        return NULL;
    }



    return iter->second;

}


