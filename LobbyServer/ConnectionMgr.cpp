/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "ConnectionMgr.h"

ConnectionMgr::ConnectionMgr()
{
    m_cliCount = 0;
    m_svrCount = 0;
    
}

int32_t
ConnectionMgr::addConnection(int32_t connfd, int32_t type)
{
    
    if(CONN_TYPE_CLIENT == type && m_cliCount >= MAX_CLIENT_CONNECTION)
    {
        _LOG("Clients is more than 1000", _ERROR);
        return -1;
    }
    
    if(CONN_TYPE_SERVER == type && m_cliCount >= MAX_CLIENT_CONNECTION)
    {
        _LOG("Clients is more than 1000", _ERROR);
        return -1;
    }
    Socket *client = getPeer(connfd, type);
    if(NULL != client)
    {//客户端已经连接.不可能走到这来.连接没关闭, 应该不会生成到新连接的fd
        _LOG("Client socket has been connected!", _ERROR);
        return -1;
    }
    client = new Socket();
    client->init(connfd);
     if(CONN_TYPE_CLIENT == type)
     {
        ++m_cliCount;
     }
     if(CONN_TYPE_SERVER == type)
     {
        ++m_svrCount;
     }
}

int32_t
ConnectionMgr::acceptPeer(int32_t connfd)
{
    return addConnection(connfd, CONN_TYPE_CLIENT);
}

int32_t 
ConnectionMgr::connectPeer(const char* serverip, int32_t port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_addr.s_addr=inet_addr(serverip);
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    int connfd = connect(sockfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_in));
    if(-1 == connfd)
    {
        _LOG("Connect to server failed!", _ERROR);
        return -1;
    }
    
    return addConnection(connfd, CONN_TYPE_SERVER);
    
}


int32_t
ConnectionMgr::disconnect(int32_t connfd, int32_t type)
{
    Socket *client = getPeer(connfd, type );
    if(NULL == client)
    {//客户端或服务没连接
        _LOG("Client socket is not connected!", _ERROR);
        return -1;
    }
    client->closeHandle();
    if(CONN_TYPE_CLIENT == type)
    {
       --m_cliCount;
    }
    if(CONN_TYPE_SERVER == type)
    {
        --m_svrCount;
    }
    
    return 0;
}
int32_t
ConnectionMgr::receiveMsg(int32_t connfd, int32_t type)
{
    Socket *client = getPeer(connfd, type);
    if(NULL == client)
    {//客户端没连接
        _LOG("Client socket is not connected!", _ERROR);
        return -1;
    }
    client->readHandle();
}
        
int32_t       
ConnectionMgr::sendMsg(int32_t connfd, int32_t type)
{
    Socket *client = getPeer(connfd, type);
    if(NULL == client)
    {//客户端没连接
        _LOG("Client socket is not connected!", _ERROR);
        return -1;
    }
    client->writeHandle();
}

Socket* 
ConnectionMgr::getPeer(int32_t fd, int32_t type)
{
    CONN_MAP_ITER iter;
    if(CONN_TYPE_CLIENT == type)
    {
        iter = m_clientMap.find(fd);
        if(m_clientMap.end() == iter)
        {
            _LOG("can not find client connection!",_ERROR);
            return NULL;
        }
    }
    if(CONN_TYPE_SERVER == type)
    {
        iter = m_serverMap.find(fd);
        if(m_serverMap.end() == iter)
        {
            _LOG("can not find client connection!",_ERROR);
            return NULL;
        }
    }
    
    return iter->second;
    
}


