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

SockServer::~SockServer()
{
    
    
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
    int32_t sockfd = sp_socket();
    sp_bindListen(sockfd, listenip, port);
    
    //m_sock 的idx设置为-1
    m_sock.init(sockfd, -1,CONN_TYPE_NONE);
     
    return 0;
 }
 
 int32_t 
 SockServer::initEPoll()
 {   
    /*init epoll server*/
    
    m_epollFD = sp_create(MAX_SOCKET_COUNT);   
    if (0 != sp_add(m_epollFD, m_sock.getFD(), (void *)&m_sock))    
    {        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "epoll open fail!");
        return -1;
    }
    sp_nonblocking(m_sock.getFD());
    
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
    //EPOLL_EV ev[MAX_EVENTS] = {0};
    memset(m_tmpev, 0, MAX_EVENTS*sizeof(EPOLL_EV));
    int n = epoll_wait(m_epollFD, m_tmpev, MAX_EVENTS, -1);
    int i;
    for (i = 0; i < n; i++) {
        m_ev[i].s = m_tmpev[i].data.ptr;
        unsigned flag = m_tmpev[i].events;
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
            __log(_WARN, __FILE__, __LINE__, __FUNCTION__, "EPoll server has been closed.");
            return ERROR_TYPE_STOP_SERVER;
        }
        
        n = this->epollWait();
        if(0 >= n)
        {
            //EINTR 在写的时候出现中断错误 
           // If a signal handler is invoked while a system call or library  function call is blocked, then either:
           // 重新开始就行
            if(EINTR == errno)
            {
                continue;
            }
            __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "epoll wait number below 0");
            return ERROR_TYPE_EPOOL_WAIT_FAIL;
        }
        index = 0;
        while (index < n)
        {
            event *e = &m_ev[index++];
            Socket *s = static_cast<Socket* >(e->s);
            if(NULL == s)
            {            
                __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "find the null socket!");
                return ERROR_TYPE_NULL_SOCKET;
            }

            if(e->read)
            {
                if(*s == m_sock)
                //if(true)
                {
                    //接收连接                            
                    __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "New connection come");   
                    //int fd = accept(m_sock.getFD(), NULL, NULL);
                    //__log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "accept [%d]!", fd);
                     
                    Socket *client = m_connMgr.acceptPeer(s); //等价于 m_sock;
                    if(NULL == client)
                    {                    
                        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "accept null peer!");
                        return ERROR_TYPE_NULL_SOCKET;
                    } 
                    __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "Acceept succeed, connidx[%d],connfd is[%d] and now connection count is[%d]", 
                            client->getIdx(),client->getFD(), m_connMgr.getConnectionCount());
                    
                    //EPOOL_EV *ev = (EPOOL_EV*)malloc(sizeof(EPOOL_EV)) ;
                    //貌似这里不需要malloc
                    ///EPOLL_EV tev = {0};
                    ///EPOLL_EV *ev = &tev;
                    
                    if(0 != sp_add(m_epollFD, client->getFD(), (void*)client))
                    {
                        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "epoll add ctl fail!");
                        return ERROR_TYPE_ADDCTL_FAIL;
                    }
                    

                }   
                else
                {
                    //有消息到来      
                    BaseMsg * msg = NULL;
                    int readret = m_connMgr.receiveMsg(s, msg);
                    if(readret == MSG_TYPE_DISCONNECT)
                    {
                        m_connMgr.disconnect(s);                    
                        __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "connection has been closed by peer!");

                    }    
                    if(NULL != msg)
                    {
                        GlobalQueue::getInstance();

                    }
                }      
            }
            else  if(e->write)
            {            
                __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "write something to far!");

            }         
        }
        
         
         
     }
 }
