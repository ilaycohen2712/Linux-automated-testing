// ilay cohen 206779514
// sean lavy2066345329

#include <stdio.h>
#include <sys/fcntl.h>
#include <syscall.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    char dir[50];
    char in[50];
    char out[50];
    char input1[50];
    char input2[50];
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("after open: ");
        return -1;
    }
    readline(dir, fd);
    readline(in, fd);
    readline(out, fd);
    int pid;
    pid = fork();
    if (pid < 0)
    {
        printf("fork didnt work");
        return -1;
    }
    if (pid == 0)
    {
        int fd2 = open("studentlist.txt", O_RDONLY | O_WRONLY | O_CREAT, 0666);
        close(1);
        dup(fd2);
        close(fd2);
        char *list[] = {"ls", dir, NULL};
        execvp("ls", list);
    }
    else
    {
        wait(NULL);
        int count = 0;
        char chread;
        char stringRow[50];
        int fd3 = open("studentlist.txt", O_RDONLY);
        while (1)
        {
            char temp[50];
            readline(temp, fd3);
            count++;
            if (read(fd3, &chread, 1) == 0)
            {
                break;
            }
        }
        lseek(fd3, 0, SEEK_SET);
        int fd = open("grades.csv", O_RDONLY | O_WRONLY | O_CREAT, 0666);
        for (int k = 0; k < count; k++)
        {
            char name[50];
            readline(name, fd3);
            int pid1;
            pid1 = fork();
            if (pid1 < 0)
            {
                printf("fork didnt work");
                return -1;
            }
            if (pid1 == 0)
            {
                int fd4 = open(in, O_RDONLY);
                int fd5 = open("out.txt", O_RDONLY | O_WRONLY | O_CREAT, 0666);
                readline(input1, fd4);
                readline(input2, fd4);
                close(1);
                dup(fd5);
                close(fd5);
                strcat(dir, "/");
                strcat(dir, name);
                strcat(dir, "/main.exe");
                char *argp[] = {dir, input1, input2, NULL};
                execvp(dir, argp);
            }
            else
            {
                wait(NULL);
                int pid2;
                pid2 = fork();
                if (pid2 < 0)
                {
                    printf("fork didnt work");
                    return -1;
                }
                if (pid2 == 0)
                {
                    int fd6 = open("isSame.txt", O_RDONLY | O_WRONLY | O_CREAT, 0666);
                    close(1);
                    dup(fd6);
                    close(fd6);
                    char *argn[] = {"./comp.exe", "out.txt", out, NULL};
                    execvp("./comp.exe", argn);
                }
                else
                {
                    wait(NULL);
                    int fdSame = open("isSame.txt", O_RDONLY);
                    char f;
                    int rdsame = read(fdSame, &f, 1);
                    if (f == '2')
                    {
                        strcat(name, " 100");
                        write(fd, name, strlen(name));
                        write(fd, "\n", 1);
                        continue;
                    }
                    else
                    {
                        strcat(name, " 0");
                        write(fd, name, strlen(name));
                        write(fd, "\n", 1);
                    }
                }
            }
        }
    }
    return 0;
}
