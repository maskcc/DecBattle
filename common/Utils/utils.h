/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utils.h
 * Author: admin
 *
 * Created on 2016年11月4日, 下午4:13
 */

#ifndef UTILS_H
#define UTILS_H

#include "log.h"

//有参数的LOG
#define _LOGX(level,fmt, ...) (__log(level, __FILE__,  __LINE__, __FUNCTION__, fmt, __VA_ARGS__))

//没有参数的log LOGX
#define _LOG(level,msg) (__log(level, __FILE__,  __LINE__, __FUNCTION__, msg))


#endif /* UTILS_H */

