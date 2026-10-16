/*
Week 5 - Classwork - Question 1 (Reader)
Demonstrate Inter-Process Communication (IPC) using a Named Pipe (FIFO).
Open the existing FIFO named "myfifo" for reading, receive the message sent
by the writer process, and display it.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char message[100];

    fd = open("myfifo", O_RDONLY);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    read(fd, message, sizeof(message));
    printf("Received message: %s\n", message);

    close(fd);
    return 0;
}