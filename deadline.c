#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int burst;
    int deadline;
    int period;
} Process;

void sortByDeadline(Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].deadline > proc[j + 1].deadline) {
                Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

void main() {
    int n;
    printf("Enter the number of processes:");
    scanf("%d", &n);

    Process proc[n];

    printf("\nEnter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &proc[i].burst);
        proc[i].pid = i + 1;
    }

    printf("\nEnter the deadlines:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &proc[i].deadline);
    }

    printf("\nEnter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &proc[i].period);
    }

    sortByDeadline(proc, n);

    printf("\nEarliest Deadline Scheduling:\n");
    printf("PID    Burst    Deadline    Period\n");
    for (int i = 0; i < n; i++) {
        printf("%d      %d        %d          %d\n", proc[i].pid, proc[i].burst, proc[i].deadline, proc[i].period);
    }
    printf("\nScheduling occurs for 6 ms\n");
    for (int time = 0; time < 6; time++) {
        printf("%dms : Task %d is running.\n", time, proc[0].pid);
    }
}
