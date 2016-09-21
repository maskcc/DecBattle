/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.h
 * Author: admin
 *
 * Created on 2016年9月1日, 上午11:37
 */

#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <errno.h>
#include "lua.hpp"

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

    
const int _DEBUG = 1;   // green
const int _WARN = 2;  //yellow
const int _ERROR = 4; //red
    
    
    static void lualog( char const*filename,  char const*funcname, char const*msg, int level );
//    static void log( char const*filename,  char const*funcname, int line,   char const*msg, int level  = _DEBUG )
//    {
//        char buff[1024] = {0};
//        char timestamp[128] = {0};
//         time_t stamp = time(NULL);
//        const char *timestr = ctime(&stamp);
//        memcpy(timestamp, timestr, strlen(timestr) - 1);        
//        //strftime(s, 1000, "%A, %B %d %Y", p);
//        
//        switch (level)
//        {
//            case _DEBUG:
//                snprintf(buff, 1024, "%s[%s] [%s]:[%d] [%s] MSG[%s]%s", GREEN, timestamp,filename, line, funcname, msg, NONE);
//                break;
//            case _WARN:
//                snprintf(buff, 1024, "%s[%s] [%s]:[%d] [%s] MSG[%s]%s", YELLOW, timestamp,filename, line, funcname, msg, NONE);
//                break;
//            case _ERROR:
//                snprintf(buff, 1024, "%s[%s] [%s]:[%d] [%s] MSG[%s] errno[%d], error[%s]%s", L_RED, timestamp,filename, line, 
//                         funcname, msg,errno, strerror(errno), NONE);
//                break;
//            default:
//                snprintf(buff, 1024, "%s[%s] [%s]:[%d] [%s] MSG[%s] errno[%d], error[%s]%s", BLINK, timestamp,filename, line, 
//                         funcname, msg, errno, strerror(errno),NONE);
//        }
//
//        std::cout << buff << std::endl;   
//    
//    }
}
#define _LOG(msg,l) (LOG::log(__FILE__, __FUNCTION__, __LINE__, msg, l)) 



int
llog(lua_State *L)
{
    const char *file = lua_tostring(L, 1);
    const char *func = lua_tostring(L, 2);
    const char *msg = lua_tostring(L, 3);
    int   level = lua_tointeger(L, 4);
    LOG::lualog(file ,func, msg, level);  
    return 0;
    
}
extern "C"
int luaopen_lobbylib_utils(lua_State *L)
{
    luaL_Reg l[] = {
        { "log", llog },        
        
        { NULL, NULL },
    };
    
    
    luaL_newlibtable(L, l);   
      
    luaL_setfuncs(L, l, 0);
    return 1;
}
#endif /* UTILS_H */

