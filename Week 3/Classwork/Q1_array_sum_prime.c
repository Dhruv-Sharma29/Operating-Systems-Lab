/*
Week 3 - Classwork - Question 1
Write a program to find the sum of elements in an array within the child
process and then check whether the given sum is prime or not.
*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int n, arr[100], sum = 0;
    int isPrime = 1;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process - Calculate sum
        for (int i = 0; i < n; i++) {
            sum = sum + arr[i];
        }

        printf("Child Process: Sum = %d\n", sum);

        // Check whether sum is prime
        if (sum <= 1) {
            isPrime = 0;
        }

        for (int i = 2; i * i <= sum; i++) {
            if (sum % i == 0) {
                isPrime = 0;
                break;
            }
        }

        if (isPrime)
            printf("The sum %d is Prime.\n", sum);
        else
            printf("The sum %d is Not Prime.\n", sum);
    }

    return 0;
}