/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "utils.h"
#include <time.h>




static void 
LOG::lualog( char const*filename,  char const*funcname, char const*msg, int level )
{
    char buff[1024] = {0};
    char timestamp[128] = {0};
    time_t stamp = time(NULL);
    const char *timestr = ctime(&stamp);
    memcpy(timestamp, timestr, strlen(timestr) - 1);        

    switch (level)
    {
        case _DEBUG:
            snprintf(buff, 1024, "%s[%s] [%s:%s] MSG[%s]%s", GREEN, timestamp, filename, funcname, msg, NONE);
            break;
        case _WARN:
            snprintf(buff, 1024, "%s[%s] [%s:%s] MSG[%s]%s", YELLOW, timestamp,filename,funcname, msg, NONE);
            break;
        case _ERROR:
            snprintf(buff, 1024, "%s[%s] [%s:%s] MSG[%s]%s", L_RED, timestamp,filename, funcname, msg, NONE);
            break;
        default:
            snprintf(buff, 1024, "%s[%s] [%s:%s] MSG[%s]%s", BLINK, timestamp,filename,funcname, msg, NONE);
    }
    
    std::cout << buff << std::endl;   
    
}
