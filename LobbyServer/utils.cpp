/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "utils.h"


bool 
readInt(int32_t& ret, char* stream)
{
    ret = ntohl(*(int32_t*)stream);
    return true;
    
}

bool 
readShort(uint16_t& ret, char* stream)
{
    ret = ntohl(*(uint16_t*)stream);
    return true;
    
}
