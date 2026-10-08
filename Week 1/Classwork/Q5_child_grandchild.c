/*
Week 1 - Classwork - Question 5
Write a C program that uses fork() to create a child process. The child
process prints the Fibonacci series and then creates another child
process using fork(). This second child process prints the factorial
of a given number, while the original parent process calculates and
prints the sum of the first n natural numbers.
*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int n, num;
    pid_t pid1, pid2;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter number for factorial: ");
    scanf("%d", &num);

    pid1 = fork();

    if (pid1 < 0) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {
        // First child process - Fibonacci series
        int a = 0, b = 1, next;

        printf("\nFirst Child - Fibonacci Series:\n");

        for (int i = 0; i < n; i++) {
            printf("%d ", a);
            next = a + b;
            a = b;
            b = next;
        }

        printf("\n");

        // First child creates another child
        pid2 = fork();

        if (pid2 < 0) {
            perror("fork");
            return 1;
        }

        if (pid2 == 0) {
            // Second child process - Factorial
            long long factorial = 1;

            for (int i = 1; i <= num; i++) {
                factorial *= i;
            }

            printf("\nSecond Child - Factorial:\n");
            printf("%d! = %lld\n", num, factorial);
        }
    }
    else {
        // Original parent process - Sum of first n natural numbers
        int sum = 0;

        for (int i = 1; i <= n; i++) {
            sum += i;
        }

        printf("\nOriginal Parent - Sum of First %d Natural Numbers:\n", n);
        printf("Sum = %d\n", sum);
    }

    return 0;
}