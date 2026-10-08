/*
Week 1 - Homework - Question 3
Write a C program where the child process exits with status code 10.
The parent process waits for the child using wait() and prints the
child's exit status.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child Process: Exiting with status code 10\n");
        exit(10);
    }
    else {
        // Parent process
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Parent Process: Child exited normally.\n");
            printf("Child Exit Status = %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}