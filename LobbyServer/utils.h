/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.h
 * Author: admin
 *
 * Created on 2016年9月1日, 下午3:14
 */

#ifndef UTILS_H
#define UTILS_H
#include <cstring>
#include <iostream>
#include "GameDef.h"
#include <errno.h>
#include <netinet/in.h>

namespace LOG{
    #define NONE                 "\e[0m"
    #define BLACK                "\e[0;30m"
    #define L_BLACK              "\e[1;30m"
    #define RED                  "\e[0;31m"
    #define L_RED                "\e[1;31m"
    #define GREEN                "\e[0;32m"
    #define L_GREEN              "\e[1;32m"
    #define BROWN                "\e[0;33m"
    #define YELLOW               "\e[1;33m"
    #define BLUE                 "\e[0;34m"
    #define L_BLUE               "\e[1;34m"
    #define PURPLE               "\e[0;35m"
    #define L_PURPLE             "\e[1;35m"
    #define CYAN                 "\e[0;36m"
    #define L_CYAN               "\e[1;36m"
    #define GRAY                 "\e[0;37m"
    #define WHITE                "\e[1;37m"

    #define BOLD                 "\e[1m"
    #define UNDERLINE            "\e[4m"
    #define BLINK                "\e[5m"
    #define REVERSE              "\e[7m"
    #define HIDE                 "\e[8m"
    #define CLEAR                "\e[2J"
    #define CLRLINE              "\r\e[K" //or "\e[1K\r"

    
    static void log( char const*filename,  char const*funcname, int line,   char const*msg, int level  = _DEBUG )
    {
        char buff[1024] = {0};
        char timestamp[128] = {0};
         time_t stamp = time(NULL);
        const char *timestr = ctime(&stamp);
        memcpy(timestamp, timestr, strlen(timestr) - 1);        
        //strftime(s, 1000, "%A, %B %d %Y", p);
        
        switch (level)
        {
            case _DEBUG:
                snprintf(buff, 1024, "%s[%s] [%s]:[%d] [%s] DEBUG[%s]%s", GREEN, timestamp,filename, line, funcname, msg, NONE);
                break;
            case _WARN:
                snprintf(buff, 1024, "%s[%s] [%s]:[%d] [%s] WARN[%s]%s", YELLOW, timestamp,filename, line, funcname, msg, NONE);
                break;
            case _ERROR:
                snprintf(buff, 1024, "%s[%s] [%s]:[%d] [%s] ERROR[%s] errno[%d], error[%s]%s", L_RED, timestamp,filename, line, \
                         funcname, msg,errno, strerror(errno), NONE);
                break;
            default:
                snprintf(buff, 1024, "%s[%s] [%s]:[%d] [%s] DEFAULT[%s] errno[%d], error[%s]%s", BLINK, timestamp,filename, line, \
                         funcname, msg, errno, strerror(errno),NONE);
        }

        std::cout << buff << std::endl;   
    
    }
    
}

#define _LOG(msg,l) (LOG::log(__FILE__, __FUNCTION__, __LINE__, msg, l)) 

//以网络字节序读出一个整型
bool readInt(int32_t& ret, char* stream);


#endif /* UTILS_H */

