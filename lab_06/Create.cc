#include "Create.h"
#include <windows.h>
#include "Global.h"
#include "Errors.h"
#include "Writer.h"
#include "Reader.h"

void createMutex()
{
	mutex = CreateMutex(nullptr, false, nullptr);

	if (mutex == nullptr) {
		mutexError();
	}
}

void createEvents()
{
	canWrite = CreateEvent(nullptr, true, false, TEXT("read"));

	if (canWrite == nullptr) {
		eventError();
	}

	canRead = CreateEvent(nullptr, false, false, TEXT("write"));

	if (canRead == nullptr) {
		eventError();
	}
}

void createThreads()
{
	for (int i = 0; i < countWriters; ++i) {
		writers[i] = CreateThread(nullptr, 0, writer, mutex, 0, nullptr);

		if (writers[i] == nullptr) {
			threadError();
		}
	}

	for (int i = 0; i < countReaders; ++i) {
		readers[i] = CreateThread(nullptr, 0, reader, mutex, 0, nullptr);

		if (readers[i] == nullptr) {
			threadError();
		}
	}
}

void close()
{
	CloseHandle(mutex);
	CloseHandle(canRead);
	CloseHandle(canWrite);
}