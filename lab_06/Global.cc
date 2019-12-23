#include "Global.h"

HANDLE mutex;

HANDLE canWrite;
HANDLE canRead;

const short unsigned int countWriters = 3;
const short unsigned int countReaders = 5;

HANDLE writers[countWriters];
HANDLE readers[countReaders];

bool activeWriter = false;
short unsigned int countActiveReaders = 0;

const short unsigned int writerIterations = 10;
const short unsigned int readerIterations = 15;

int variable = 0;