/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SocketEPoll.h
 * Author: admin
 *
 * Created on 2016年9月19日, 上午10:14
 */

#ifndef SOCKETEPOLL_H
#define SOCKETEPOLL_H


#include <netdb.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "utils.h"
#include "GameDef.h"

//成功返回sockfd, 失败退出进程
static int32_t
sp_socket() {
    int32_t sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "SOCKET fail, sockfd is[%d]", sockfd);
        exit(-1);
    }
    
    return sockfd;
}

//失败退出进程
static void
sp_bindListen(int32_t sockfd, char* listenip, int32_t port) {    
    struct sockaddr_in servaddr = {0};   
    socklen_t addrlen = sizeof(servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port =  htons(port);
    
    if(0 == inet_aton(listenip, &servaddr.sin_addr))
    {        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "server ip configer is not right!");
         exit(-1);
    }
    if(0 != bind(sockfd, (struct sockaddr* )&servaddr, addrlen))
    {        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "bind failed!");
        exit(-1);
    }
    if(0 != listen(sockfd, MAX_BACK_LOG))
    {        
        __log(_ERROR, __FILE__, __LINE__, __FUNCTION__, "listen failed!");
        exit(-1);
    }   
   
}
static bool 
sp_invalid(int32_t efd) {
	return efd == -1;
}

static int32_t
sp_create(int32_t c) {
	return epoll_create(c);
}

static void
sp_release(int32_t efd) {
	close(efd);
}

static int32_t 
sp_add(int32_t efd, int32_t sock, void *ud) {
	EPOLL_EV ev;
	ev.events = EPOLLIN;
	ev.data.ptr = ud;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, sock, &ev) == -1) {
		return 1;
	}
	return 0;
}

static int32_t 
sp_del(int32_t efd, int sock) {
	epoll_ctl(efd, EPOLL_CTL_DEL, sock , NULL);
}

static void 
sp_write(int32_t efd, int32_t sock, void *ud, bool enable) {
	EPOLL_EV ev;
	ev.events = EPOLLIN | (enable ? EPOLLOUT : 0);
	ev.data.ptr = ud;
	epoll_ctl(efd, EPOLL_CTL_MOD, sock, &ev);
}

static int32_t 
sp_wait(int32_t efd, event *e, int32_t max) {
	EPOLL_EV ev[max];
	int n = epoll_wait(efd , ev, max, -1);
	int i;
	for (i=0;i<n;i++) {
		e[i].s = ev[i].data.ptr;
		unsigned flag = ev[i].events;
		e[i].write = (flag & EPOLLOUT) != 0;
		e[i].read = (flag & EPOLLIN) != 0;
	}

	return n;
}

static void
sp_nonblocking(int32_t fd) {
	int32_t flag = fcntl(fd, F_GETFL, 0);
	if ( -1 == flag ) {
		return;
	}

	fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

#endif /* SOCKETEPOLL_H */

