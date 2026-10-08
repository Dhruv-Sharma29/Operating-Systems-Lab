/*
Week 1 - Homework - Question 6
Write a C program using fork(), exec(), and wait() to execute the date
command. The parent process should wait for the child process to
complete before terminating.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
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
        printf("Child Process: Executing date command...\n");

        execlp("date", "date", (char *)NULL);

        // This executes only if execlp() fails
        perror("execlp");
        exit(1);
    }
    else {
        // Parent process
        wait(NULL);

        printf("Parent Process: Child has completed.\n");
    }

    return 0;
}