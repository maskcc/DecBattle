/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SockServer.h"

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
    
    m_sock.init(sockfd);
     
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
            break;
        }
        
        n = this->epollWait();
        if(0 >= n)
        {
            _LOG("epoll wait number <= 0", _ERROR);
            break;
        }
        
        event *e = &m_ev[index++];
        Socket *s = static_cast<Socket* >(e->s);
        if(NULL == s)
        {
            _LOG("find the null socket!", _ERROR);
            return -1;
        }
            
        if(e->read)
        {
            if(*s == m_sock)
            {
                //接收连接
                _LOG("A CONNECTION come", _DEBUG);
                int connfd = accept(s->getFD(), NULL, NULL);
                m_connMgr.acceptPeer(connfd);
                
                EPOOL_EV *ev = (EPOOL_EV*)malloc(sizeof(EPOOL_EV)) ;    
                ev->events = EPOLLIN;
                ev->data.ptr = m_connMgr.getPeer(connfd);
                if (-1 == epoll_ctl(m_epollFD, EPOLL_CTL_ADD, connfd, ev))
                {
                    _LOG("epoll open fail!", _ERROR);
                    return -1;
                }
                
            }   
            else
            {
                //有消息到来 
                //_LOG("a message come", _DEBUG);
                s->readHandle();
                
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
