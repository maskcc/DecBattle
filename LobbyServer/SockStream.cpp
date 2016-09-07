/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "SockStream.h"
SockStream::SockStream()
{
    this->reset();
    
}
SockStream::~SockStream()
{    
    
}

/**
 * 要编写健壮的程序.
 * @return 
 */
int32_t 
SockStream::reciveMsg(int32_t fd, BaseMsg *msg)
{
    //先读取4字节长度的包头
    if(STEP_READ_SIZE == this->m_readStep)
    {
        int n = read(fd, m_stream + m_readSize, MSG_SIZE_LENGTH - m_readSize);
        
        //关闭连接的消息...n < 0 暂时还未处理!
        if( n <= 0 )  
        {//上报关闭连接的消息           
            return MSG_TYPE_DISCONNECT;
        }
        
        m_readSize += n;
        
        if( n > 0 && m_readSize < MSG_SIZE_LENGTH)
        {            
            return MSG_TYPE_MORE; //size  都没读完整            
        }
        
        //读出字符串大小
        bool ret = readInt(m_bodySize, m_stream);
        if( false == ret)
        {
            _LOG("read int fail!", _ERROR);
            this->reset();
            return ERROR_TYPE_READNUM_FAIL;
        }        
        //内存模型::
        //  _______
        // |sz|body|
        //  -------
        // sz = sizeof(body)

        //修改接收状态
        this->m_readStep = STEP_READ_BODY;
        this->m_readSize = 0;
        
        //将缓冲区清理, 这里只填写了前面4个字节
        memset(m_stream, 0, MSG_SIZE_LENGTH);
        
        return 0;
    }
    
    //读取body
    int n = read(fd, m_stream + m_readSize, m_bodySize - m_readSize);
    if (n <= 0)
    {           
        return MSG_TYPE_DISCONNECT;        
    }
    
    m_readSize += n;
    if(0 < m_bodySize - m_readSize)
    {        
        return MSG_TYPE_MORE; //m_sizeToRead  都没读完整           
    }
    
    msg = static_cast<BaseMsg*>(malloc(sizeof(BaseMsg_t)));
    msg->msg = malloc(m_bodySize);
    memcpy(msg->msg, this->m_stream, m_bodySize);
    msg->sz = m_bodySize;
    char buff[1024] = {0};
    snprintf(buff, 1024, "recived msg, msg size[%d] msg msg[%s]", msg->sz, (char*)msg->msg);
    _LOG(buff, _WARN);
    
    
    //还要将消息加入特定的队列中, 也可以将消息写成自解析类
    
    
    this->reset(); 
    
    return 0;
    
}

int32_t 
SockStream::reset()
{
    m_bodySize = 0;   //包体长度
    m_readStep = STEP_READ_SIZE;  //当前读取进度
    m_readSize = 0;  //已经读取的长度
    memset(m_stream, 0, sizeof(BUFF_LENGTH));
    
}
