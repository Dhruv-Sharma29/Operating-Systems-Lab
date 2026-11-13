/*
Week 7 - Classwork - Question 1
Write a C program to implement First-Come, First-Served (FCFS) CPU
scheduling. Calculate the waiting time and turnaround time of each
process, and the average waiting time and turnaround time.
Execute it for: P1 = 24, P2 = 3, P3 = 3 (burst times).
*/

#include <stdio.h>

int main(void)
{
    int n, bt[20], wt[20], tat[20];
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst times:\n");

    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // First process does not wait
    wt[0] = 0;

    // Each process waits for all processes before it
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avgWT = avgWT + wt[i];
        avgTAT = avgTAT + tat[i];
    }

    printf("\nProcess\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", avgWT / n);
    printf("Average Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}
