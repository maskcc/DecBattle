/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NameService.h
 * Author: admin
 *
 * Created on 2016年9月13日, 上午10:44
 */

#ifndef NAMESERVICE_H
#define NAMESERVICE_H
#include <string>
#include <vector>
#include "GameDef.h"
#include "utils.h"
using namespace std;

class SName
{
public:
    int32_t service;
    string name;    
};

class NameService
{
public:
    
    static NameService* getInstance();
    int32_t reg(int32_t s, string name);
    int32_t search(string name);
    static NameService* m_ins;
    
protected:
    vector<SName> m_nameList;
    
    NameService();
    
};


#endif /* NAMESERVICE_H */

