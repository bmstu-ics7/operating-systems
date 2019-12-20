#ifndef __PRODUCER_H
#define __PRODUCER_H

#include <unistd.h>
#include "errors.h"
#include "semafor.h"

void producer(int* shared_bufer, const int len, const semid);

#endif /* __PRODUCER_H */
