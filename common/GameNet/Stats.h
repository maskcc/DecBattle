/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stats.h
 * Author: admin
 *
 * Created on 2016年11月8日, 下午2:40
 */

#ifndef STATS_H
#define STATS_H
#include "utils.h"
class StatCounter{
public:
    StatCounter(){clear();}
    ~StatCounter(){}
    void log(){
        _LOGX(_DEBUG, "read packet[%d] \n write packet[%d] \n \
                        read bytes[%d] \n write bytes[%d] ",
                m_packetReadCnt, m_packetWriteCnt, 
                m_dataReadCnt, m_dataWriteCnt);
    }
    
    void clear(){
        m_packetReadCnt = 0;
        m_packetWriteCnt = 0;
        m_dataReadCnt = 0;
        m_dataWriteCnt = 0;
    }
public:
    uint64_t m_packetReadCnt; //packet read
    uint64_t m_packetWriteCnt;//packet write
    uint64_t m_dataReadCnt; //bytes read
    uint64_t m_dataWriteCnt;//bytes write
    
public:
    static StatCounter gStatCounter; //全局变量
    

};

#define NW_GLOBAL_STAT StatCounter::gStatCounter
#define NW_COUNT_PACKET_READ(n) {NW_GLOBAL_STAT.m_packetReadCnt += (n);}
#define NW_COUNT_PACKET_WRITE(n) {NW_GLOBAL_STAT.m_packetWriteCnt += (n);}
#define NW_COUNT_DATA_READ(n) {NW_GLOBAL_STAT.m_dataReadCnt += (n);}
#define NW_COUNT_DATA_WRITE(n) {NW_GLOBAL_STAT.m_dataWriteCnt += (n);}
#endif /* STATS_H */

