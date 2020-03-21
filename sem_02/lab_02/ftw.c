#include "ftw.h"

int ftw(char *pathname, Function *func)
{
    if (chdir(pathname) < 0)
    {
        printf("Can't change dir to %s\n", pathname);
        return -1;
    }

    return dopath(func);
}

int dopath(Function *func)
{
    struct stat     statbuf;
    struct dirent   *dirp;
    DIR             *dp;

    int             len = -1;

    struct stack *stack = stack_create();
    stack_push(stack, ".");

    while (!stack_is_empty(stack))
    {
        const char *filename = stack_pop(stack);

        if (filename == "..")
        {
            len--;

            if (chdir(filename) < 0)
            {
                printf("Cannot return into .. from");
                return -1;
            }
        }
        else if (lstat(filename, &statbuf) < 0)
        {
            func(filename, &statbuf, FTW_NS, 0);
        }
        else if (S_ISDIR(statbuf.st_mode) == 0)
        {
            func(filename, &statbuf, FTW_F, 0);
        }
        else
        {
            func(filename, &statbuf, FTW_D, len);

            dp = opendir(filename);

            if (dp == NULL)
            {
                func(filename, &statbuf, FTW_DNR, 0);
            }

            if (chdir(filename) < 0)
            {
                printf("Cannot chdir into %s\n", filename);
                func(filename, &statbuf, FTW_DNR, 0);
            }
            else
            {
                ++len;

                stack_push(stack, "..");
                while ((dirp = readdir(dp)) != NULL)
                {
                    if (strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)
                    {
                        stack_push(stack, dirp->d_name);
                    }
                }
            }
        }
    }

    return 0;
}
