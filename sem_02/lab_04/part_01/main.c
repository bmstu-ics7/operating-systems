#include "print_file.h"
#include "print_directory.h"

int main(int argc, char *argv[])
{
    printf("ENVIRON:\n");
    if (print_file("/proc/self/environ") < 0)
        return -1;

    printf("CMDLINE:\n");
    if (print_file("/proc/self/cmdline") < 0)
        return -1;

    printf("STAT:\n");
    if (print_stat() < 0)
        return -1;

    printf("FD:\n");
    if (print_directory("/proc/self/fd/") < 0)
        return -1;

    return 0;
}
