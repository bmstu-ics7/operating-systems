#ifndef __ERRORS_H
#define __ERRORS_H

#include <stdio.h>
#include <stdlib.h>

void fork_error();
void shget_error();
void shmat_error();
void semget_error();
void semctl_error();
void semop_error();
void clean_error();

#endif /* __ERRORS_H */
