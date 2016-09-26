/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "NameService.h"

NameService* NameService::m_ins = NULL;
NameService::NameService()
{
    
}

NameService* 
NameService::getInstance()
{
    if(NULL == m_ins)
    {
        m_ins = new NameService();
    }
    
    return m_ins;
    
}
int32_t
NameService::reg(int32_t s, string name)
{
    if(-1 != search(name))
    {        
        __log(_WARN, __FILE__, __LINE__, __FUNCTION__, "find the repeated name service!");
        return -1; //重复注册
    }
    
    SName n;
    n.name = name;
    n.service = s;
    m_nameList.push_back(n);
    
    return 0;
}


int32_t
NameService::search(string& name)
{
    int ret = -1;
    for(int32_t c = 0; c < m_nameList.size(); c++)
    {
        if(m_nameList.at(c).name == name)
        {
            ret = m_nameList.at(c).service;
            break;
        }
    }
    
    return ret;
    
}
