/*
Week 2 - Classwork - Question 1
Write a C program in which:
1. The child process checks whether a given number is prime or not prime.
2. The parent process calculates and prints the factorial of the same number.
*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int num;
    int factorial = 1;
    int isPrime = 1;

    printf("Enter a number: ");
    scanf("%d", &num);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process - Check prime

        if (num <= 1) {
            isPrime = 0;
        }

        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = 0;
                break;
            }
        }

        if (isPrime)
            printf("Child Process: %d is Prime.\n", num);
        else
            printf("Child Process: %d is Not Prime.\n", num);
    }
    else {
        // Parent process - Calculate factorial

        for (int i = 1; i <= num; i++) {
            factorial = factorial * i;
        }

        printf("Parent Process: Factorial of %d = %d\n", num, factorial);
    }

    return 0;
}