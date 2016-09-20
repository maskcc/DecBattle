/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: admin
 *
 * Created on 2016年9月1日, 上午11:29
 */

#include <cstdlib>
#include <dlfcn.h>
#include <signal.h>
#include "LobbyServer.h"



using namespace std;

/*
 * 
 */
void handler(int h)
{
    __log(_WARN, __FILE__, __LINE__, __FUNCTION__, "signal receive [%d]", h);
    
}

int main(int argc, char** argv) 
{
    signal(SIGINT, handler);
    signal(SIGPIPE, handler);
    LobbyServer s;
    s.start();
    
    
    return 0;
}

