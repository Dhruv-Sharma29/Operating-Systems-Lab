/*
Week 1 - Classwork - Question 4
Write a C program in which the child process prints the Fibonacci series
up to n, while the parent process calculates and prints the factorial
of a given number.
*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int n, num;
    pid_t pid;

    printf("Enter n for Fibonacci series: ");
    scanf("%d", &n);

    printf("Enter number for factorial: ");
    scanf("%d", &num);

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process - Fibonacci series
        int a = 0, b = 1, next;

        printf("\nChild Process - Fibonacci Series:\n");

        for (int i = 0; i < n; i++) {
            printf("%d ", a);
            next = a + b;
            a = b;
            b = next;
        }

        printf("\n");
    }
    else {
        // Parent process - Factorial
        long long factorial = 1;

        for (int i = 1; i <= num; i++) {
            factorial *= i;
        }

        printf("\nParent Process - Factorial:\n");
        printf("%d! = %lld\n", num, factorial);
    }

    return 0;
}