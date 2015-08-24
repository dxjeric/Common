#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifdef linux
#include <stdlib.h>
#endif // linux

#include "log.h"

#define _SysPause() system("pause")

int main()
{
	_FILE_HANDLE fh = OpenNewLogFile("./test.log", true);
	_FILE_HANDLE fh2 = OpenNewLogFile("./test_no_std.log", false);

	if (fh == STDOUT_FILE_HANDLE)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "fh == STDOUT_FILE_HANDLE (./test.log)");
		_SysPause();
		return 0;
	}

	if (fh2 == STDOUT_FILE_HANDLE)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "fh2 == STDOUT_FILE_HANDLE (./test_no_std.log)");
		_SysPause();
		return 0;
	}
	int a = 0;
	int b = 0;

	WriteLog(FC_GREEN, fh, "<< fh write new log (%d).", a++);
	WriteLog(FC_GREEN, fh2, ">> fh2 write new log (%d).", b++);

	CloseLogFile(fh);

	WriteLog(FC_RED, fh, "<< fh write new log (%d).", a++);
	WriteLog(FC_RED, fh2, ">> fh2 write new log (%d).", b++);

	FlushLogFile(fh);
	FlushLogFile(fh2);

	//printf("123123123123123.\n");

	_SysPause();

	return 1;
}
