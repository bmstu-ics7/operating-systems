#ifndef __FTW_H
#define __FTW_H

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "func.h"
#include "stack.h"

int ftw(char *pathname, Function *func);
/*int dopath(Function *func, char *filename, int len);*/
int dopath(Function *func);

#endif /* __FTW_H */
