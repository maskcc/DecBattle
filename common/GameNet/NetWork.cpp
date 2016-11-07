/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "NetWork.h"

CNetWork::CNetWork()
{
    
}
CNetWork::~CNetWork()
{
    
}

bool CNetWork::start()
{
    signal(SIGPIPE, SIG_IGN);
    m_timeoutThread.start(this, nullptr);
    m_rwThread.start(this, nullptr);
    return true;
}

void CNetWork::run(CThread* thread, void* arg)
{
    //超时线程
    if(thread == &m_timeoutThread)
    {
        
    }
    else if(thread == &m_rwThread)
    {
        
    }
    
}