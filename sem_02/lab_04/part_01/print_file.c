#include "print_file.h"

const char *stat_names[] =
{
    "pid",
    "comm",
    "state",
    "ppid",
    "pgrp",
    "session",
    "tty_nr",
    "tpgid",
    "flags",
    "minflt",
    "cminflt",
    "majflt",
    "cmajflt",
    "utime",
    "stime",
    "cutime",
    "cstime",
    "priority",
    "nice",
    "num_threads",
    "itrealvalue",
    "starttime",
    "vsize",
    "rss",
    "rsslim",
    "startcode",
    "endcode",
    "startstack",
    "kstkesp",
    "kstkeip",
    "signal",
    "blocked",
    "sigignore",
    "sigcatch",
    "wchan",
    "nswap",
    "сnswap",
    "exit_signal",
    "processor",
    "rt_priority",
    "policy",
    "delayacct_blkio_ticks",
    "guest_time",
    "cguest_time",
    "start_data",
    "end_data",
    "start_brk",
    "arg_start",
    "arg_end",
    "env_start",
    "env_end ",
    "exit_code",
};

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
    int i;
    char buf[BUF_SIZE] = { 0 };
    FILE *f = fopen("/proc/self/stat", "r");

    if (f == NULL)
    {
        perror("Can't open stat\n");
        return -1;
    }

    fread(buf, 1, BUF_SIZE, f);
    char *pch = strtok(buf, " ");

    i = 0;
    while(pch != NULL)
    {
        printf("%s -> %s\n", stat_names[i++], pch);
        pch = strtok(NULL, " ");
    }

    fclose(f);
    return 0;
}
