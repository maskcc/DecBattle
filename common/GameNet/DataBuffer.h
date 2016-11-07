/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataBuffer.h
 * Author: admin
 *
 * Created on 2016年11月4日, 下午5:30
 */

#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
const int32_t MAX_BUFF_BLOCK = 2048;
const int32_t MAX_RW_BUFFER = 8192;

//这里存储底层数据的buff使用unsigned char, 可以以signed int 存储 int型数据, 
//只是根据读出时候讲signed 转换成 int型即可读出包含负数的整数 

//读取写入数据按照网络字节序(大端)
//读出的数据是小端数据
class DataBuffer
{
public:
    DataBuffer();
    ~DataBuffer();
public:
    /**对流进行操作*/
    void drainData(uint32_t len);
    void pourData(uint32_t len);
    void stripData(uint32_t len);
    unsigned char* getStart();
    unsigned char* getData();
    unsigned char* getFree();
    void ensureFree(uint32_t len);    
    void destroy();
    uint32_t getFreeLen();
    
    
    //对流上的数据进行操作
    int32_t getData(int32_t len, char*);
    
    
    //写入缓冲区
    void writeInt8(uint8_t n);
    void writeInt16(uint16_t n);
    void writeInt32(uint32_t n);
    void writeInt64(uint64_t n);
    void writeBytes(const void* src, uint32_t len);
    
    //从缓冲区读出
    uint8_t readUInt8();
    uint16_t readUInt16();
    uint32_t readUInt32();
    uint64_t readUInt64();
    
    int8_t readInt8();
    int16_t readInt16();
    int32_t readInt32();
    int64_t readInt64();
    bool readBytes(void* dst, uint32_t len);
    
    //扩展到need sz
    
    bool shrink(); //自动收缩
    
private:
    void expand(uint32_t need);
    void clear();
    
    inline uint32_t calSize(uint32_t len){
        int origin = 256;
        while(len > origin){
            origin <<= 1;
        }
        return origin;
    }
    
private:
    unsigned char *m_start, *m_end;  //m_start 内存起始点, m_end 内存终结边界
    unsigned char *m_data, *m_free;  //m_data 当前读取数据的头结点, m_free 存入数据的初始指针
};

#endif /* DATABUFFER_H */

