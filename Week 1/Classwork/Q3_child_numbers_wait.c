/*
Week 1 - Classwork - Question 3
Write a C program in which the child process prints the numbers from
1 to 5, while the parent process waits for the child to finish using wait().
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child Process:\n");

        for (int i = 1; i <= 5; i++) {
            printf("%d\n", i);
        }
    }
    else {
        // Parent process
        wait(NULL);
        printf("Parent Process: Child has finished.\n");
    }

    return 0;
}