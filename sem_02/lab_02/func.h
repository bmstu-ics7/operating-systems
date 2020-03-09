#ifndef __FUNC_H
#define __FUNC_H

#include <stdio.h>
#include <sys/stat.h>

#define FTW_F   1 /* файл, не являющийся каталогом */
#define FTW_D   2 /* каталог */
#define FTW_DNR 3 /* каталог, который не доступен для чтения */
#define FTW_NS  4 /* файл, о котором нельзя получить информацию */

typedef int Function
(
    const char *,
    const struct stat *,
    int,
    int
);

int print_func
(
    const char          *pathname,
    const struct stat   *statptr,
    int                 type,
    int                 len
);

#endif /* __FUNC_H */
