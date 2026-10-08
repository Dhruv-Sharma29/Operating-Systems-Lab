/*
Week 4 - Classwork - Question 2
Write a program to create input.txt in the parent process and write
your name, university roll number, and class in it. Then read the same
file in the child process and print its contents.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    FILE *file;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        // Parent process - Create and write to file
        file = fopen("input.txt", "w");

        if (file == NULL) {
            perror("File creation failed");
            return 1;
        }

        fprintf(file, "Name: Rahul Mehta\n");
        fprintf(file, "University Roll Number: 23CSE1047\n");
        fprintf(file, "Class: CSE-A\n");

        fclose(file);

        printf("Parent Process: Data written to input.txt\n");

        wait(NULL);
    }
    else {
        // Child process
        sleep(1);

        file = fopen("input.txt", "r");

        if (file == NULL) {
            perror("File opening failed");
            return 1;
        }

        char ch;

        printf("\nChild Process: Contents of input.txt\n");

        while ((ch = fgetc(file)) != EOF) {
            printf("%c", ch);
        }

        fclose(file);
    }

    return 0;
}