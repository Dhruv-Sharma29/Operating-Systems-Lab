/*
Week 6 - Classwork - Question 1 (Reader)
Demonstrate Inter-Process Communication (IPC) using Shared Memory.
Attach the existing shared memory segment created by the writer, display
the data stored in it, and then remove the segment.
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

    // Generate the same key used by the writer
    key = ftok(".", 'S');

    // Access the existing segment (no IPC_CREAT)
    shmid = shmget(key, 1024, 0666);

    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shared = (char *)shmat(shmid, NULL, 0);

    if (shared == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Data received: %s", shared);

    shmdt(shared);

    // Remove the segment from the system
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
