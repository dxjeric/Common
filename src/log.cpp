//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   20:54
//	File Name:	log.c
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include "log.h"
#include "logfile.h"
//-------------------------------------------------------------------------------------------------
static _FILE_HANDLE init_id = STDOUT_FILE_HANDLE;
typedef std::map<_FILE_HANDLE, CLogFile*> _ALL_LOG_FILE;
typedef _ALL_LOG_FILE::iterator _ALL_LOG_FILE_ITOR;
static _ALL_LOG_FILE log_files;
//-------------------------------------------------------------------------------------------------

/*
CreateNewLogFile:
parameter: the log file name, max length if LOG_FILE_PATH_LEN
*/
LOG_API _FILE_HANDLE OpenNewLogFile(const char* szName, bool bWriteToStdout)
{
	CLogFile* pNewLogFile = new CLogFile();
	if (!pNewLogFile->Init(szName, bWriteToStdout))
	{
		delete pNewLogFile;
		return STDOUT_FILE_HANDLE;
	}

	_FILE_HANDLE nNewHandle = ++init_id;

	log_files.insert(std::pair<_FILE_HANDLE, CLogFile*>(nNewHandle, pNewLogFile));
	return nNewHandle;
}

LOG_API void FlushLogFile(_FILE_HANDLE hLogFile)
{
	if (hLogFile == STDOUT_FILE_HANDLE)
		fflush(stdout);
	else
	{
		_ALL_LOG_FILE_ITOR itor = log_files.find(hLogFile);
		if (itor != log_files.end())
			itor->second->Flush();
	}
}

LOG_API void CloseLogFile(_FILE_HANDLE hLogFile)
{
	if (hLogFile != STDOUT_FILE_HANDLE)
	{
		_ALL_LOG_FILE_ITOR itor = log_files.find(hLogFile);
		if (itor != log_files.end())
		{
			delete itor->second;
			log_files.erase(itor);
		}
	}
}

LOG_API bool WriteLog(FontColor wColor, _FILE_HANDLE hLogFile, const char* szFormat, ...)
{
	if (hLogFile != STDOUT_FILE_HANDLE)
	{
		_ALL_LOG_FILE_ITOR itor = log_files.find(hLogFile);
		if (itor != log_files.end())
		{
			va_list vlArgs;
			va_start(vlArgs, szFormat);
			itor->second->WriteLog(wColor, szFormat, vlArgs);
			va_end(vlArgs);

			return true;
		}
		else
		{
			WriteLog(FC_RED, STDOUT_FILE_HANDLE, "hLogFile = (%lu) not exist!", hLogFile);
		}
	}

	char szLogInfo[LOG_INFO_MAX_LEN];
	memset(szLogInfo, 0, LOG_INFO_MAX_LEN);
	va_list vlArgs;
	va_start(vlArgs, szFormat);
	FormatLogInfo(szLogInfo, szFormat, vlArgs);
	WriteInfoToStdout(wColor, szLogInfo);
	va_end(vlArgs);

	return true;
}


