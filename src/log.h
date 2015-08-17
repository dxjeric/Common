//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   20:52
//	File Name:	log.h
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	对外接口。
//-------------------------------------------------------------------------------------------------
#include "log_config.h"
//-------------------------------------------------------------------------------------------------
// write into file
//-------------------------------------------------------------------------------------------------
// 创建一个log文件
LOG_API _FILE_HANDLE OpenNewLogFile(const char* szName);

// 添加日志
LOG_API bool WriteLog(_FILE_HANDLE hLogFile, const char* szFormat, ...);

// 添加日志以及调用堆栈
LOG_API bool WriteCallStackLog(_FILE_HANDLE hLogFile, const char* szFormat, ...);

// 关闭日志文件
LOG_API void CloseLogFile(_FILE_HANDLE hLogFile);

//-------------------------------------------------------------------------------------------------
// write into stdout
//-------------------------------------------------------------------------------------------------
// 输出到标准输出, write log info into stdout
LOG_API void WriteStdLog(const char* szFormat, ...);

// 输出到标准输出，完成是flush。flush stdout after write log info into stdout 
LOG_API void WriteStdLogAndFlush(const char* szFormat, ...);


