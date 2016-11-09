/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TCPAcceptor.h
 * Author: admin
 *
 * Created on 2016年11月8日, 下午3:25
 */

#ifndef TCPACCEPTOR_H
#define TCPACCEPTOR_H

#include "IOComponent.h"

class TCPAcceptor
: public IOComponent {
public:
    virtual void readHandler(shared_ptr<Socket> sock);
};

#endif /* TCPACCEPTOR_H */

