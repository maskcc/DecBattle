/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Socket.h"


int32_t 
Socket::init(int32_t connfd)
{
    m_fd = connfd;
    return 0;
}

int32_t 
Socket::closeHandle()
{//要考虑断开连接时的处理, 断开连接时, buff要清空
    close(this->m_fd);    
    return 0;
}
int32_t 
Socket::getFD()
{
    return m_fd;
}


int32_t 
Socket::readHandle()
{
    int ret = -1;
    BaseMsg *msg = NULL;
    ret = m_stream.reciveMsg(this->m_fd, msg);
    
    //接收到了完整的包, 需要将包发送到某个处理队列中去
    if(0 == ret)
    {
        
        return 0;
    }
    
    return ret;
    
}


int32_t 
Socket::writeHandle()
{
    int ret = -1;
   
    
    return ret;
    
}

