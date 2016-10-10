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
SockStream::reciveMsg(int32_t fd, MsgBase* &msg)
{
    //先读取4字节长度的包头
    if(STEP_READ_SIZE == this->m_readStep)
    {
        int n = read(fd, m_headBuf + m_readSize, MSG_SIZE_LENGTH - m_readSize);
        
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
        memset(&m_head, 0, MSG_SIZE_LENGTH);
        m_head = *((MsgHeadDef*)&m_headBuf);
        m_head.cMsgType = ntohs(m_head.cMsgType);
        m_head.length = ntohs(m_head.length);
        m_bodySize =  m_head.length - MSG_SIZE_LENGTH;
        
        if(m_bodySize > BUFF_LENGTH || m_bodySize < 0)
        {            
            _LOGX(_WARN, "read body size over flow or body size not right! m_head.length[%d]", m_head.length);
            this->reset();
            return ERROR_TYPE_BODY_OVER_FLOW;  //包体超过缓冲区, 客户端不可能发送这么大的包体, 错误
                                               //防止发送大包体导致内存超标 
        }
      
        //修改接收状态
        this->m_readStep = STEP_READ_BODY;
        this->m_readSize = 0;
       
    }
    
    if( STEP_READ_BODY != this->m_readStep )
    {
        //包体读取错误, 重新连接
        _LOG(_ERROR, "read buff error, step not right");
        this->reset();
        return MSG_TYPE_DISCONNECT;
           
    }
    
    //将缓冲区清理
    m_stream.clear();
    m_stream.resize(m_bodySize);
    
    //读取body, 当有不是只发送头时
    int n = 0;
    if(0 != m_bodySize)
    {
        n = read(fd, &m_stream[0] + m_readSize, m_bodySize - m_readSize);
        if (n <= 0)
        {           
            return MSG_TYPE_DISCONNECT;        
        }
    }
    
    m_readSize += n;
    if(0 < m_bodySize - m_readSize)
    {        
        return MSG_TYPE_MORE; //m_sizeToRead  都没读完整           
    }
    
    msg = new MsgBase;
    msg->msg.assign(m_stream.begin(), m_stream.end());
    memcpy(&msg->head, &m_head, MSG_SIZE_LENGTH);   
  
    __log(_DEBUG, __FILE__, __LINE__, __FUNCTION__, "recived msg, msg size[%d] type[%d]", msg->head.length, msg->head.cMsgType);
    
    this->reset(); 
    return 0;
    
}

int32_t 
SockStream::reset()
{
    m_bodySize = 0;   //包体长度
    m_readStep = STEP_READ_SIZE;  //当前读取进度
    m_readSize = 0;  //已经读取的长度
    m_stream.clear();
    memset(m_headBuf, 0, sizeof(BUFF_LENGTH));
      
}
