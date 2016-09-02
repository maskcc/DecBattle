/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Socket.h
 * Author: admin
 *
 * Created on 2016年9月2日, 下午6:02
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <stdint.h>

using namespace std;
class Socket
{
public:
    
    
protected:
    string   m_addr;   //地址
    uint32_t m_port;   //端口号
    int32_t  m_fd;     //连接信息
    
    
};


#endif /* SOCKET_H */

