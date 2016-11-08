/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ServerSocket.h"

ServerSocket::ServerSocket() {

}

ServerSocket::~ServerSocket() {

}

shared_ptr<Socket> ServerSocket::accept(int32_t sockfd, string &peer) {

    struct sockaddr_in addr = {0};
    socklen_t len = sizeof (struct sockaddr_in);
    int32_t connfd = ::accept(sockfd, (struct sockaddr *) &addr, &len);

    if (connfd < 0) {
        int32_t err = getLastError();
        if (EAGAIN != err) {
            _LOGX(_ERROR, "accept[%d] fail", sockfd);
        }
        return nullptr;
    }

    auto sock = make_shared<Socket>();   
    sock->setUp(connfd, addr);
    sock->getAddr(peer);
    return sock;

}

void
ServerSocket::listen(int32_t fd) {
    int32_t ret = -1;
    ret = ::listen(fd, LISTEN_BACKLOG);
    if (0 != ret) {
        _LOGX(_ERROR, "listen socket[%d] fail", fd);
        exit(-1);
    }
    return;

}