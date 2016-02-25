//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-24   16:07
//	File Name:	buffer_config.h
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
// allocate buffer which size is n
typedef char* (*AllocBufferFun)(unsigned int n);
// free the allocated buffer
typedef void  (*FreeBufferFun)(char* pBuffer);


// default value for allocate buffer
#define ALLOC_BUFFER_SIZE 8192

