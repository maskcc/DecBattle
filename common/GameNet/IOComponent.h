/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IOComponent.h
 * Author: admin
 *
 * Created on 2016年11月8日, 下午2:09
 */

#ifndef IOCOMPONENT_H
#define IOCOMPONENT_H

#include <memory>
#include <map>
#include "Socket.h"

using namespace std;
class Socket;
class IOComponent {
public:
    IOComponent();
    ~IOComponent();
    
    virtual void readHandler(shared_ptr<Socket> sock);
    virtual void writeHandler(shared_ptr<Socket> sock);
    
private:
    

};


#endif /* IOCOMPONENT_H */

