/*
Week 3 - Classwork - Question 2
Write a program to read a string from the user within the child process
and then print all the permutations of the characters of the given string.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void permute(char str[], int left, int right)
{
    if (left == right) {
        printf("%s\n", str);
        return;
    }

    for (int i = left; i <= right; i++) {
        char temp = str[left];
        str[left] = str[i];
        str[i] = temp;

        permute(str, left + 1, right);

        temp = str[left];
        str[left] = str[i];
        str[i] = temp;
    }
}

int main(void)
{
    char str[20];
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Enter a string: ");
        scanf("%s", str);

        printf("\nPermutations:\n");
        permute(str, 0, strlen(str) - 1);
    }

    return 0;
}