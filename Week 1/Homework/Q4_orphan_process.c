/*
Week 1 - Homework - Question 4
Write a C program to demonstrate an orphan process. The child process
should print its PPID before and after the parent terminates.
Observe how the PPID changes after the parent exits.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child Process:\n");
        printf("PPID before parent terminates = %d\n", getppid());

        sleep(3);

        printf("PPID after parent terminates  = %d\n", getppid());
        printf("Child has become an orphan process.\n");
    }
    else {
        // Parent process
        printf("Parent Process:\n");
        printf("PID = %d\n", getpid());

        sleep(1);

        printf("Parent is terminating...\n");
        exit(0);
    }

    return 0;
}