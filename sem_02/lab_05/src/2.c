#include <fcntl.h>
#include <unistd.h>

int main()
{
    char c;
    int cond1 = 1, cond2 = 1;
    int fd1 = open("alphabet.txt", O_RDONLY);
    int fd2 = open("alphabet.txt", O_RDONLY);

    while(cond1 || cond2)
    {
        if ((cond1 = read(fd1, &c, 1)) == 1)
            write(1, &c, 1);

        if ((cond2 = read(fd2, &c, 1)) == 1)
            write(1, &c, 1);
    }

    return 0;
}
