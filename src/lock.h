//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   21:57
//	File Name:	lock.h
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	thread lock
//-------------------------------------------------------------------------------------------------
#include "system.h"

#ifdef _WIN32
typedef CRITICAL_SECTION _HLOCK;
#else
typedef pthread_mutex_t  _HLOCK;
#endif



class CLock
{
public:
	CLock();
	~CLock();

public:
	void Lock();
	void UnLock();
private:
	_HLOCK	m_hLockHandle;
};
