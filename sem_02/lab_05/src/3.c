#include <stdio.h>

int main()
{
    const char letters[] = "Abcdefghijklmnopqrstuvwxyz";
    FILE *fd[2];
    fd[0] = fopen("out.txt", "wr");
    fd[1] = fopen("out.txt", "wr");

    for (int i = 0; i < sizeof(letters) - 1; ++i)
    {
        fprintf(fd[i % 2], "%c", letters[i]);
    }

    fclose(fd[0]);
    fclose(fd[1]);

    return 0;
}
