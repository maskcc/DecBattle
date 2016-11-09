/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Socket.h"

Socket::Socket() {
    memset(&m_addr, 0, sizeof (sockaddr_in));
    m_sock = -1;
}

Socket::~Socket() {

}


bool Socket::connect(const string& addr, unsigned short port) {
    this->init();
    struct sockaddr_in connAddr = {0};
    connAddr.sin_family = SOCK_STREAM;
    connAddr.sin_port = htons(port);
    if (0 == inet_aton(addr.c_str(), &connAddr.sin_addr)) {
        _LOGX(_ERROR, "inet_aton fail, sock addr is not right [%s] ", addr.c_str());
        return false;
    }
    socklen_t sz = sizeof (connAddr);
    int32_t ret = ::connect(m_sock, (struct sockaddr*) &connAddr, sz);
    if (-1 == ret) {
        _LOG(_ERROR, "connect fail");
        return false;
    }
    return true;
}

void Socket::close(){
    if( -1 != m_sock){
        ::close(m_sock);
        m_sock = -1;
    }
}

void Socket::shutdown(){
    if( -1 != m_sock){
        ::shutdown(m_sock, SHUT_WR);
    }
}

int32_t Socket::write(const void *data, int len){
    if( -1 == m_sock){
        return -1;
    }
    
    int32_t res = 0;
    do{
        res = ::write(m_sock, data, len);
        if(res > 0){
            NW_COUNT_DATA_WRITE(res);
        }
    }while(res < 0 && errno == EINTR);
    
    return res;
}

int32_t Socket::read(void *data, int len){
    if( -1 == m_sock){
        return -1;
    }
    
    int32_t res = 0;
    do{
        res = ::read(m_sock, data, len);
        if(res > 0){
                NW_COUNT_DATA_READ(res);
        }
    }while(res < 0 && errno == EINTR);
    
    return res;
}

bool Socket::setSoBlocking(bool block){
    bool rc = false;
    this->init();    
    int32_t flags = fcntl(m_sock, F_GETFL, NULL);
    if( flags >= 0 ){
        if(block){
            flags &= ~O_NONBLOCK; // clear blocking
        }else{
            flags |= O_NONBLOCK;
        }
    }
    if(fcntl(m_sock, F_SETFL, flags) >= 0){
        rc = true;
    }
        
    return rc;
}
void Socket::setUp(int32_t fd, struct sockaddr_in addr) {
    m_sock = fd;
    memcpy(&m_addr, &addr, sizeof(struct sockaddr_in));
    
}

int32_t Socket::getSockFD(){
    return m_sock;
}
shared_ptr<IOComponent> Socket::getIOComponent(){
    return m_ioComponent;
}

int32_t Socket::getLastError() {
    return errno;
}

void Socket::getAddr(string &addr) {
    char dest[32];
    unsigned long ad = ntohl(m_addr.sin_addr.s_addr);
    sprintf(dest, "%d.%d.%d.%d:%d",
            static_cast<int32_t> ((ad >> 24) & 255),
            static_cast<int32_t> ((ad >> 16) & 255),
            static_cast<int32_t> ((ad >> 8) & 255),
            static_cast<int32_t> (ad & 255),
            ntohs(m_addr.sin_port));
}


void Socket::init() {
    if(m_sock != -1){
        return;
    }
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == m_sock) {
        _LOG(_ERROR, "socket init fail");
        exit(-1);
    }
    

}