/*
Week 7 - Classwork - Question 5
Write a C program to implement the Least Recently Used (LRU) page
replacement algorithm. Display the frames after each page reference and
calculate the total number of page faults.
*/

#include <stdio.h>

int main(void)
{
    int pages[100], frames[20], lastUsed[20];
    int n, f, found, position;
    int faults = 0, time = 0;

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
        lastUsed[i] = -1;
    }

    printf("\nPage\tFrames\n");

    for (int i = 0; i < n; i++) {
        found = -1;
        time++;

        // Check whether the page is already in a frame (page hit)
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            // Page hit - update its last used time
            lastUsed[found] = time;
        }
        else {
            // Page fault - use an empty frame if available
            position = -1;

            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    position = j;
                    break;
                }
            }

            // No empty frame - replace the least recently used page
            if (position == -1) {
                position = 0;

                for (int j = 1; j < f; j++) {
                    if (lastUsed[j] < lastUsed[position]) {
                        position = j;
                    }
                }
            }

            frames[position] = pages[i];
            lastUsed[position] = time;
            faults++;
        }

        printf("%d\t", pages[i]);

        for (int j = 0; j < f; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if (found != -1)
            printf("\tHit");
        else
            printf("\tFault");

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
