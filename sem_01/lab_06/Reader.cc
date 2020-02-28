#include "Reader.h"
#include "Global.h"
#include <iostream>
#include <windows.h>

void startRead()
{
	InterlockedIncrement16(&waitingReaders);

	if (activeWriter || waitingWriters > 0) {
		WaitForSingleObject(canRead, INFINITE);
	}

	InterlockedDecrement16(&waitingReaders);
	InterlockedIncrement16(&countActiveReaders);
	SetEvent(canRead);
}

void stopRead()
{
	InterlockedDecrement16(&countActiveReaders);

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