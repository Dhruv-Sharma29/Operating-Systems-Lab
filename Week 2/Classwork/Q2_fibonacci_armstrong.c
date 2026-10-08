/*
Week 2 - Classwork - Question 2
Write a C program in which:
1. The child process calls a function to print the Fibonacci series up to n.
2. The parent process calls a function to print all Armstrong numbers up to n.
*/

#include <stdio.h>
#include <unistd.h>

void fibonacci(int n)
{
    int a = 0, b = 1, next;

    printf("Child Process - Fibonacci Series:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        next = a + b;
        a = b;
        b = next;
    }

    printf("\n");
}

void armstrong(int n)
{
    int i, temp, digit, sum;

    printf("Parent Process - Armstrong Numbers:\n");

    for (i = 1; i <= n; i++) {
        temp = i;
        sum = 0;

        while (temp != 0) {
            digit = temp % 10;
            sum = sum + (digit * digit * digit);
            temp = temp / 10;
        }

        if (sum == i) {
            printf("%d ", i);
        }
    }

    printf("\n");
}

int main(void)
{
    int n;
    pid_t pid;

    printf("Enter n: ");
    scanf("%d", &n);

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        fibonacci(n);
    }
    else {
        // Parent process
        armstrong(n);
    }

    return 0;
}