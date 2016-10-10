/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SockServer.h"
#include "MQueue.h"
#include "GlobalQueue.h"
#include "ContextMap.h"
#include "ParseQueue.h"

uint32_t SockServer::HANDLER = 0;
SockServer* SockServer::ins =  new SockServer;
SockServer* SockServer::getInstance()
{
    return ins;
}

int32_t SockServer::getSendFD()
{
    return m_sendctrFD;    
}
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
 SockServer::initServer(Addr *addr)
 {   
    m_readctrFD = addr->fd[0];
    m_sendctrFD = addr->fd[1];
    if(0 != this->initEPoll())
    {
        return -1;
    }    
    
    if (0 != sp_add(m_epollFD, m_readctrFD, NULL))
    {        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "epoll open fail!");
        return -1;
    }
     
    
     
    return 0;
 }
 
 
 int32_t 
 SockServer::addListen(const char* listenip, int32_t port)
 {     
     /*start listen port*/
    int32_t sockfd = sp_socket();
    
    //监听错误会退出
    sp_bindListen(sockfd, listenip, port);
    
    //监听端口Socket的idx和ConnectionMgr的意义不同
    uint32_t idx = (++HANDLER) % MAX_SOCKET_COUNT;
    
    Socket *sock = new Socket;
    sock->init(sockfd, idx,CONN_TYPE_NONE, listenip);
    sp_nonblocking(sock->getFD());
    
    m_listenSock.push_back(sock);
     
    //sp_add 的userdata不要是栈上的数据, m_listenSock.back()返回的是刚推入数据的引用)
    if (0 != sp_add(m_epollFD, sock->getFD(), (void *)m_listenSock.back()))    
    {        
            __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "epoll open fail!");
            return -1;
    }
    return 0;
 }
 
 int32_t 
 SockServer::initEPoll()
 {   
    /*init epoll server*/
    
    m_epollFD = sp_create(MAX_SOCKET_COUNT);  
    
    m_checkCtr = 1;
    FD_ZERO(&m_rfds);
    
    for(int c = 0; c < m_listenSock.size(); c++)
    {
        if (0 != sp_add(m_epollFD, m_listenSock[c]->getFD(), (void *)m_listenSock[c]))    
        {        
            __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "epoll open fail!");
            return -1;
        }
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
        if(m_checkCtr)
        {
            if(hasCmd())
            {
                ctrlCmd();
            }
            else
            {
                m_checkCtr = 0;
            }
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
                m_checkCtr = 1;
                __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "socket is null, the pipe msg come");
                
                //这里s == NULL 表示有管道信息到来
                continue;
            }

            if(e->read)
            {
                int32_t ilisten = isListener(s);
                if(1 == ilisten)                    
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
                    
                    __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "Acceept succeed, connidx[%d],connfd is[%d] remote ip[%s] and now connection count is[%d]", 
                                client->getIdx(),client->getFD(), client->getAddr() ,m_connMgr.getConnectionCount());
                    
                    if(0 != sp_add(m_epollFD, client->getFD(), (void*)client))
                    {
                        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "epoll add ctl fail!");
                        client->reset();
                        //错误处理??
                        //return ERROR_TYPE_ADDCTL_FAIL;
                    }
                    
                }   
                else if(0 == ilisten)
                {
                    //有消息到来, 将消息接收完成后会new 一个MsgBase      
                    MsgBase *msg = NULL;
                    int readret = m_connMgr.receiveMsg(s, msg);
                    
                    //读取出现错误
                    if( readret < 0 )
                    {
                         disconnect(s);  
                         SAFEDEL(msg);
                        _LOGX(_DEBUG,  "read sock error errno[%d], close peer.now connection count[%d]", 
                                readret, m_connMgr.getConnectionCount());
                        continue;
                        
                    }
                    if( readret == MSG_TYPE_DISCONNECT)
                    {
                         disconnect(s); 
                         SAFEDEL(msg);
                        _LOGX(_DEBUG, "connection has been closed by peer! now connection count[%d]",
                               m_connMgr.getConnectionCount() );
                        continue;

                    } 
                    if( readret == ERROR_TYPE_BODY_OVER_FLOW)  
                    {
                        disconnect(s); 
                        SAFEDEL(msg);
                        _LOGX(_DEBUG,  "read body size over flow.now connection count[%d]",
                                 m_connMgr.getConnectionCount());
                        continue;
                    }
                    
                    if( MSG_TYPE_MORE == readret)
                    {
                        //还没有读完
                        continue;
                    }
                    
                    //处理消息
                    if(NULL != msg)
                    {//这个应该在别的地方将其转换成内部队列
                        ParseQueue::getInstance()->push(msg);
                        

                    }
                } 
                else
                {
                    _LOGX(_ERROR, "socket isListener not right ilisten[%d]", ilisten);
                }
            }
            if(e->write)
            {            
                m_connMgr.sendMsg(s);
                //sp_write(m_epollFD, client->getFD(), client, true);
               //     write(client->getFD(), "goodjob", 8);
                __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "write something to far!");

            }    
        }        
     }
 }
 
void 
SockServer::disconnect(Socket *s)
{
    sp_del(m_epollFD, s->getFD());//这个要在disconnect 前, disconnect会将 fd 置为-1
    m_connMgr.disconnect(s);            
}

int32_t    
SockServer::isListener(const Socket* s)
{
    
     
    if (NULL == s )
    {        
        return ERROR_TYPE_NULL_SOCKET;
    }
    
    //CONN_TYPE_NONE 表示这是监听socket 
    //如果不是监听socket, 就表示是和其他服务器连接的或者客户端的连接  
    if(CONN_TYPE_NONE != s->getType() )
    {        
        //返回0 表示不是连接接收者
        return 0;
    }
    for(int c = 0; c < m_listenSock.size(); c++)
    {
        if(m_listenSock[c] == s)
        { 
            //是监听连接的端口
            return 1;
        }
    }    
    return ERROR_TYPE_NOT_LISTEN_NOR_ACCEPT;
}

bool
SockServer::hasCmd() 
{
    struct timeval tv = {0, 0};
    int retval;

    FD_SET(m_readctrFD, &m_rfds);

    retval = select(m_readctrFD + 1, &m_rfds, NULL, NULL, &tv);
    if (retval == 1) {
        return true;
    }
    return false;
}
void 
SockServer::ctrlCmd()
{
    uint8_t buffer[256];
    uint8_t header[2];
    blockReadpipe(header, sizeof (header));
    int type = header[0];
    int len = header[1];
    blockReadpipe(buffer, len);
    
    switch(type)
    {
        case 'K':
        {
            request_close *close = (request_close*)buffer;
            Socket *s = m_connMgr.getPeer(close->idx);
            this->disconnect(s);            
        }
            break;
        case 'S':
        {
            request_start *conf = (request_start*)buffer;
            
            this->addListen(conf->ip, conf->port);            
        }
            break;
        default:
            break;
    }
    
}

void
SockServer::blockReadpipe(void *buffer, int sz) {
    for (;;) 
    {
        int n = read(m_readctrFD, buffer, sz);
        if (n < 0) 
        {
            if (errno == EINTR)
                continue;
            
            _LOG(_ERROR, "block read pipe error");
            return;
        }
        // must atomic read from a pipe
        if(n != sz)
        {
            _LOG(_ERROR, "receive pipe msg error");
            exit(-1);
        }
        
        return;
    }
}