/*
Week 7 - Classwork - Question 3
Write a C program to implement non-preemptive Priority Scheduling.
A smaller priority number means a higher priority. Calculate the
waiting time and turnaround time of each process, and the averages.
*/

#include <stdio.h>

int main(void)
{
    int n, temp;
    int pid[20], bt[20], priority[20], wt[20], tat[20];
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;

        printf("P%d burst time: ", i + 1);
        scanf("%d", &bt[i]);

        printf("P%d priority: ", i + 1);
        scanf("%d", &priority[i]);
    }

    // Sort processes by priority (smallest number first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (priority[i] > priority[j]) {
                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avgWT = avgWT + wt[i];
        avgTAT = avgTAT + tat[i];
    }

    printf("\nProcess\tPriority\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t%d\t%d\n", pid[i], priority[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", avgWT / n);
    printf("Average Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}
