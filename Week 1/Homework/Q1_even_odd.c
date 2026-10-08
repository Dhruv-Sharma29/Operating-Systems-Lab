/*
Week 1 - Homework - Question 1
Write a C program in which:
1. The parent process prints all even numbers from 1 to 20.
2. The child process prints all odd numbers from 1 to 20.
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
        // Child process - print odd numbers
        printf("Child Process - Odd Numbers:\n");

        for (int i = 1; i <= 20; i++) {
            if (i % 2 != 0) {
                printf("%d ", i);
            }
        }

        printf("\n");
    }
    else {
        // Parent process - print even numbers
        printf("Parent Process - Even Numbers:\n");

        for (int i = 1; i <= 20; i++) {
            if (i % 2 == 0) {
                printf("%d ", i);
            }
        }

        printf("\n");
    }

    return 0;
}