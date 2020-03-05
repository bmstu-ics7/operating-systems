#pragma once

#include <Windows.h>

void startRead();
void stopRead();
DWORD WINAPI reader(LPVOID mutex);