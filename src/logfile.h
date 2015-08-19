//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   21:47
//	File Name:	logfile.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include "system.h"
#include "lock.h"
#include "log_config.h"

extern int FormatLogInfo(char* szDest, const char* szFormat, va_list vlArgs);
extern void WriteInfoToStdout(FontColor fc, const char* szStr);
extern int GetStackTrace(char* szStackTrace);

class CLogFile
{
public:
	CLogFile();
	~CLogFile();

public:
	// write log info into m_pLogFile
	bool WriteLog(FontColor fc, const char* szFormat, va_list vlArgs);

	// write log info and the call stack info into m_pLogFile
	bool WriteCallStackLog(FontColor fc, const char* szFormat, va_list vlArgs);

	// close file
	void Close();

	// flush stdout and log file
	void Flush();

	bool Init(const char* szFileName, bool bWriteToStdout);

private:
	// log file
	FILE*	m_pLogFile;
	// file path
	char*	m_szFileName;
	// if m_bWriteToStdout is true, call WriteLog will write into  file and stdout, Otherwise only write into file.
	bool	m_bWriteToStdout;
};