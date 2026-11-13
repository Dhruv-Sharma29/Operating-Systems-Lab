/*
Week 6 - Classwork - Question 1 (Writer)
Demonstrate Inter-Process Communication (IPC) using Shared Memory.
Create a shared memory segment, attach it to the process, accept a
message from the user, and write it into the shared memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
    key_t key;
    int shmid;
    char *shared;

    // Generate the same key in writer and reader
    key = ftok(".", 'S');

    // Create a 1024-byte shared memory segment
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the segment to this process
    shared = (char *)shmat(shmid, NULL, 0);

    if (shared == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Enter data: ");
    fgets(shared, 1024, stdin);

    printf("Data written to shared memory.\n");

    // Detach the segment (the data stays in memory)
    shmdt(shared);

    return 0;
}
