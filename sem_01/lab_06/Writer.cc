#include "Writer.h"
#include "Global.h"
#include <iostream>
#include <windows.h>

void startWrite()
{
	InterlockedIncrement16(&waitingWriters);

	if (countActiveReaders > 0 || activeWriter) {
		WaitForSingleObject(canWrite, INFINITE);
	}

	InterlockedDecrement16(&waitingWriters);
	activeWriter = true;
}

void stopWrite()
{
	activeWriter = false;
	ResetEvent(canWrite);

	if (waitingReaders > 0) {
		SetEvent(canRead);
	}
	else {
		SetEvent(canWrite);
	}
}

DWORD WINAPI writer(LPVOID mutex)
{
	for (int i = 0; i < writerIterations; ++i) {
		startWrite();

		WaitForSingleObject(mutex, INFINITE);
		variable++;
		std::cout << "Writer ["
			<< GetCurrentThreadId()
			<< "] --> " << variable << std::endl;
		ReleaseMutex(mutex);

		stopWrite();

		Sleep(100);
	}

	return 0;
}