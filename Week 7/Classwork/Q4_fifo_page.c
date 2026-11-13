/*
Week 7 - Classwork - Question 4
Write a C program to implement the FIFO page replacement algorithm.
Display the frames after each page reference and calculate the total
number of page faults.
*/

#include <stdio.h>

int main(void)
{
    int pages[100], frames[20];
    int n, f, found;
    int pointer = 0, faults = 0;

    printf("Enter reference string length: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // -1 means the frame is empty
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\n");

    for (int i = 0; i < n; i++) {
        found = 0;

        // Check whether the page is already in a frame (page hit)
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // Page fault - replace the oldest page
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % f;
            faults++;
        }

        printf("%d\t", pages[i]);

        for (int j = 0; j < f; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if (found)
            printf("\tHit");
        else
            printf("\tFault");

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
