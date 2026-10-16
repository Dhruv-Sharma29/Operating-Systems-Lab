/*
Week 5 - Classwork - Question 1 (Writer)
Demonstrate Inter-Process Communication (IPC) using a Named Pipe (FIFO).
Create a FIFO named "myfifo", open it for writing, accept a message from
the user, and write it to the FIFO.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char message[100];

    if (mkfifo("myfifo", 0666) == -1) {
        perror("mkfifo");
    }

    fd = open("myfifo", O_WRONLY);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);

    write(fd, message, strlen(message) + 1);

    close(fd);
    return 0;
}