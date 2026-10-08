/*
Week 1 - Homework - Question 5
Write a C program to demonstrate a zombie process. Observe the zombie
process using the ps command before the parent calls wait().
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

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
        printf("Child Process: Exiting...\n");
        exit(0);
    }
    else {
        // Parent process
        printf("Parent Process: PID = %d\n", getpid());
        printf("Child Process: PID = %d\n", pid);

        printf("Parent is sleeping for 10 seconds.\n");
        printf("During this time, check the zombie using:\n");
        printf("ps -l\n");

        sleep(10);

        // Parent collects child's exit status
        wait(NULL);

        printf("Parent called wait(). Zombie process is removed.\n");
    }

    return 0;
}