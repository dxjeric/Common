//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   22:09
//	File Name:	lock.cpp
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include "lock.h"

CLock::CLock()
{
#ifdef _WIN32
	InitializeCriticalSection(&m_hLockHandle);
#else
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutex_init(&m_hLockHandle, &attr);
#endif
}

 CLock::~CLock()
{
#ifdef _WIN32
	DeleteCriticalSection(&m_hLockHandle);
#else
	pthred_mutex_destroy(&m_hLockHandle);
#endif
}

void CLock::Lock()
{
#ifdef _WIN32
	EnterCriticalSection(&m_hLockHandle);
#else
	pthread_mutex_lock(&m_hLockHandle);
#endif
}

void CLock::UnLock()
{
#ifdef _WIN32
	LeaveCriticalSection(&m_hLockHandle);
#else
	pthread_mutex_unlock(&m_hLockHandle);
#endif
}