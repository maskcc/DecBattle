/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SockServer.h"
#include "MQueue.h"
#include "GlobalQueue.h"

SockServer::SockServer()
{
    m_stop = false;
    m_epollFD = -1;
    memset(m_ev, 0, MAX_EVENTS * sizeof(event));
    
}

 int32_t 
 SockServer::initServer(char* listenip, int32_t port)
 {     
     if(0 != this->initSock(listenip, port))
     {
         return -1;
     }
     if(0 != this->initEPoll())
     {
         return -1;
     }
     
    return 0;
 }
 
 
 int32_t 
 SockServer::initSock(char* listenip, int32_t port)
 {     
     /*start listen port*/
    int32_t sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr = {0};   
    socklen_t addrlen = sizeof(servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port =  htons(port);
    if(0 == inet_aton(listenip, &servaddr.sin_addr))
    {
        _LOG("server ip configer is not right!", _ERROR);
         return -1;
    }
    if(0 != bind(sockfd, (struct sockaddr* )&servaddr, addrlen))
    {
        _LOG("bind failed!", _ERROR);
         return -1;
    }
    if(0 != listen(sockfd, MAX_BACK_LOG))
    {
        _LOG("listen failed!", _ERROR);
        return -1;
    }
    
    m_sock.init(sockfd, CONN_TYPE_NONE);
     
    return 0;
 }
 
 int32_t 
 SockServer::initEPoll()
 {   
    /*init epoll server*/
    EPOOL_EV ev = {0};
    m_epollFD = epoll_create(MAX_CLIENT_CONNECTION);
    ev.events = EPOLLIN;
    ev.data.ptr = &m_sock;
    if (-1 == epoll_ctl(m_epollFD, EPOLL_CTL_ADD, m_sock.getFD(), &ev))
    {
        _LOG("epoll open fail!", _ERROR);
        return -1;
    }
    
    //noblocking
//    int flag = fcntl(m_sock.getFD(), F_GETFL, 0);
//    if ( -1 == flag ) {
//        _LOG("epoll fcntl fail!", _ERROR);
//        return -1;
//    }
    
    return 0;
 }
 
 
 
int32_t 
SockServer::connectServer()
{
        
        
}
    
int32_t 
SockServer::semdMsg()
{
        
        
}


int32_t
SockServer::epollWait() {
    EPOOL_EV ev[MAX_EVENTS] = {};
    int n = epoll_wait(m_epollFD, ev, MAX_EVENTS, -1);
    int i;
    for (i = 0; i < n; i++) {
        m_ev[i].s = ev[i].data.ptr;
        unsigned flag = ev[i].events;
        m_ev[i].write = (flag & EPOLLOUT) != 0;
        m_ev[i].read = (flag & EPOLLIN) != 0;
    }

    return n;
}

 int32_t 
 SockServer::run()
 {
     int32_t n = -1;
     int32_t index = 0;
     
     for(;;)
     {
        if(m_stop)
        {
            _LOG("EPoll server has been closed.", _WARN);
            return ERROR_TYPE_STOP_SERVER;
        }
        
        n = this->epollWait();
        if(0 >= n)
        {
            _LOG("epoll wait number below 0", _ERROR);
            return ERROR_TYPE_EPOOL_WAIT_FAIL;
        }
        
        event *e = &m_ev[index++];
        Socket *s = static_cast<Socket* >(e->s);
        if(NULL == s)
        {
            _LOG("find the null socket!", _ERROR);
            return ERROR_TYPE_NULL_SOCKET;
        }
            
        if(e->read)
        {
            if(*s == m_sock)
            {
                //接收连接
                _LOG("New connection come", _DEBUG);                
                Socket *client = m_connMgr.acceptPeer(s); //等价于 m_sock;
                if(NULL == client)
                {
                    _LOG("accept null peer!", _ERROR);
                    return ERROR_TYPE_NULL_SOCKET;
                }
                
                EPOOL_EV *ev = (EPOOL_EV*)malloc(sizeof(EPOOL_EV)) ;
                if(NULL == ev)
                {
                    _LOG("malloc ev fail!", _ERROR);
                    return ERROR_TYPE_MALLOC_FAIL;
                }
                ev->events = EPOLLIN;
                ev->data.ptr = client;
                if (-1 == epoll_ctl(m_epollFD, EPOLL_CTL_ADD, client->getFD(), ev))
                {
                    _LOG("epoll add ctl fail!", _ERROR);
                    return ERROR_TYPE_ADDCTL_FAIL;
                }
                
            }   
            else
            {
                //有消息到来      
                BaseMsg * msg;
                int readret = m_connMgr.receiveMsg(s, msg);
                if(readret == MSG_TYPE_DISCONNECT)
                {
                    m_connMgr.disconnect(s);
                    _LOG("connection has been closed by peer!", _DEBUG);
                    
                }    
                if(NULL != msg)
                {
                    GlobalQueue::getInstance();
                    
                }
            }      
        }
        else  if(e->write)
        {
            _LOG("write something to far!", _ERROR);
            
            
        }
         
        if(index >= n)
        {
            index = 0;
            n = -1;
        }
         
         
         
     }
 }
