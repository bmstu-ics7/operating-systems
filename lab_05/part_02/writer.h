#ifndef __WRITER_H
#define __WRITER_H

#include <unistd.h>
#include "errors.h"
#include "semafor.h"

void writer(int* shared_bufer, const int semid);

#endif /* __WRITER_H */
