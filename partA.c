// ilay cohen 206779514
// sean lavy2066345329

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/fcntl.h>

int main(int argc, char *argv[])
{
    char ch1, ch2;
    int filetest1, filetest2;
    int file1Check = open(argv[1], O_RDONLY);
    if (file1Check < 0)
    {
        printf("file1 did not opened\n");
        return -1;
    }
    int file2Check = open(argv[2], O_RDONLY);
    if (file2Check < 0)
    {
        printf("file2 did not opened\n");
        return -1;
    }
    filetest1 = read(file1Check, &ch1, 1);
    filetest2 = read(file2Check, &ch2, 1);
    while (filetest1 > 0 && filetest2 > 0)
    {
        if (ch1 != ch2)
        {
            printf("1\n");
            close(file1Check);
            close(file2Check);
            return 1;
        }
        filetest1 = read(file1Check, &ch1, 1);
        filetest2 = read(file2Check, &ch2, 1);
    }
    if (filetest1 == 0 && filetest2 == 0)
    {
        printf("2\n");
        close(file1Check);
        close(file2Check);
        return 2;
    }
    printf("1\n");
    close(file1Check);
    close(file2Check);
    return 1;
}
