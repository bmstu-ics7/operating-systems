#include "print_directory.h"

int print_directory(const char *dirname)
{
    struct dirent *dirp;
    DIR *dp;
    char str[BUF_SIZE] = { 0 };
    char path[BUF_SIZE] = { 0 };

    dp = opendir(dirname);

    if (dp == NULL)
    {
        perror("Can't open dir");
        return -1;
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        if ((strcmp(dirp->d_name, ".") != 0) &&
            (strcmp(dirp->d_name, "..") != 0))
        {
            sprintf(path, "%s%s", dirname, dirp->d_name);
            readlink(path, str, BUF_SIZE);
            printf("%s -> %s\n", dirp->d_name, str);
        }
    }

    closedir(dp);
    return 0;
}
