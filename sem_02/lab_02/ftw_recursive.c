#include "ftw_recursive.h"

int ftw(char *pathname, Function *func)
{
    if (chdir(pathname) < 0)
    {
        printf("Can't change dir to %s\n", pathname);
        return -1;
    }

    return dopath(func, ".", 0);
}

int dopath(Function *func, char *filename, int len)
{
    struct stat     statbuf;
    struct dirent   *dirp;
    DIR             *dp;
    int             ret;

    if (lstat(filename, &statbuf) < 0)
        return func(filename, &statbuf, FTW_NS, 0);

    if (S_ISDIR(statbuf.st_mode) == 0)
        return func(filename, &statbuf, FTW_F, 0);

    ret = func(filename, &statbuf, FTW_D, len);

    if (ret != 0)
        return ret;

    dp = opendir(filename);
    if (dp == NULL)
    {
        printf("DEBUG2");
        return func(filename, &statbuf, FTW_DNR, 0);
    }

    if (chdir(filename) < 0)
    {
        printf("Cannot chdir into %s\n", filename);
        return func(filename, &statbuf, FTW_DNR, 0);
    }

    ++len;

    while ((dirp = readdir(dp)) != NULL)
    {
        if (strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)
            dopath(func, dirp->d_name, len);
    }

    if (chdir("..") < 0)
    {
        printf("Cannot return into .. from %s", filename);
        return -1;
    }

    if (closedir(dp) < 0)
    {
        printf("Can't close directory %s\n", filename);
        return -1;
    }

    return ret;
}
