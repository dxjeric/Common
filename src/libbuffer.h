//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-24   16:00
//	File Name:	libbuffer.h
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include <stdio.h>

#include "buffer_config.h"
//-------------------------------------------------------------------------------------------------
class Buffer;
//-------------------------------------------------------------------------------------------------
/* 
名称: 创建一个Buffer对象
参数1: 申请buf函数，如果不为NULL，则Buffer对象在申请buffer时使用这个函数，否则使用默认的申请函数
参数2: 释放buf函数，如果不为NULL，则Buffer对象在释放buffer时使用这个函数，否则使用默认的释放函数
返回值: 成功时返回Buffer对象的指针，失败则返回NULL

name: create a Buffer object
param pfnAllocFun: allocate new buffer. if it is not NULL, Buffer object will allocate buffer by using 
pfnAllocFun, otherwise, using default allocate fun.
param pfnFreeFun: free the allocated buffer. if it is not NULL, Buffer object will allocate buffer by using 
pfnAllocFun, otherwise, using default free fun.
return value: On success a point for new buffer object is returned, On error NULL is returned
*/
Buffer* CreateNewBufferObj(AllocBufferFun pfnAllocFun = NULL, AllocBufferFun pfnFreeFun = NULL);

/*
名称: 删除Buffer对象
参数1: 要删除的对象

name: delete Buffer object
param 1: object need to be deleted
*/
void DeleteBufferObj(Buffer* pObj);

/*
名称: 设置Buffer对象的配置项
参数1: Buffer对象
参数2: 每次申请内存时的大小， 默认值见buffer_config.h ALLOC_BUFFER_SIZE
参数3: 最多可以申请的buffer的数量, 默认值为0， 表示不限制

name: set config of Buffer object
param 1: the Buffer object
param 2: the size of alloc new buffer
param 3: the max times for alloc buffer. default value is 0, that mean no limit on the times for alloc buffer
*/
void SetConfigOfBufferObj(Buffer* pObj, unsigned int nAllocBufferSize, unsigned int nMaxOfAllocBuffers);

/*
名称: 添加数据到Buffer对象
参数1: Buffer对象
参数2: 添加的数据
参数3: 添加的数据的长度
返回值:是否添加成功

name: add data to Buffer object
param 1: the Buffer object
param 2: the data will add to the pObj
param 3: the length of pData
return value: return true on success, return false on error
*/
bool WriteDataToBuffer(Buffer* pObj, const char* pData, unsigned int nLen);

/*
名称: 读取Buffer对象中的数据
参数1: Buffer对象
参数2: 读出数据的存放地址
参数3: 可以读取的最大长度
返回值:读取到的数据长度

name: read data from Buffer object
param 1: the Buffer object
param 2: the point of buffer will save the data is read from pObj
param 3: the length of pDest
return value: length of data is read from pObj is returned.
*/
unsigned int ReadDataFromBuffer(Buffer* pObj, char* pDest, unsigned int nDestLen);
