#ifndef __CONSUMER_H
#define __CONSUMER_H

#include <unistd.h>
#include "errors.h"
#include "semafor.h"

void consumer(int* shared_bufer, const int len, const int semid);

#endif /* __CONSUMER_H */
