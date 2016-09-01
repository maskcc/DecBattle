/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "utils.h"


static void 
LOG::lualog( char const*filename,  char const*funcname, char const*msg, int level )
{
    char buff[1024] = {0};
    
    switch (level)
    {
        case _DEBUG:
            snprintf(buff, 1024, "%s[%s:%s] MSG[%s]%s", GREEN, filename, funcname, msg, NONE);
            break;
        case _WARN:
            snprintf(buff, 1024, "%s[%s:%s] MSG[%s]%s", YELLOW, filename,funcname, msg, NONE);
            break;
        case _ERROR:
            snprintf(buff, 1024, "%s[%s:%s] MSG[%s]%s", L_RED, filename, funcname, msg, NONE);
            break;
        default:
            snprintf(buff, 1024, "%s[%s:%s] MSG[%s]%s", BLINK, filename,funcname, msg, NONE);
    }
    
    std::cout << buff << std::endl;   
    
}
