/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "DataBuffer.h"

DataBuffer::DataBuffer() {
    m_start = nullptr;
    m_end = nullptr;
    m_data = nullptr;
    m_free = nullptr;
}

DataBuffer::~DataBuffer() {

    destroy();
}

void
DataBuffer::destroy() {
    free(m_start);
}

//读出长度为len的数据, 该数据读出后内存空间可用

void
DataBuffer::drainData(uint32_t len) {
    m_data += len;

    //里面的数据都读完了, 从头开始缓存
    if (m_data >= m_free) {
        clear();
    }
}

//存入数据后, 还要移动坐标

void
DataBuffer::pourData(uint32_t len) {
    assert(m_end - m_free > len);
    m_free += len;

}

//撤销写入数据, 例如出现错误后撤销写入

void DataBuffer::stripData(uint32_t len) {
    //撤销长度过大, 程序使用错误, 撤销数据过大
    assert(m_free - m_data >= len);
    m_free -= len;

}

unsigned char*
DataBuffer::getStart() {
    return m_start;
}

unsigned char*
DataBuffer::getData() {
    return m_data;
}

unsigned char*
DataBuffer::getFree() {
    return m_free;
}

void
DataBuffer::ensureFree(uint32_t len) {
    expand(len);
}

uint32_t DataBuffer::getFreeLen() {
    return static_cast<uint32_t> (m_end - m_free);
}

void
DataBuffer::expand(uint32_t need) {

    if (nullptr == m_start) {
        uint32_t sz = calSize(need);
        m_start = (unsigned char*) malloc(sz);
        //malloc 失败
        assert(m_start != nullptr);
        m_data = m_free = m_start;
        m_end = m_start + sz;

        return;
    }

    //可以直接使用的长度
    uint32_t freelen = static_cast<uint32_t> (m_end - m_free);

    if (freelen >= need) {
        return;
    }

    //还未读取数据长度
    uint32_t dlen = static_cast<uint32_t> (m_free - m_data);
    //total free 长度(已经不需要的数据 + free空间)大于需要的长度(所在的4的倍数范围内)
    uint32_t tflen = freelen + static_cast<uint32_t> (m_data - m_start);
    //当前空余空间(已经取了数据的 + free的空间)够使用
    if (tflen >= need) {
        memmove(m_start, m_data, dlen);
        m_data = m_start;
        m_free = m_start + dlen;
        return;
    }

    //需要的空间比现在可用空间大     
    uint32_t expandsz = calSize(dlen + need);
    unsigned char *newbuf = (unsigned char*) malloc(expandsz);
    //malloc 失败
    assert(newbuf != nullptr);

    if (dlen > 0) {
        memcpy(newbuf, m_data, dlen);
    }
    free(m_start);
    m_start = newbuf;
    m_data = m_start;
    m_free = m_start + dlen;
    m_end = m_start + expandsz;

}


//数据错乱, 需要清除
//可能使用错误, 写入数据后没有改变写入锚点

void
DataBuffer::clear() {
    m_data = m_free = m_start;
}

void
DataBuffer::writeInt8(uint8_t n) {
    expand(1);
    *m_free = static_cast<unsigned char> (n);
    m_free++;

}

void
DataBuffer::writeInt16(uint16_t n) {
    expand(2);
    //读出低八位
    m_free[1] = static_cast<unsigned char> (n);

    //读出高八位
    n >>= 8;
    m_free[0] = static_cast<unsigned char> (n);
    m_free += 2;

}

void
DataBuffer::writeInt32(uint32_t n) {
    expand(4);

    m_free[3] = static_cast<unsigned char> (n);
    n >>= 8;
    m_free[2] = static_cast<unsigned char> (n);
    n >>= 8;
    m_free[1] = static_cast<unsigned char> (n);
    n >>= 8;
    m_free[0] = static_cast<unsigned char> (n);

    m_free += 4;

}

void
DataBuffer::writeInt64(uint64_t n) {
    expand(8);

    m_free[7] = static_cast<unsigned char> (n);
    n >>= 8;
    m_free[6] = static_cast<unsigned char> (n);
    n >>= 8;
    m_free[5] = static_cast<unsigned char> (n);
    n >>= 8;
    m_free[4] = static_cast<unsigned char> (n);


    m_free[3] = static_cast<unsigned char> (n);
    n >>= 8;
    m_free[2] = static_cast<unsigned char> (n);
    n >>= 8;
    m_free[1] = static_cast<unsigned char> (n);
    n >>= 8;
    m_free[0] = static_cast<unsigned char> (n);

    m_free += 8;

}

void
DataBuffer::writeBytes(const void* src, uint32_t len) {
    expand(len);
    assert(nullptr != src);
    memcpy(m_free, src, len);
    m_free += len;    
}

uint8_t DataBuffer::readUInt8() {
    return (*m_data++);
}

uint16_t DataBuffer::readUInt16() {
    uint16_t n = m_data[0];
    n <<= 8;
    n = static_cast<uint16_t> (n | m_data[0]);
    
    assert(m_free >= m_data);
    m_data += 2;
    return (n);
}

uint32_t DataBuffer::readUInt32() {
    uint32_t n = 0;

    n = m_data[0];
    n <<= 8;
    n |= m_data[1];
    n <<= 8;
    n |= m_data[2];
    n <<= 8;
    n |= m_data[3];
    
    assert(m_free >= m_data);
    m_data += 4;
    return n;
}

uint64_t DataBuffer::readUInt64() {
    uint64_t n = 0;

    n |= m_data[0];
    n <<= 8;
    n |= m_data[1];
    n <<= 8;
    n |= m_data[2];
    n <<= 8;
    n |= m_data[3];
    n <<= 8;
    n |= m_data[4];
    n <<= 8;
    n |= m_data[5];
    n <<= 8;
    n |= m_data[6];
    n <<= 8;
    n |= m_data[7];

    assert(m_free >= m_data);
    m_data += 8;
    return (n);
}

bool DataBuffer::readBytes(void* dst, uint32_t len)
{
    if(m_data + len > m_free)
    {
        return false;
    }
    
    memcpy(dst, m_data, len);
    m_data += len;
    assert(m_free >= m_data);
    return true;
    
}
int8_t DataBuffer::readInt8() {
    return readUInt8();
}

int16_t DataBuffer::readInt16() {
    return readUInt16();
}

int32_t DataBuffer::readInt32() {
    return readUInt32();
}

int64_t DataBuffer::readInt64() {
    return readUInt64();
}
