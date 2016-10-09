/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "NetMessageManager.h"


static NetMessageManager* _NetMessageManager = NULL;
NetMessageManager* NetMessageManager::getInstance()
{
    if (!_NetMessageManager)
    {
        _NetMessageManager = new NetMessageManager();
      
    }
    
    return _NetMessageManager;
}

NetMessageManager::~NetMessageManager()
{
    SAFEDEL(_NetMessageManager);
    _NetMessageManager = NULL;
}

void NetMessageManager::loadCfg(std::string name)
{
    int ret = m_Config.readJsonFile(name.c_str(),m_docCfg);
    if(-1 == ret)
    {
        _LOGX(_ERROR, "find [%s] fail", name.c_str());
        exit(-1);
    }
    
    //m_docCfg.Parse<rapidjson::kParseDefaultFlags>(contentStr.c_str());
    //int parseError = m_docCfg.GetParseError();
    
}

std::vector<char> NetMessageManager::readMessageByJson(const char* buf)
{
    
  
    string bufstr = buf;
    
    rapidjson::Document doc_msg;//用户传过来的消息
    doc_msg.Parse<rapidjson::kParseDefaultFlags>(bufstr.c_str());
    const rapidjson::Value& game_data = doc_msg["game_data"];//从用户传过来的消息读
    

    
    int vecBufLen = 0;
    m_iinsertPos = 0;
    m_pNewBuf = NULL;
    
    MsgHeadDef msgHead;
    unsigned short msgHeadLen = MSG_SIZE_LENGTH;
    const rapidjson::Value& msg_header = game_data["HEADER"];
 
    msgHead.identity = IDENTIFY_VER;
    msgHead.encode = ENCODE_NONE;
    msgHead.version = MESSAGE_VER;
    msgHead.reserve = 0;
    
    string cMsgType = msg_header["cMsgType"].GetString();
    long cMsgType_16 = strtol(cMsgType.c_str(),NULL,16);
    msgHead.cMsgType = htons(cMsgType_16);
    
    int retCode = 0;
    const rapidjson::Value& cfg_Obj = getMsgCfgObj(cMsgType.c_str(),1,retCode);//从配置表读出对应消息

    if (retCode == 1)
    {
        //只发包头
        vecBufLen = 8;
        msgHead.length = htons((unsigned short)8);
    }
    else
    {
        int msg_len = cfg_Obj["msg_len"].GetInt();
        msgHead.length = htons((unsigned short)msg_len);
        vecBufLen = msg_len;
    }
    

    vector<char> vecBuf(vecBufLen);
    m_pNewBuf = &vecBuf[0];
    memset(m_pNewBuf, 0, vecBufLen);
    if(!msg_header.IsNull())
    {
         memcpy(m_pNewBuf + m_iinsertPos,&msgHead,msgHeadLen);
         m_iinsertPos = msgHeadLen;
    }
 
    if(retCode != 1)
    {
       readMessageByObj(cfg_Obj,game_data);
    }

    return vecBuf;
}

void NetMessageManager::readMessageByArray(const rapidjson::Value& array)
{
    
}
void NetMessageManager::readMessageByObj(const rapidjson::Value& object_cfg,const rapidjson::Value& object_msg)
{
    const rapidjson::Value& cfg_values = object_cfg["game_data"];//从配置表读出
    for (rapidjson::SizeType i = 0; i < cfg_values.Size(); i++) {
        const rapidjson::Value& cfg_value = cfg_values[i];
        const rapidjson::Value& value_name = cfg_value["value_name"];
        const rapidjson::Value& value_offset = cfg_value["value_offset"];
        const rapidjson::Value& value_type = cfg_value["value_type"];
        const rapidjson::Value& value_btye = cfg_value["value_byte"];
        m_iinsertPos = m_iinsertPos + value_offset.GetInt(); //内存偏移先加上
        
        string cfg_valueType = value_type.GetString();
    
        if(cfg_valueType == "OP_STRUCT")
        {
            const string msg_key_str = value_name.GetString();
            const rapidjson::Value& cfg_Obj = m_docCfg[msg_key_str.c_str()];//从配置表读出对应消息
            const rapidjson::Value& msg_Obj = object_msg[msg_key_str.c_str()];//从用户传过来的消息读
            readMessageByObj(cfg_Obj,msg_Obj);
        }
        
        
        const rapidjson::Value& msg_value = object_msg[value_name.GetString()];
        
        rapidjson::Type type = msg_value.GetType();
        switch (type)
        {
            case rapidjson::kNumberType :
            {
                
                if(cfg_valueType == "OP_CHAR" || cfg_valueType == "OP_BYTE")
                {
                    int msgValue = msg_value.GetInt();
                    if (cfg_valueType == "OP_BYTE")
                    {
                        unsigned char ch = (unsigned char)msgValue;
                        memcpy(m_pNewBuf+m_iinsertPos,&ch,sizeof(unsigned char));
                    }
                    else
                    {
                       char ch = (char)msgValue;
                       memcpy(m_pNewBuf+m_iinsertPos,&ch,sizeof(char));
                    }
            
                }
                else if (cfg_valueType == "OP_SHORT" || cfg_valueType == "OP_USHORT")
                {
                    int msgValue = msg_value.GetInt();
                    if(cfg_valueType == "OP_USHORT")
                    {
                      unsigned short ishort = (unsigned short)msgValue;
                      memcpy(m_pNewBuf + m_iinsertPos, &ishort, sizeof(unsigned short));
                    }
                    else
                    {
                      short ishort = (short)msgValue;
                      memcpy(m_pNewBuf + m_iinsertPos, &ishort, sizeof(short));
                    }
                }
                else if(cfg_valueType == "OP_INT" || cfg_valueType == "OP_UINT" || cfg_valueType == "OP_LONG" || cfg_valueType == "OP_ULONG")
                {
                    if(cfg_valueType == "OP_UINT")
                    {
                        unsigned int msgValue = msg_value.GetUint();
                        memcpy(m_pNewBuf+m_iinsertPos,&msgValue,sizeof(int32_t));
                    }
                    else
                    {
                      int msgValue = msg_value.GetInt();
                      memcpy(m_pNewBuf+m_iinsertPos,&msgValue,sizeof(int32_t));
                    }
                    
                }
                else if (cfg_valueType == "OP_LLONG" || cfg_valueType == "OP_ULLONG")
                {
                    if (cfg_valueType == "OP_ULLONG")
                    {
                        unsigned long long msgValue = msg_value.GetUint64();
                        memcpy(m_pNewBuf + m_iinsertPos, &msgValue, sizeof(unsigned long long));
                    }
                    else
                    {
                        long long msgValue = msg_value.GetInt64();
                        memcpy(m_pNewBuf + m_iinsertPos, &msgValue, sizeof(long long));
                    }
                }
                
            }
                break;
            case rapidjson::kStringType :
            {
                string msgValue = msg_value.GetString();
               
                int btye = value_btye.GetInt();
                int strlen = msgValue.length();
                memcpy(m_pNewBuf+m_iinsertPos,msgValue.c_str(),strlen);
                
              
            }
                break;
            case rapidjson::kArrayType :
            {

                if(cfg_valueType == "OP_CHAR" || cfg_valueType == "OP_BYTE")
                {
                    for (int i = 0 ; i< msg_value.Size(); i++) {
                        char ch = msg_value[i].GetInt();
                        printf("ch.. %c",ch);
                        memcpy(m_pNewBuf+m_iinsertPos + i,&ch,sizeof(char));
                        
                    }
                   
                }
                else if(cfg_valueType == "OP_INT" || cfg_valueType == "OP_UINT" || cfg_valueType == "OP_LONG" || cfg_valueType == "OP_ULONG")
                {
                    for (int i = 0 ; i< msg_value.Size(); i++) {
                        int value = msg_value[i].GetInt();
                        
                        memcpy(m_pNewBuf+m_iinsertPos + i,&value,sizeof(int32_t));
                    }
                }
            }
                break;
            case rapidjson::kObjectType :
            {
                
            }
                break;
            default:
                break;
        }
    }
}


//std::vector<std::string> NetMessageManager::writeMessageToJson(vector<char>* data)
string NetMessageManager::writeMessageToJson( MsgBase* data)
{    
    int dataSize = data->head.length;
    vector<char> tmpdata(dataSize);
    memcpy(&tmpdata[0], &data->head, MSG_SIZE_LENGTH);
    tmpdata.insert(tmpdata.begin() + MSG_SIZE_LENGTH, data->msg.begin(), data->msg.end());
        
    std::string msg = writeOneMessageToJson(&tmpdata);
    
    return msg;
}

std::string NetMessageManager::writeOneMessageToJson(std::vector<char>* data)
{
    m_structCount = 0;
    
    string jsonstr = "";
    m_ireadPos = 0;
    m_pReadBuf= (char*)malloc(data->size());
    memcpy(m_pReadBuf, &((*data)[0]), data->size());
    
    MsgHeadDef* pHead = ( MsgHeadDef*)m_pReadBuf + m_ireadPos;
    pHead->cMsgType = (pHead->cMsgType);
    pHead->length = (pHead->length);
    
    rapidjson::Document game_data;
    game_data.SetObject();
    rapidjson::Document::AllocatorType& allocator = game_data.GetAllocator();
    
    rapidjson::Value HEADER(rapidjson::kObjectType);
    HEADER.AddMember("cMsgType", pHead->cMsgType, allocator);
    HEADER.AddMember("encode", pHead->encode, allocator);
    HEADER.AddMember("identity", pHead->identity, allocator);
    HEADER.AddMember("length",  pHead->length, allocator);
    HEADER.AddMember("reserve", pHead->reserve, allocator);
    HEADER.AddMember("version", pHead->version, allocator);
    
    game_data.AddMember("HEADER",HEADER,allocator);
    
    
    int retCode = 0;
    
    char sMsgType[32] = {0};
    sprintf(sMsgType, "0x%02X",pHead->cMsgType);
    const rapidjson::Value& cfg_Obj = getMsgCfgObj(sMsgType,2,retCode);//从配置表读出对应消息
    
    if (retCode == 0)
    {
        writeMessageByObj(cfg_Obj,game_data);
    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    game_data.Accept(writer);
    jsonstr = buffer.GetString();
    
    _LOGX(_DEBUG, "jsonstr[%s]", jsonstr.c_str());
    SAFEDEL( m_pReadBuf );
    return jsonstr;
    
}


void NetMessageManager::writeMessageByObj(const rapidjson::Value& object_cfg,rapidjson::Document& game_data,bool head /* = true*/)
{
    if (head)
    {
      m_ireadPos = m_ireadPos + MSG_SIZE_LENGTH;
    }
    
    rapidjson::Document::AllocatorType& allocator = game_data.GetAllocator();
    const rapidjson::Value& cfg_values = object_cfg["game_data"];//从配置表读出
    for (rapidjson::SizeType i = 0; i < cfg_values.Size(); i++) {
        const rapidjson::Value& cfg_value = cfg_values[i];
        const rapidjson::Value& value_name = cfg_value["value_name"];
        const rapidjson::Value& value_offset = cfg_value["value_offset"];
        const rapidjson::Value& value_type = cfg_value["value_type"];
        const rapidjson::Value& value_btye = cfg_value["value_byte"];
        m_ireadPos = m_ireadPos + value_offset.GetInt(); //内存偏移先加上
        m_structAllOffset = m_structAllOffset + value_offset.GetInt();
        if(i == cfg_values.Size() - 1)
        {
            m_iLastByte = value_btye.GetInt();
        }
        string cfg_valueType = value_type.GetString();
        rapidjson::Value valueKey(rapidjson::kStringType);
        valueKey.SetString(value_name.GetString(), allocator);
        
       // _LOGX(_DEBUG, "value_name :%s",value_name.GetString());
        if(cfg_valueType == "OP_STRUCT")
        {
            rapidjson::Value array(rapidjson::kArrayType);
            
            int structLen = 0;
            const string struct_key_str = value_name.GetString();
            
        //    _LOGX(_DEBUG, "struct_key_str :%s",struct_key_str.c_str());
        
            const rapidjson::Value& struct_Objs = m_docCfg["STRUCT"];//从配置表读出结构体
            const rapidjson::Value& struct_Obj = struct_Objs[struct_key_str.c_str()];
            
            int count = m_structCount;
            for (int i = 0 ; i< count; i++) {
                m_structAllOffset = 0;
                m_iLastByte = 0;
                memset(m_AlignmentByte, 0, sizeof(m_AlignmentByte));
                writeMessageByArray(struct_Obj,game_data,array);
                int maxAlignmentByte = getMaxAlignmentByte();
                m_structAllOffset = m_structAllOffset + m_iLastByte;
                int structMaxOffsetCount = (m_structAllOffset / maxAlignmentByte);
                int remainder = (m_structAllOffset % maxAlignmentByte);
                if(remainder)
                {
                  structMaxOffsetCount = structMaxOffsetCount + 1;
                }
                structLen = maxAlignmentByte * structMaxOffsetCount;
       
                m_ireadPos = m_ireadPos + m_iLastByte;
                m_ireadPos = m_ireadPos + (structLen - m_structAllOffset);
                
            }
        
            rapidjson::Value valueKey(rapidjson::kStringType);
            valueKey.SetString(struct_key_str.c_str(), allocator);
            game_data.AddMember(valueKey, array,allocator);
            
        }
        else if ( cfg_valueType == "OP_STRUCT_A_FIX")
        {
            rapidjson::Value array(rapidjson::kArrayType);
            
            int structLen = 0;
            const string struct_key_str = value_name.GetString();
            
        //    _LOGX(_DEBUG, "struct_key_str :%s",struct_key_str.c_str());
            
            const rapidjson::Value& struct_type = cfg_value["struct_type"];
            const string struct_type_str = struct_type.GetString();
            
            const rapidjson::Value& struct_Objs = m_docCfg["STRUCT"];//从配置表读出结构体
            const rapidjson::Value& struct_Obj = struct_Objs[struct_type_str.c_str()];
            const rapidjson::Value& arrary_num = cfg_value["arrary_num"];
            int count = arrary_num.GetInt();
            for (int i = 0 ; i< count; i++) {
                m_structAllOffset = 0;
                m_iLastByte = 0;
                memset(m_AlignmentByte, 0, sizeof(m_AlignmentByte));
                writeMessageByArray(struct_Obj,game_data,array);
                int maxAlignmentByte = getMaxAlignmentByte();
                m_structAllOffset = m_structAllOffset + m_iLastByte;
                int structMaxOffsetCount = (m_structAllOffset / maxAlignmentByte);
                int remainder = (m_structAllOffset % maxAlignmentByte);
                if(remainder)
                {
                    structMaxOffsetCount = structMaxOffsetCount + 1;
                }
                structLen = maxAlignmentByte * structMaxOffsetCount;
                m_ireadPos = m_ireadPos + m_iLastByte;
                m_ireadPos = m_ireadPos + (structLen - m_structAllOffset);
                
            }
            
            rapidjson::Value valueKey(rapidjson::kStringType);
            valueKey.SetString(struct_key_str.c_str(), allocator);
            game_data.AddMember(valueKey, array,allocator);
        }
        else if(cfg_valueType == "OP_CHAR" || cfg_valueType == "OP_BYTE")
        {
            if (cfg_valueType == "OP_CHAR")
            {
                char value = *(int8_t*)(m_pReadBuf + m_ireadPos);
                game_data.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }
            else if (cfg_valueType == "OP_BYTE")
            {
                unsigned char value = *(int8_t*)(m_pReadBuf + m_ireadPos);
                game_data.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }
            m_AlignmentByte[0] = 1;
        
        }
        else if(cfg_valueType == "OP_SHORT" || cfg_valueType == "OP_USHORT")
        {
            if (cfg_valueType == "OP_SHORT")
            {
                short value =*((int16_t*)(m_pReadBuf + m_ireadPos));
                game_data.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }
            else if (cfg_valueType == "OP_USHORT")
            {
                unsigned short value =*((int16_t*)(m_pReadBuf + m_ireadPos));
                game_data.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }
            m_AlignmentByte[1] = 2;
        }
        else if(cfg_valueType == "OP_INT" || cfg_valueType == "OP_UINT" || cfg_valueType == "OP_LONG" || cfg_valueType == "OP_ULONG")
        {
            //int long 暂且当成同样的东西
            if (cfg_valueType == "OP_INT" || cfg_valueType == "OP_LONG")
            {
                int value =*((int32_t*)(m_pReadBuf + m_ireadPos));
                game_data.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }
            else if (cfg_valueType == "OP_UINT" || cfg_valueType == "OP_ULONG")
            {
                unsigned int value =*((int32_t*)(m_pReadBuf + m_ireadPos));
                game_data.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }
            m_AlignmentByte[2] = 4;
        }
        else if(cfg_valueType == "OP_LLONG" || cfg_valueType == "OP_ULLONG")
        {
            if (cfg_valueType == "OP_LLONG")
            {
                //long long value = *((int64_t*)(m_pReadBuf + m_ireadPos));
                int64_t value = *((int64_t*)(m_pReadBuf + m_ireadPos));
                game_data.AddMember(valueKey, value,allocator);
            }
            else if (cfg_valueType == "OP_ULLONG")
            {
                //unsigned long long value = *((int64_t*)(m_pReadBuf + m_ireadPos));
                uint64_t value = *((int64_t*)(m_pReadBuf + m_ireadPos));
                game_data.AddMember(valueKey, value,allocator);
            }
            m_AlignmentByte[3] = 4;
        }
        else if(cfg_valueType == "OP_CS")
        {
            int byte = value_btye.GetInt();
            
            string value = string((m_pReadBuf + m_ireadPos),byte);
        //    _LOGX(_DEBUG, "strvalue : %s",value.c_str());
         
            //转换成UTF-8的函数还需要添加
           //     value = ToolManager::getInstance()->GBKToUTF8(value.c_str());
         
            
            rapidjson::Value jvalue(rapidjson::kStringType);
            jvalue.SetString(value.c_str(), allocator);
            game_data.AddMember(valueKey, jvalue,allocator);
        }
        else if(cfg_valueType == "OP_CC")
        {
            rapidjson::Value array(rapidjson::kArrayType);
            const string struct_key_str = value_name.GetString();
            
            int byte = value_btye.GetInt();
            
            for(int i = 0 ;i < byte ;i ++)
            {
                int value = *(int8_t*)(m_pReadBuf + m_ireadPos + i*sizeof(int8_t));
                rapidjson::Value valueKey(rapidjson::kNumberType);
                valueKey.SetInt(value);
                array.PushBack(valueKey, allocator);
            }
            
            rapidjson::Value valueKey(rapidjson::kStringType);
            valueKey.SetString(struct_key_str.c_str(), allocator);
            game_data.AddMember(valueKey, array,allocator);
        }
        else if(cfg_valueType == "OP_IA")
        {
            rapidjson::Value array(rapidjson::kArrayType);
            const string struct_key_str = value_name.GetString();
            
            int byte = value_btye.GetInt();
            int num = byte/sizeof(int32_t);
            for(int i = 0 ;i < num ;i ++)
            {
                int value = *(int32_t*)(m_pReadBuf + m_ireadPos + i*sizeof(int32_t));
                rapidjson::Value valueKey(rapidjson::kNumberType);
                valueKey.SetInt(value);
                array.PushBack(valueKey, allocator);
            }
            
            rapidjson::Value valueKey(rapidjson::kStringType);
            valueKey.SetString(struct_key_str.c_str(), allocator);
            game_data.AddMember(valueKey, array,allocator);
        }
        else if(cfg_valueType == "OP_LLA")
        {
            rapidjson::Value array(rapidjson::kArrayType);
            const string struct_key_str = value_name.GetString();
            
            int byte = value_btye.GetInt();
            
            int num = byte/sizeof(int64_t);
            for(int i = 0 ;i < num ;i ++)
            {
                int64_t value = *(int64_t*)(m_pReadBuf + m_ireadPos + i*sizeof(int64_t));
                rapidjson::Value valueKey(rapidjson::kNumberType);
                valueKey.SetInt64(value);
                array.PushBack(valueKey, allocator);
            }
            
            rapidjson::Value valueKey(rapidjson::kStringType);
            valueKey.SetString(struct_key_str.c_str(), allocator);
            game_data.AddMember(valueKey, array,allocator);
        }

    }
}


void NetMessageManager::writeMessageByArray(const rapidjson::Value& object_cfg,rapidjson::Document& game_data,rapidjson::Value& arrayOut)
{
    rapidjson::Value object(rapidjson::kObjectType);
    
    rapidjson::Document::AllocatorType& allocator = game_data.GetAllocator();
    const rapidjson::Value& cfg_values = object_cfg["game_data"];//从配置表读出
    for (rapidjson::SizeType i = 0; i < cfg_values.Size(); i++)
    {
        const rapidjson::Value& cfg_value = cfg_values[i];
        const rapidjson::Value& value_name = cfg_value["value_name"];
        const rapidjson::Value& value_offset = cfg_value["value_offset"];
        const rapidjson::Value& value_type = cfg_value["value_type"];
        const rapidjson::Value& value_btye = cfg_value["value_byte"];
        m_ireadPos = m_ireadPos + value_offset.GetInt(); //内存偏移先加上

        m_structAllOffset = m_structAllOffset + value_offset.GetInt();
        if(i == cfg_values.Size() - 1)
        {
           m_iLastByte = value_btye.GetInt();
        }
        string cfg_valueType = value_type.GetString();
        rapidjson::Value valueKey(rapidjson::kStringType);
        valueKey.SetString(value_name.GetString(), allocator);
        
    //    _LOGX(_DEBUG, "value_name :%s",value_name.GetString());
        if(cfg_valueType == "OP_STRUCT")
        {
            
            int structLen = 0;
            
            const string struct_key_str = value_name.GetString();
        //    _LOGX(_DEBUG, "struct_key_str :%s",struct_key_str.c_str());
            
            rapidjson::Value array(rapidjson::kArrayType);
            
            
            const rapidjson::Value& struct_Objs = m_docCfg["STRUCT"];//从配置表读出结构体
            const rapidjson::Value& struct_Obj = struct_Objs[struct_key_str.c_str()];
            int count = m_structCount;
            for (int i = 0 ; i< count; i++) {
                m_structAllOffset = 0;
                m_iLastByte = 0;
                memset(m_AlignmentByte, 0, sizeof(m_AlignmentByte));
                
                writeMessageByObj(struct_Obj,game_data,false);
                
                int maxAlignmentByte = getMaxAlignmentByte();
                m_structAllOffset = m_structAllOffset + m_iLastByte;
                int structMaxOffsetCount = (m_structAllOffset / maxAlignmentByte);
                int remainder = (m_structAllOffset % maxAlignmentByte);
                if(remainder)
                {
                    structMaxOffsetCount = structMaxOffsetCount + 1;
                }
                
                structLen = maxAlignmentByte * structMaxOffsetCount;
                m_ireadPos = m_ireadPos + m_iLastByte;
                m_ireadPos = m_ireadPos + (structLen - m_structAllOffset);
                
            }
            
            rapidjson::Value valueKey(rapidjson::kStringType);
            valueKey.SetString(struct_key_str.c_str(), allocator);
            object.AddMember(valueKey, array,allocator);
            
        }
        else if ( cfg_valueType == "OP_STRUCT_A_FIX")
        {
            rapidjson::Value array(rapidjson::kArrayType);
            
            int structLen = 0;
            const string struct_key_str = value_name.GetString();
        //    _LOGX(_DEBUG, "struct_key_str :%s",struct_key_str.c_str());
            
            const rapidjson::Value& struct_type = cfg_value["struct_type"];
            const string struct_type_str = struct_type.GetString();
            
            const rapidjson::Value& struct_Objs = m_docCfg["STRUCT"];//从配置表读出结构体
            const rapidjson::Value& struct_Obj = struct_Objs[struct_type_str.c_str()];
            const rapidjson::Value& arrary_num = cfg_value["arrary_num"];
            int count = arrary_num.GetInt();
            for (int i = 0 ; i< count; i++) {
                m_structAllOffset = 0;
                m_iLastByte = 0;
                memset(m_AlignmentByte, 0, sizeof(m_AlignmentByte));
                writeMessageByArray(struct_Obj,game_data,array);
                int maxAlignmentByte = getMaxAlignmentByte();
                m_structAllOffset = m_structAllOffset + m_iLastByte;
                int structMaxOffsetCount = (m_structAllOffset / maxAlignmentByte);
                int remainder = (m_structAllOffset % maxAlignmentByte);
                if(remainder)
                {
                    structMaxOffsetCount = structMaxOffsetCount + 1;
                }
                structLen = maxAlignmentByte * structMaxOffsetCount;
                m_ireadPos = m_ireadPos + m_iLastByte;
                m_ireadPos = m_ireadPos + (structLen - m_structAllOffset);
                
            }
            
            rapidjson::Value valueKey(rapidjson::kStringType);
            valueKey.SetString(struct_key_str.c_str(), allocator);
            game_data.AddMember(valueKey, array,allocator);
        }
        else if(cfg_valueType == "OP_CHAR" || cfg_valueType == "OP_BYTE")
        {
            if (cfg_valueType == "OP_CHAR")
            {
                char value = *(int8_t*)(m_pReadBuf + m_ireadPos);
                object.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }
            else if (cfg_valueType == "OP_BYTE")
            {
                unsigned char value = *(int8_t*)(m_pReadBuf + m_ireadPos);
                object.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }
            m_AlignmentByte[0] = 1;
            
        }
        else if(cfg_valueType == "OP_SHORT" || cfg_valueType == "OP_USHORT")
        {
            if (cfg_valueType == "OP_SHORT")
            {
                short value =*((int16_t*)(m_pReadBuf + m_ireadPos));
                object.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }
            else if (cfg_valueType == "OP_USHORT")
            {
                unsigned short value =*((int16_t*)(m_pReadBuf + m_ireadPos));
                object.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }
            m_AlignmentByte[1] = 2;
        }
        else if(cfg_valueType == "OP_INT" || cfg_valueType == "OP_UINT" || cfg_valueType == "OP_LONG" || cfg_valueType == "OP_ULONG")
        {
            //int long 暂且当成同样的东西
            if (cfg_valueType == "OP_INT" || cfg_valueType == "OP_LONG")
            {
                int value =*((int32_t*)(m_pReadBuf + m_ireadPos));
                object.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }
            else if (cfg_valueType == "OP_UINT" || cfg_valueType == "OP_ULONG")
            {
                unsigned int value =*((int32_t*)(m_pReadBuf + m_ireadPos));
                object.AddMember(valueKey, value,allocator);
                m_structCount = value;
            }

            m_AlignmentByte[2] = 4;
        }
        else if(cfg_valueType == "OP_LLONG" || cfg_valueType == "OP_ULLONG")
        {
            if (cfg_valueType == "OP_LLONG")
            {
                //long long value = *((int64_t*)(m_pReadBuf + m_ireadPos));
                int64_t value = *((int64_t*)(m_pReadBuf + m_ireadPos));
                object.AddMember(valueKey, value,allocator);
            }
            else if (cfg_valueType == "OP_ULLONG")
            {
                //unsigned long long value = *((int64_t*)(m_pReadBuf + m_ireadPos));
                uint64_t value = *((int64_t*)(m_pReadBuf + m_ireadPos));
                object.AddMember(valueKey, value,allocator);
            }
            m_AlignmentByte[3] = 4;
        }
        else if(cfg_valueType == "OP_CS")
        {
            int byte = value_btye.GetInt();
            string value = string((m_pReadBuf + m_ireadPos),byte);
            //
            
            
            //value = ToolManager::getInstance()->GBKToUTF8(value.c_str());
            rapidjson::Value jvalue(rapidjson::kStringType);
            jvalue.SetString(value.c_str(), allocator);
            object.AddMember(valueKey, jvalue,allocator);
        }
        else if(cfg_valueType == "OP_CC")
        {
            rapidjson::Value array(rapidjson::kArrayType);
            const string struct_key_str = value_name.GetString();
            
            int byte = value_btye.GetInt();
            
            for(int i = 0 ;i < byte ;i ++)
            {
                int value = *(int8_t*)(m_pReadBuf + m_ireadPos + i*sizeof(int8_t));
                rapidjson::Value valueKey(rapidjson::kNumberType);
                valueKey.SetInt(value);
                array.PushBack(valueKey, allocator);
            }
            
            rapidjson::Value valueKey(rapidjson::kStringType);
            valueKey.SetString(struct_key_str.c_str(), allocator);
            game_data.AddMember(valueKey, array,allocator);
        }
        else if(cfg_valueType == "OP_IA")
        {
            rapidjson::Value array(rapidjson::kArrayType);
            const string struct_key_str = value_name.GetString();
            
            int byte = value_btye.GetInt();
            
            int num = byte/sizeof(int32_t);
            for(int i = 0 ;i < num ;i ++)
            {
                int value = *(int32_t*)(m_pReadBuf + m_ireadPos + i*sizeof(int32_t));
                rapidjson::Value valueKey(rapidjson::kNumberType);
                valueKey.SetInt(value);
                array.PushBack(valueKey, allocator);
            }
            
            rapidjson::Value valueKey(rapidjson::kStringType);
            valueKey.SetString(struct_key_str.c_str(), allocator);
            game_data.AddMember(valueKey, array,allocator);
        }
        else if(cfg_valueType == "OP_LLA")
        {
            rapidjson::Value array(rapidjson::kArrayType);
            const string struct_key_str = value_name.GetString();
            
            int byte = value_btye.GetInt();
            
            int num = byte/sizeof(int64_t);
            for(int i = 0 ;i < num ;i ++)
            {
                int64_t value = *(int64_t*)(m_pReadBuf + m_ireadPos + i*sizeof(int64_t));
                rapidjson::Value valueKey(rapidjson::kNumberType);
                valueKey.SetInt64(value);
                array.PushBack(valueKey, allocator);
            }
            
            rapidjson::Value valueKey(rapidjson::kStringType);
            valueKey.SetString(struct_key_str.c_str(), allocator);
            game_data.AddMember(valueKey, array,allocator);
        }
        
        
    }
    arrayOut.PushBack(object, allocator);
}

int NetMessageManager::getMaxAlignmentByte()
{
    int max = 0;
    for (int i = 3 ; i>=0 ;i-- )
    {
        if(m_AlignmentByte[i] > 0)
        {
            max = m_AlignmentByte[i];
            break;
        }
    }
    
    return max;

}

const rapidjson::Value& NetMessageManager::getMsgCfgObj(string msgTypeStr,int iType,int &retCode)
{
    //从配置表读出对应消息
    


   if (iType == 1)
   {
      
       const rapidjson::Value& msgid_Objs = m_docCfg["C2S"];
       
        if (msgid_Objs.FindMember(msgTypeStr.c_str()) != msgid_Objs.MemberEnd())
        {
          return msgid_Objs[msgTypeStr.c_str()];
        }
       
   }
   else if (iType == 2)
   {
       if(!m_msgType.empty()) //先检查外部有没有传进来的修正类型
       {
           if(m_msgType.find(msgTypeStr) != m_msgType.end())
           {
               map<std::string, std::string>::iterator it = m_msgType.find(msgTypeStr);
               string typeStr = it->second;
               
               m_msgType.erase(it); //移除
               
               const rapidjson::Value& msgid_Objs = m_docCfg["S2C"];
               
               if (msgid_Objs.HasMember(msgTypeStr.c_str()))
               {
                   return msgid_Objs[msgTypeStr.c_str()];
               }
               else
               {
                   //出错了
                  retCode = 1;
                   
               }
           }
       }
       
       std::string modifyMsg = modifyMsgKey(msgTypeStr);
       
       if (modifyMsg == msgTypeStr)
       {
           const rapidjson::Value& msgid_Objs = m_docCfg["S2C"];
           if (msgid_Objs.HasMember(msgTypeStr.c_str()))
           {
               
                return msgid_Objs[msgTypeStr.c_str()];
           }
       }
       else
       {
           const rapidjson::Value& msgid_Objs = m_docCfg["ERRORMSG"];
           if (msgid_Objs.HasMember(modifyMsg.c_str()))
           {
               
               return msgid_Objs[modifyMsg.c_str()];
           }
       }
       
   }
   
    retCode = 1;
}

void NetMessageManager::setMessageType(std::string msgKey,std::string msgType)
{
    m_msgType.insert(make_pair(msgKey, msgType));
}

std::string NetMessageManager::modifyMsgKey(std::string msgKey)
{
    string modifyMsg = msgKey;
    
    if (m_docCfg.HasMember("S2C")) {
        const rapidjson::Value& s2c_Objs = m_docCfg["S2C"];
        if (s2c_Objs.HasMember(msgKey.c_str())) {
            const rapidjson::Value& s2c_Obj = s2c_Objs[msgKey.c_str()];
            
            int ireadPos = 0;
            int iError = 0;
            const rapidjson::Value& cfg_values = s2c_Obj["game_data"];//从配置表读出
            for (rapidjson::SizeType i = 0; i < cfg_values.Size(); i++)
            {
                const rapidjson::Value& cfg_value = cfg_values[i];
                const rapidjson::Value& value_name = cfg_value["value_name"];
                const rapidjson::Value& value_offset = cfg_value["value_offset"];
                ireadPos = ireadPos + ireadPos + value_offset.GetInt();
                
                if (strcmp(value_name.GetString(), "cError") == 0) {
                    
					ireadPos = ireadPos + MSG_SIZE_LENGTH;
					iError = *(int8_t*)(m_pReadBuf + ireadPos);
					break;
                }
            }
            
            modifyMsg = getMsgTypeByErrorCode(iError,msgKey);
            
        }
    }
    
    return modifyMsg;
}

std::string NetMessageManager::getMsgTypeByErrorCode(int iErrorCode,std::string msgKey)
{
   string modifyMsg = msgKey;
   if (m_docCfg.HasMember("ERRORCODE")) {
        const rapidjson::Value& error_Objs = m_docCfg["ERRORCODE"];
        if(error_Objs.HasMember(msgKey.c_str()))
        {
           const rapidjson::Value& error_Obj = error_Objs[msgKey.c_str()];
           char buf[32] = {0};
           sprintf(buf, "%d",iErrorCode);
           if(error_Obj.HasMember(buf))
           {
              const rapidjson::Value& obj = error_Obj[buf];
               modifyMsg = obj.GetString();
           }
        }
   }
    
   return modifyMsg;
}

string NetMessageManager::GBKToUTF8(const std::string& strGBK)
{
    string strOutUTF8 = "";

    size_t strLen = strGBK.length();
//   auto outLength = strLen * 4;
//    auto outbuf = new (std::nothrow) char[outLength];
//    memset(outbuf, 0, outLength);
 //   char* pBuff = outbuf;
    //conversionEncodingJNI((char*)strGBK.c_str(), gb2312StrSize, "GB2312", outbuf, "UTF-8");
 //   strOutUTF8 = pBuff;
   // _LOGX(_DEBUG, "utf-8 :%s",pBuff);
    return strOutUTF8;
    

}

bool NetMessageManager::isGBKCode(const string& strIn)
{
    unsigned char ch1;
    unsigned char ch2;
    
    if (strIn.size() >= 2)
    {
        ch1 = (unsigned char)strIn.at(0);
        ch2 = (unsigned char)strIn.at(1);
        if (ch1>=129 && ch1<=254 && ch2>=64 && ch2<=254)
            return true;
        else return false;
    }
    else return false;
}