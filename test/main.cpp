#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifdef linux
#include <stdlib.h>
#endif // linux

#include "liblog.h"


#ifdef _WIN32
#define _SysPause() system("pause")
#else
#define _SysPause() system("");
#endif

void check(unsigned int n, unsigned int m, char* p)
{
	if (m != n)
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "(%s) >> error  m(%05d) != n(%05d).", p, m, n);
}

struct Buffer
{
	char* pBuffer;
	char* pBegin;
	char* pTail;
	char* pRead;
	char* pWrite;

public:
	Buffer()
	{
		pBuffer = new char[10251];
		pRead = pWrite = pBegin = pBuffer;
		pTail = pBuffer + 10251;
	}

	~Buffer()
	{
		delete [] pBuffer;
		pRead = pWrite = pBegin = pTail = pBuffer = NULL;
	}
public:
	char* Read()
	{
		if (pRead == pWrite)
			return NULL;

		int nLen = pWrite - pRead;
		check(nLen, pWrite - pRead, "1");
		char* pBuf = new char[nLen+1];
		check(nLen, pWrite - pRead, "2");
		memset(pBuf, 0, nLen+1);
		check(nLen, pWrite - pRead, "3");
		memcpy(pBuf, pRead, nLen);
		check(nLen, pWrite - pRead, "4");
		pRead += nLen;	
		WriteLog(FC_BLUE, STDOUT_FILE_HANDLE, "-------------------------------------------------------");

		return pBuf;
	}

	bool Write(char* pData, unsigned int nLen)
	{
		unsigned int nLeft = pTail - pWrite;
		if (nLeft <= 0)
			return false;

		if (nLeft < nLen)
			nLen = nLeft;

		memcpy(pWrite, pData, nLen);
		pWrite += nLen;
		return true;
	}
};


void WorkThread(LPWORD pParam)
{
	Buffer* pBuf = (Buffer*) pParam;
	char data[32];

	int a = 0;
	while (true)
	{
		memset(data, 0, 32);
		sprintf_s(data, 32, "%03d >> add new data.", a++);
		pBuf->Write(data, strlen(data));

		Sleep(33);
	}
}

int main()
{
	Buffer buf;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkThread, &buf, 0, 0);

	while (true)
	{
		char* pReadData = buf.Read();
		if (pReadData)
			WriteLog(FC_GREEN, STDOUT_FILE_HANDLE, pReadData);

		Sleep(55);
	}

	return 1;
}
