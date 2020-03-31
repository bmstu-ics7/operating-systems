#include <stdio.h>

int main()
{
    const char letters[] = "Abcdefghijklmnopqrstuvwxyz";
    FILE *fd1 = fopen("out.txt", "wr");
    FILE *fd2 = fopen("out.txt", "wr");

    for (int i = 0; i < sizeof(letters) - 1; ++i)
    {
        fprintf(fd1, "%c", letters[i]);
        fprintf(fd2, "%c" , letters[i]);
    }

    fclose(fd1);
    fclose(fd2);

    return 0;
}
