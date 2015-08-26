#ifdef _BUFFERTEST
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifdef linux
#include <errno.h>
#include <pthread.h>
#endif // linux

#include "liblog.h"
#include "buffer.h"

#ifdef linux 
// 字符格式化
#define sprintf_s snprintf
// 线程开启
#define _THANDLE pthread_t
#define createthread(threadid, routine_addr, param) pthread_create(&threadid, NULL, routine_addr, (void*)param)
#endif // linux

#ifdef _WIN32
#define _THANDLE HANDLE
#define createthread(threadid, routine_addr, param) threadid = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)routine_addr, (LPVOID)param, NULL, NULL)
#endif


void* WorkThread(LPWORD pParam)
{
	Block* pBlock = (Block*)pParam;

	char data[32];
	while (pBlock->GetCanWriteDataSize())
	{
		memset(data, 0, 32);
		sprintf_s(data, 32, "add new data(%05d) ", pBlock->GetCanWriteDataSize());
		pBlock->WriteData(data, strlen(data));
	}

	return ((void*)0);
}

char* allocbuffer(unsigned int nSize)
{
	return (new char[nSize]);
}

void freebuffer(char* pBuff)
{
	delete[] pBuff;
}

int main()
{
	_THANDLE tindex;

	Block buf(8192, allocbuffer, freebuffer);
#ifdef linux
	int ret = createthread(tindex, WorkThread, &buf);
	if (ret != 0)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "createthread error(%d).", errno);
		return 0;
	}
#else	// _WIN32
	createthread(tindex, WorkThread, &buf);
	if (tindex == NULL)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "createthread error(%d).", GetLastError());
		return 0;
	}
#endif // linux
	unsigned int nLen = 0;
	char readbuf[100];
	while (1)
	{
		nLen = buf.GetCanReadDataSize();
		if (nLen > 0)
		{
			memset(readbuf, 0, 100);
			nLen = buf.ReadData(readbuf, 100);
			WriteLog(FC_RED, STDOUT_FILE_HANDLE, readbuf);
		}
	}

	return 0;
}
#endif // _BUFFERTEST