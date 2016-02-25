#ifdef _BUFFERTEST
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifdef linux
#include <errno.h>
#include <pthread.h>
#include <unistd.h>	// sleep
#endif // linux
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#include "liblog.h"
#include "buffer.h"
#include "common_sys_fun.h"

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

#define READ_FILE_PATH	"E:\\ceshi.txt"
#define WRITE_FILE_PATH "E:\\ceshi_write.txt"


void* WorkThread(LPWORD pParam)
{
	Buffer* pBuffer = (Buffer*)pParam;
	char data[201];
	FILE* fRead = fopen(READ_FILE_PATH, "rb");
	if (fRead == NULL)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "fopen READ_FILE_PATH error %d.", errno);
		assert(false);
	}
	srand((unsigned int)time(NULL));

	while (true)
	{
		memset(data, 0, 201);
		int nRand = rand() % 200 + 1;
		int nReadLen = fread(data, 1, nRand, fRead);

		if (nReadLen > 0)
			//WriteLog(FC_RED, STDOUT_FILE_HANDLE, data);

		if (nReadLen > 0 && !pBuffer->WriteData(data, nReadLen))
		{
			WriteLog(FC_RED, STDOUT_FILE_HANDLE, "pBuffer->WriteData failed!");
			break;
		}
		csf_sleep(1000);
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

	Buffer buf(0, 500);
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

	FILE* fWrite = fopen(WRITE_FILE_PATH, "wb");
	if (fWrite == NULL)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "fopen WRITE_FILE_PATH error %d.", errno);
		assert(false);
	}

	unsigned int nLen = 0;
	char readbuf[101];
	while (1)
	{
		nLen = buf.GetCanReadSize();
		if (nLen > 0)
		{
			memset(readbuf, 0, 101);
			nLen = buf.ReadData(readbuf, 100);
			fwrite(readbuf, 1, nLen, fWrite);
			fflush(fWrite);
			//WriteLog(FC_GREEN, STDOUT_FILE_HANDLE, readbuf);
		}
		csf_sleep(1000);
	}

	return 0;
}
#endif // _BUFFERTEST