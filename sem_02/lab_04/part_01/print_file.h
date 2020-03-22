#ifndef __PRINT_FILE_H
#define __PRINT_FILE_H

#include <stdio.h>
#include <string.h>
#include "buf_size.h"

extern const char *stat_names[];

int print_file(const char *filename);
int print_stat();

#endif /* __PRINT_FILE_H */
