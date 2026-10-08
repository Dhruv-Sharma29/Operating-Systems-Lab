/*
Week 1 - Homework - Question 2
Write a C program to create three child processes using fork().
Each child process should print its child number (Child 1, Child 2,
Child 3), its Process ID (PID), and its Parent Process ID (PPID).
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    for (int i = 1; i <= 3; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            // Child process
            printf("Child %d\n", i);
            printf("PID  = %d\n", getpid());
            printf("PPID = %d\n\n", getppid());

            return 0;
        }
    }

    // Parent waits for all three children
    for (int i = 1; i <= 3; i++) {
        wait(NULL);
    }

    return 0;
}