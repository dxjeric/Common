//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   21:47
//	File Name:	logfile.cpp
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include <stdarg.h>

#ifdef _WIN32
#include <time.h>
#endif

#ifdef linux
#include <sys/time.h>
#include <errno.h>

// function backtrace is defined in execinfo.h
#include <execinfo.h>
#endif

#include "logfile.h"

//-------------------------------------------------------------------------------------------------
// font color 
//-------------------------------------------------------------------------------------------------

#ifdef _WIN32
static const WORD FondColorInfo[] =
{
	0,															// FC_BLACK	
	FOREGROUND_RED,												// FC_RED	
	FOREGROUND_GREEN,											// FC_GREEN	
	FOREGROUND_GREEN | FOREGROUND_RED,							// FC_YELLOW
	FOREGROUND_BLUE,											// FC_BLUE	
	FOREGROUND_BLUE | FOREGROUND_RED,							// FC_MAGENTA
	FOREGROUND_BLUE | FOREGROUND_GREEN,							// FC_CYAN	
	FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,		// FC_WHITE	
};
#endif // _WIN32

#ifdef linux
static const char* FondColorInfo[] =
{
	"\e[30m",	// FC_BLACK	
	"\e[31m",	// FC_RED		
	"\e[32m",	// FC_GREEN	
	"\e[33m",	// FC_YELLOW	
	"\e[34m",	// FC_BLUE		
	"\e[35m",	// FC_MAGENTA	
	"\e[36m",	// FC_CYAN		
	"\e[37m",	// FC_WHITE	
};
#endif //linux

#ifdef _WIN32	
// SetConsoleAttr 和 RecoverConsoleAttr必须在同一个作用域中
// SetConsoleAttr and RecoverConsoleAttr must be in the same domain
#define SetConsoleAttr(fc)		CONSOLE_SCREEN_BUFFER_INFO info; \
								if(fc != FC_DEFAULT) { \
									GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info); \
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FondColorInfo[fc]); \
								}

#define RecoverConsoleAttr(fc)	if(fc != FC_DEFAULT) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), info.wAttributes); }
#endif // _WIN32

#ifdef linux
#define SetConsoleAttr(fc)		if(fc != FC_DEFAULT) { printf(FondColorInfo[fc]); }
#define RecoverConsoleAttr(fc)	if(fc != FC_DEFAULT) { printf("\e[0m"); }
#endif	// linux
//-------------------------------------------------------------------------------------------------
#ifdef _WIN32
#define _gettime(tms, tt) localtime_s(tms, tt)
#endif // _WIN32

#ifdef linux
#define _vsnprintf vsnprintf
#define _gettime(tms, tt) localtime_r(tt, tms)

#endif	// linux
//-------------------------------------------------------------------------------------------------
int FormatLogInfo(char* szDest, const char* szFormat, va_list vlArgs)
{
	if (strlen(szFormat) >= (size_t)LOG_INFO_MAX_LEN)
		return 0;
	
	size_t nMaxLen = LOG_INFO_MAX_LEN;
	char* pDest = szDest;
	time_t tt;
	time(&tt);
	struct tm tms;
	_gettime(&tms, &tt);
	
	pDest += sprintf(pDest, "(%04d/%02d/%02d %02d:%02d:%02d) ", tms.tm_year + 1900, tms.tm_mon, tms.tm_mday, tms.tm_hour, tms.tm_min, tms.tm_sec);
	nMaxLen -= strlen(szDest);
	int len = _vsnprintf(pDest, nMaxLen, szFormat, vlArgs);
	if (len >= (int)nMaxLen)
		len = nMaxLen - 4;	// add '\r\n' and '\0' to the end of log info
	else if (len < 0)
		len = 0;
	pDest += len;
	pDest += sprintf(pDest, "\r\n");
	*(pDest++) = '\0';

	return pDest - szDest - 1;	// 长度不包含'\0'
}
void WriteInfoToStdout(FontColor fc, const char* szStr)
{
	SetConsoleAttr(fc);
	printf(szStr);
	RecoverConsoleAttr(fc);
}

int GetStackTrace(char* szStackTrace)
{
	int len = 0;
#ifdef linux 
	szStackTrace = szStackTrace;
	//len = backtrace(&szStackTrace, LOG_INFO_MAX_LEN);
#endif // linux
	return len;
}
//-------------------------------------------------------------------------------------------------
// class CLogFile
void FlushAndFlushStdout(FontColor fc, const char* szFormat, ...)
{
	char szLogInfo[LOG_INFO_MAX_LEN];
	memset(szLogInfo, 0, LOG_INFO_MAX_LEN);
	va_list vlArgs;
	va_start(vlArgs, szFormat);
	FormatLogInfo(szLogInfo, szFormat, vlArgs);
	va_end(vlArgs);
	WriteInfoToStdout(fc, szLogInfo);
	fflush(stdout);
}


CLogFile::CLogFile()
{
	m_bWriteToStdout = false;
	m_pLogFile = NULL;
	m_szFileName = NULL;
}

CLogFile::~CLogFile()
{
	if (m_pLogFile != NULL)
		fclose(m_pLogFile);
	m_pLogFile = NULL;

	delete [] m_szFileName;
	m_szFileName = NULL;
}

bool CLogFile::Init(const char* szFileName, bool bWriteToStdout)
{
	size_t nLen = strlen(szFileName);
	if (nLen < 0 || *szFileName == '\0')
	{
		FlushAndFlushStdout(FC_RED, "szFileName len is smaller than 0, szFileName.");
		return false;
	}	
	m_szFileName = new char[nLen+1];
	strcpy(m_szFileName, szFileName);

	m_pLogFile = fopen(m_szFileName, "wb");
	if (m_pLogFile == NULL)
	{
		FlushAndFlushStdout(FC_RED, "szFileName len is smaller than 0, szFileName = (%s), error(%d)(%s).", m_szFileName, errno, strerror(errno));
		return false;
	}
	
	m_bWriteToStdout = bWriteToStdout;
	return true;
}


void CLogFile::Close()
{
	fclose(m_pLogFile);
	m_pLogFile = NULL;
}

void CLogFile::Flush()
{
	fflush(m_pLogFile);
	if (m_bWriteToStdout)
		fflush(stdout);
}

bool CLogFile::WriteLog(FontColor fc, const char* szFormat, va_list vlArgs)
{

	char szLogInfo[LOG_INFO_MAX_LEN];
	memset(szLogInfo, 0, LOG_INFO_MAX_LEN);
	int nLogInfoLen = FormatLogInfo(szLogInfo, szFormat, vlArgs);
	if (nLogInfoLen <= 0)
		return false;

	fwrite(szLogInfo, 1, nLogInfoLen, m_pLogFile);
	if (m_bWriteToStdout)
		WriteInfoToStdout(fc, szLogInfo);

	return true;
}

bool CLogFile::WriteCallStackLog(FontColor fc, const char* szFormat, va_list vlArgs)
{
	char szLogInfo[LOG_INFO_MAX_LEN];
	memset(szLogInfo, 0, LOG_INFO_MAX_LEN);
	int nLogInfoLen = FormatLogInfo(szLogInfo, szFormat, vlArgs);
	if (nLogInfoLen <= 0)
		return false;

	fwrite(szLogInfo, 1, nLogInfoLen, m_pLogFile);
	if (m_bWriteToStdout)
		WriteInfoToStdout(fc, szLogInfo);

#ifdef linux
	// 打印调用堆栈信息
	memset(szLogInfo, 0, LOG_INFO_MAX_LEN);
	int nBackTraceLen = GetStackTrace(szLogInfo);
	if (nBackTraceLen > 0)
	{
		fwrite(szLogInfo, 1, nBackTraceLen, m_pLogFile);
		if (m_bWriteToStdout)
			WriteInfoToStdout(fc, szLogInfo);
	}		
#endif // linux

	return true;
}
