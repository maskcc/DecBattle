/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "GlobalQueue.h"

GlobalQueue* GlobalQueue::m_instance = NULL;

GlobalQueue* 
GlobalQueue::getInstance()
{
    if(NULL ==m_instance)
    {
        m_instance = new GlobalQueue;
    }
    return m_instance;
        
    
}

 GlobalQueue::GlobalQueue()
 {
     
 }
GlobalQueue:: ~GlobalQueue()
 {
     
 }
