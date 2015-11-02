//-------------------------------------------------------------------------------------------------
//	Created:	2015-9-25   17:02
//	File Name:	thread.h
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifdef linux
#include <pthread.h>
#endif // linux

#include "basetype.h"
#include "common_sys_fun.h"
//-------------------------------------------------------------------------------------------------
// 统一变量定义
#ifdef linux
typedef pthread_t	_THREAD_HANDLE;
typedef void*		_THREAD_START_FUN;
#endif // linux

#ifdef _WIN32
typedef HANDLE					_THREAD_HANDLE;
typedef LPTHREAD_START_ROUTINE	_THREAD_START_FUN;
#endif //_WIN32
//-------------------------------------------------------------------------------------------------
/*
* 关于pthread的joinable和detached属性说明
* joinable属性为该线程可以被其他线程或者进程关闭，线程资源的结束必须通过pthread_join来回收。
* detached属性不能通过pthread_join来终止线程，线程结束时，线程资源系统会自动回收。使用这个属性是程序不需要关心线程的退出状态。
*		  无法再设置为joinable属性
*/
class CThrea
{
public:
	/*
	* pFun		 : 线程运行函数
	* nStackSize : 线程申请的堆栈大小，0表示申请的大小为系统设置的默认大小
	* 			   linux查看命令 ulimit -s	
	* 备注:	1. join detach属性只有linux支持
	*       2. linux系统线程创建默认为joinable属性
	*/
	CThrea(_THREAD_START_FUN pFun, int nStackSize = 0, bool bIsJoin = true);
	~CThrea();

public:
	// 创建运行线程
	bool Run();
	/*
	* 将joinable重新设置为detach属性
	*/
	bool SetDetached();

	/*
	* 关闭线程
	*/
	bool Join();

private:
	bool m_bHasRun;	// 线程是否已经运行
	bool m_bIsJoin;	// 线程属性

	// 线程句柄
	_THREAD_HANDLE m_Thread;
};
