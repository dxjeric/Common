//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   19:52
//	File Name:	System.h
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	包含linux和windows通用的头文件
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <list>
#include <map>
#include <vector>
#include <assert.h>


#ifdef _WIN32
#include <windows.h>
#include <time.h>
#endif	// _WIN32

#ifdef linux
#include <stdarg.h>
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>

#endif // linux