/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConfigMgr.h
 * Author: admin
 *
 * Created on 2016年9月29日, 下午1:29
 */

#ifndef CONFIGMGR_H
#define CONFIGMGR_H

#include <vector>
#include <string>
#include <map>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include <cstdio>
#include <iostream>
#include "utils.h"
using namespace rapidjson;
using namespace std;
class ConfigMgr
{
public:
    ConfigMgr();
    int32_t readJsonFile(string name);
    Document* find(string name);
protected:
    vector<string> files;
    map<string, Document*> m_configs;
    
    
    
    
    
    
    
};


#endif /* CONFIGMGR_H */

