/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetMessageManager.h
 * Author: admin
 *
 * Created on 2016年9月30日, 上午10:50
 */

#ifndef NETMESSAGEMANAGER_H
#define NETMESSAGEMANAGER_H
#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include <stdint.h>

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cstdio>
#include <netinet/in.h>
#include <vector>
#include "utils.h"
#include "GameDef.h"
#include "ConfigMgr.h" 



class NetMessageManager
{
public:
    static NetMessageManager* getInstance();
    void loadCfg(std::string name);
    std::vector<char> readMessageByJson(const char* buf);
    string writeMessageToJson( MsgBase* q);
    std::string writeOneMessageToJson(std::vector<char>* data);
    void setMessageType(std::string msgKey,std::string msgType);
    
private:
    ~NetMessageManager();
    void readMessageByArray(const rapidjson::Value& array);
    void readMessageByObj(const rapidjson::Value& object_cfg,const rapidjson::Value& object_msg);
    void writeMessageByObj(const rapidjson::Value& object_cfg,rapidjson::Document& game_data,bool head = true);
    void writeMessageByArray(const rapidjson::Value& object_cfg,rapidjson::Document& game_data,rapidjson::Value& arrayOut);
    
    const rapidjson::Value& getMsgCfgObj(std::string msgTypeStr,int iType,int &retCode); //1是c2s 2是s2c
    int getMaxAlignmentByte();
    
    std::string modifyMsgKey(std::string msgKey);
    std::string getMsgTypeByErrorCode(int iErrorCode,std::string msgKey);
    
    std::string GBKToUTF8(const std::string& strGBK);
    bool isGBKCode(const std::string& strIn);
    
    
    rapidjson::Document m_docCfg;
   
    
    
    int m_iinsertPos;
    int m_ireadPos;
    char* m_pNewBuf;
    char* m_pReadBuf;
    int m_structCount;     //结构体数量（消息里 结构体数组的上一个值表示）
    int m_structAllOffset; //单个结构体的偏移累加(没有内嵌结构体的消息也可以当成一个结构体)
    int m_structMaxAlignment; //单个结构体的最大对齐值

    int m_iLastByte;       //结构体最后那个字段的大小
    std::map<std::string, std::string> m_msgType;
    
    int m_iHeadLen;
    
    int m_AlignmentByte[4]; 
    
    ConfigMgr m_Config;
	

};

#endif /* NETMESSAGEMANAGER_H */

