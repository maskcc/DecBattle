/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ConfigMgr.h"

int32_t
ConfigMgr::readJsonFile(string name)
{
    string fname = name + ".json";
    char readBuffer[65535] = {0};
    FILE *fp = fopen(fname.c_str(), "r");
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document *d = new Document();
    if(d->ParseStream(is).HasParseError())
    {
        _LOGX(_ERROR, "parse config file failed %s", name.c_str());
        fclose(fp);
        exit(-1);
    }
    
    m_configs.insert(make_pair(name, d));
    fclose(fp);
    //tests
    
    
    
    /*
    Value& s = d["C2S"];
    Value& msg = s["0xB4"];
    Value& arr = msg["game_data"];
    for (Value::ConstValueIterator itr = arr.Begin(); itr != arr.End(); ++itr)
        cout << itr->FindMember("value_name")->name.GetString() << ":" << itr->FindMember("value_name")->value.GetString()<< endl;
    
 
   */
   
    
    
    
}
ConfigMgr::ConfigMgr()
{
    readJsonFile("NJZnetMessage");
    
}

Document*
ConfigMgr::find(string name)
{
    
}