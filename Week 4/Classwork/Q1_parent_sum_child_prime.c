/*
Week 4 - Classwork - Question 1
Write a program to calculate the sum of an array in the parent process
and then check whether the calculated sum is prime or not in the
child process using pipe().
*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int n, arr[100], sum = 0;
    int pipefd[2];
    int isPrime = 1;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pipe(pipefd);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        // Parent process - Calculate sum
        close(pipefd[0]);

        for (int i = 0; i < n; i++) {
            sum = sum + arr[i];
        }

        printf("Parent Process: Sum = %d\n", sum);

        // Send sum to child
        write(pipefd[1], &sum, sizeof(sum));

        close(pipefd[1]);
    }
    else {
        // Child process - Check whether sum is prime
        close(pipefd[1]);

        // Receive sum from parent
        read(pipefd[0], &sum, sizeof(sum));

        close(pipefd[0]);

        if (sum <= 1) {
            isPrime = 0;
        }

        for (int i = 2; i * i <= sum; i++) {
            if (sum % i == 0) {
                isPrime = 0;
                break;
            }
        }

        printf("Child Process: Received Sum = %d\n", sum);

        if (isPrime)
            printf("The sum is Prime.\n");
        else
            printf("The sum is Not Prime.\n");
    }

    return 0;
}