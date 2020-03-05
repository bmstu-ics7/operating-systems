#pragma once

#include <Windows.h>

extern HANDLE mutex;

extern HANDLE canWrite;
extern HANDLE canRead;

extern const short unsigned int countWriters;
extern const short unsigned int countReaders;

extern HANDLE writers[];
extern HANDLE readers[];

extern bool activeWriter;
extern volatile SHORT countActiveReaders;

extern const short unsigned int writerIterations;
extern const short unsigned int readerIterations;

extern int variable;

extern volatile SHORT waitingWriters;
extern volatile SHORT waitingReaders;