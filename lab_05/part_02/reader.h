#ifndef __READER_H
#define __READER_H

#include <unistd.h>
#include "errors.h"
#include "semafor.h"

void reader(int* shared_bufer, const int semid);

#endif /* __READER_H */
