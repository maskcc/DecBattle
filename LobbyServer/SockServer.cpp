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
    //释放epoll fd
    sp_release(m_epollFD);
    
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
    sp_nonblocking(m_sock.getFD());
     
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
SockServer::epollWait() 
{    
    memset(m_tmpev, 0, MAX_EVENTS*sizeof(EPOLL_EV));
    int n = epoll_wait(m_epollFD, m_tmpev, MAX_EVENTS, -1);
    int i;
    for (i = 0; i < n; i++) 
    {
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
        if( n <= 0)
        {
            //EINTR 在写的时候出现中断 (例如 Ctrl + C 捕获到)           
            if(EINTR == errno)
            {
                __log(_WARN, __FILE__, __LINE__, __FUNCTION__, "EINTR");
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
                {        
                    Socket *client = NULL;
                    int accRet = m_connMgr.acceptPeer(s, client); //等价于 m_sock;
                        
                    if(accRet <= 0 )
                    {
                        if  (EAGAIN == errno || EWOULDBLOCK == errno)
                        {   
                            continue;
                        } 
                        else
                        {
                            //错误处理
                            __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "accept handle fail!");
                            continue;
                        }
                    }
                    
                    __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "Acceept succeed, connidx[%d],connfd is[%d] and now connection count is[%d]", 
                                client->getIdx(),client->getFD(), m_connMgr.getConnectionCount());
                    
                    if(0 != sp_add(m_epollFD, client->getFD(), (void*)client))
                    {
                        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "epoll add ctl fail!");
                        client->reset();
                        //错误处理??
                        //return ERROR_TYPE_ADDCTL_FAIL;
                    }
                }   
                else
                {
                    //有消息到来      
                    BaseMsg * msg = NULL;
                    int readret = m_connMgr.receiveMsg(s, msg);
                    
                    //读取出现错误
                    if( readret < 0 )
                    {
                         disconnect(s);                           
                        __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "read sock error errno[%d], close peer.", readret );
                        continue;
                        
                    }
                    if( readret == MSG_TYPE_DISCONNECT)
                    {
                         disconnect(s);   
                        __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "connection has been closed by peer! now connection count[%d]",
                               m_connMgr.getConnectionCount() );
                        continue;

                    } 
                    if( readret == ERROR_TYPE_BODY_OVER_FLOW)  
                    {
                        disconnect(s); 
                        __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "read body size over flow.");
                        continue;
                    }
                    
                    //处理消息
                    if(NULL != msg)
                    {
                        GlobalQueue::getInstance();

                    }
                }      
            }
            if(e->write)
            {            
                __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "write something to far!");

            }    
        }        
     }
 }
 
  void SockServer::disconnect(Socket *s)
{
    sp_del(m_epollFD, s->getFD());//这个要在disconnect 前, disconnect会将 fd 置为-1
    m_connMgr.disconnect(s);            
}
