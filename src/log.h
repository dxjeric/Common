//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   20:52
//	File Name:	log.h
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	对外接口。
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "log_config.h"
//-------------------------------------------------------------------------------------------------
// write into file
//-------------------------------------------------------------------------------------------------
// 创建一个log文件
// parameter: 
// szName:			日志文件名(the path of log file)
// bWriteToStdout:  如果bWriteToStdout为true, 则会将日志信息同时写入stdout和日志文件中，否则只写入日志文件。
//					if bWriteToStdout is true, call write log funs will write into  file and stdout, 
//					Otherwise only write into file.
// return value:    return positive number if success, otherwise return 0.
LOG_API _FILE_HANDLE OpenNewLogFile(const char* szName, bool bWriteToStdout);

// 添加日志
// parameter：
// wColor: 见log_config.h(see log_config.h enum FontColor)
// hLogFile: the file handle that function OpenNewLogFile return. it will write into stdout when hLogFIle is STDOUT_FILE_HANDLE,
// szFormat: a format string that specifies how subsequent arguments
// write the log info 
LOG_API bool WriteLog(FontColor wColor, _FILE_HANDLE hLogFile, const char* szFormat, ...);

// 添加日志以及调用堆栈
// write the log info and call stack 
LOG_API bool WriteCallStackLog(FontColor wColor, _FILE_HANDLE hLogFile, const char* szFormat, ...);

// flush log file 
LOG_API void FlushLogFile(_FILE_HANDLE hLogFile);

// 关闭日志文件
// close the log file
LOG_API void CloseLogFile(_FILE_HANDLE hLogFile);
