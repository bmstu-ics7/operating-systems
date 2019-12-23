#include "Reader.h"
#include "Global.h"
#include <iostream>
#include <Windows.h>

void startRead()
{
	if (activeWriter || WaitForSingleObject(canWrite, 0) == WAIT_OBJECT_0) {
		WaitForSingleObject(canRead, INFINITE);
	}

	++countActiveReaders;
	SetEvent(canRead);
}

void stopRead()
{
	--countActiveReaders;

	if (0 == countActiveReaders) {
		SetEvent(canWrite);
	}
}

DWORD WINAPI reader(LPVOID mutex)
{
	for (int i = 0; i < readerIterations; ++i) {
		startRead();

		WaitForSingleObject(mutex, INFINITE);
		std::cout << "Reader ["
				  << GetCurrentThreadId()
				  << "] <-- " << variable << std::endl;
		ReleaseMutex(mutex);

		stopRead();

		Sleep(100);
	}
	
	return 0;
}