#include "func.h"

int print_func
(
    const char          *pathname,
    const struct stat   *statptr,
    int                 type,
    int                 len
)
{
    int i;

    if (type == FTW_D)
    {
        for (i = 0; i < len; i++)
            printf("│   ");

        if (len >= 0) printf("├───");

        printf("%s\n", pathname);
    }
    else if (type == FTW_DNR || type == FTW_NS)
    {
        printf("Error on %s: type %d\n", pathname, type);
    }

    return 0;
}
