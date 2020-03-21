#include "print_file.h"

int print_file(const char *filename)
{
    char buf[BUF_SIZE] = { 0 };
    int len, i;
    FILE *f;

    f = fopen(filename, "r");

    if (f == NULL)
    {
        perror("Can't open file\n");
        return -1;
    }

    while ((len = fread(buf, 1, BUF_SIZE, f)) > 0)
    {
        for (i = 0; i < len; ++i)
            if (buf[i]  == 0)
                buf[i] = 10;

        buf[len - 1] = 0;
        printf("%s", buf);
    }

    printf("\n");

    fclose(f);
    return 0;
}

int print_stat()
{
    char buf[BUF_SIZE] = { 0 };
    FILE *f = fopen("/proc/self/stat", "r");

    if (f == NULL)
    {
        perror("Can't open stat\n");
        return -1;
    }

    fread(buf, 1, BUF_SIZE, f);
    char *pch = strtok(buf, " ");

    while(pch != NULL)
    {
        printf("%s\n", pch);
        pch = strtok(NULL, " ");
    }

    fclose(f);
    return 0;
}
