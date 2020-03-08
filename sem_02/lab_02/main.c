#include <stdio.h>
#include "func.h"
#include "ftw.h"

int main(int argc, char* argv[])
{
    int ret;

    if (argc != 2)
    {
        perror("usage: ./a.out <input directory>");
        return -1;
    }

    return ftw(argv[1], print_func);
}
