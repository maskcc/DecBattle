/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Socket.h"
Socket::Socket()
{
    m_fd = -1;
    m_addr = "";
    m_lastRecvTime = 0;
    
}

int32_t 
Socket::init(int32_t fd)
{
    m_fd = fd;    
    return 0;
}

int32_t 
Socket::closeHandle()
{//要考虑断开连接时的处理, 断开连接时, buff要清空
    close(this->m_fd);    
    return 0;
}
int32_t 
Socket::getFD() const
{
    return m_fd;
}


int32_t 
Socket::readHandle()
{
    int ret = -1;
    BaseMsg *msg = NULL;
    ret = m_stream.reciveMsg(this->m_fd, msg);
    m_lastRecvTime = time(NULL);
    
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

//重载等于运算符
//这里重载等于运算符需要学习一下
//http://blog.163.com/zhangjie_0303/blog/static/99082706201191311147901
//http://www.cppblog.com/doing5552/archive/2011/02/15/140098.html
bool 
operator==(const Socket &lsh, const Socket& rhs)
{
    return lsh.getFD() == rhs.getFD();
    
}


//重载不等于运算符
bool 
operator!=(const Socket &lsh, const Socket& rhs)
{
    return !(lsh == rhs);
    
}

