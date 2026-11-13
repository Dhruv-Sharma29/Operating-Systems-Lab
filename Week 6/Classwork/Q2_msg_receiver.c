/*
Week 6 - Classwork - Question 2 (Receiver)
Demonstrate Inter-Process Communication (IPC) using a System V Message Queue.
Access the message queue created by the sender, receive a message of
type 1, display it, and then remove the queue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long type;
    char text[100];
};

int main(void)
{
    key_t key;
    int msgid;
    struct message msg;

    // Generate the same key used by the sender
    key = ftok(".", 'A');

    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Wait for a message of type 1
    if (msgrcv(msgid, &msg, sizeof(msg.text), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Received: %s", msg.text);

    // Remove the queue from the system
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
