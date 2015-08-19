//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   21:01
//	File Name:	log_config.h
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	config of log
//-------------------------------------------------------------------------------------------------
#pragma once
// DLL暂时不做
#if defined(LOG_DLL)

#else
#define LOG_API extern
#endif 

// 定义CreateNewLogFile返回给用户的文件句柄, define file handle function CreateNewLogFile return
typedef unsigned int _FILE_HANDLE;

// 文件名的长度, 文件不能超过系统可以允许的文件路径的长度
// the max length of log file path. 
// the max length must be not bigger than 256, because it is the max length of system file path.
// the log class will record the log file path
#define LOG_FILE_PATH_LEN 256

// 每条日志的最大长度， the max length of every log info
#define LOG_INFO_MAX_LEN  10240

// 字体颜色仅用于stdout
// font color can only be used on stdout
enum FontColor {
	FC_BLACK	= 0,
	FC_RED		= 1,
	FC_GREEN	= 2,
	FC_YELLOW	= 3,
	FC_BLUE		= 4,
	FC_MAGENTA	= 5,
	FC_CYAN		= 6,
	FC_WHITE	= 7,
};

// stdout 
#define STDOUT_FILE_HANDLE 0