/*
Week 6 - Classwork - Question 2 (Sender)
Demonstrate Inter-Process Communication (IPC) using a System V Message Queue.
Create a message queue, accept a message from the user, and send it to the
queue with message type 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    // Generate the same key in sender and receiver
    key = ftok(".", 'A');

    // Create the queue, or open it if it already exists
    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    msg.type = 1;

    printf("Enter message: ");
    fgets(msg.text, sizeof(msg.text), stdin);

    // Size does not include the long type field
    if (msgsnd(msgid, &msg, strlen(msg.text) + 1, 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent.\n");

    return 0;
}
