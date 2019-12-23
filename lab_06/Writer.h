#pragma once

#include <Windows.h>

void startWrite();
void stopWrite();
DWORD WINAPI writer(LPVOID mutex);