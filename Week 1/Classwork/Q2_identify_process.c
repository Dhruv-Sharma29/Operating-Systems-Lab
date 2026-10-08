/*
Week 1 - Classwork - Question 2
Write a C program that uses the return value of fork() to print
"Parent Process" only in the parent process and "Child Process"
only in the child process.
*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child Process\n");
    }
    else {
        // Parent process
        printf("Parent Process\n");
    }

    return 0;
}