/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Socket.h"
Socket::Socket()
{
    m_fd = -1;
    m_idx = -1;
    m_port = -1;
    m_addr = "";
    m_lastRecvTime = 0;
    m_connType = CONN_TYPE_NONE;
    
}

int32_t 
Socket::init(int32_t fd, uint32_t idx,int32_t type, string addr)
{
    m_fd = fd;    
    m_connType = type;
    m_idx = idx;
    m_addr = addr;
    return 0;
}
void
Socket::reset()
{
    m_fd = -1;
    m_idx = -1;
    m_addr = "";
    m_lastRecvTime = 0;
    m_connType = CONN_TYPE_NONE;
    
}
int32_t 
Socket::closeHandle()
{//要考虑断开连接时的处理, 断开连接时, buff要清空
    if(CONN_TYPE_NONE != this->m_connType  && -1 != this->m_fd)
    {
        close(this->m_fd);    
        reset();
        return 0;
    }    
    __log(_WARN, __FILE__, __LINE__, __FUNCTION__, "TRY to close listen fd??");
    return 0;
}
int32_t
Socket::getFD() const
{
    return m_fd;
}
int32_t
Socket::getIdx() const
{
    return m_idx;
}
int32_t
Socket::getType() const
{
    return m_connType;
}
const char*
Socket::getAddr() 
{
    return m_addr.c_str();
}

void
Socket::setIdx(int32_t idx)
{
    m_idx = idx;
}

int32_t 
Socket::readHandle(BaseMsg *&msg)
{
    int ret = -1;    
    ret = m_stream.reciveMsg(this->m_fd, msg);
    m_lastRecvTime = time(NULL);
    
    //接收到了完整的包, 需要将包发送到某个处理队列中去
    return ret;
    
}


int32_t 
Socket::writeHandle()
{
    int ret = -1;
 //   ret = m_stream.sendMsg(this->m_fd);
    
    return ret;
    
}

//重载等于运算符
//这里重载等于运算符需要学习一下
//http://blog.163.com/zhangjie_0303/blog/static/99082706201191311147901
//http://www.cppblog.com/doing5552/archive/2011/02/15/140098.html
bool 
operator==(const Socket &lsh, const Socket& rhs)
{
    return lsh.getIdx() == rhs.getIdx();
    
}


//重载不等于运算符
bool 
operator!=(const Socket &lsh, const Socket& rhs)
{
    return !(lsh == rhs);
    
}

