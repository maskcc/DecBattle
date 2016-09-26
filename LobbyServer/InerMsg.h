/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InerMsg.h
 * Author: admin
 *
 * Created on 2016年9月26日, 下午1:54
 */

#ifndef INERMSG_H
#define INERMSG_H
#include <string>
#include <stdint.h>


class InerMsg
{
public:
    std::string service;  //服务id, 目的服务地址
    std::string source;   //源id 
    uint32_t type;     // 内部消息还是外部消息
    uint32_t sz;
    std::string msg;
    InerMsg()
    {
        type = 0;
        sz = 0;
    }
    ~InerMsg()
    {
                
    }
    
};

#endif /* INERMSG_H */

