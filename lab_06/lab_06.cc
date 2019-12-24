#include <iostream>
#include <windows.h>
#include "Global.h"
#include "Create.h"
#include "Errors.h"
#include "Writer.h"
#include "Reader.h"

int main()
{
	createMutex();
	createEvents();
	createThreads();

	WaitForMultipleObjects(countWriters, writers, TRUE, INFINITE);
	WaitForMultipleObjects(countReaders, readers, TRUE, INFINITE);

	close();
}