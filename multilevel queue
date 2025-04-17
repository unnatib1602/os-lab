#include <stdio.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2

typedef struct {
    int id;
    int burst_time;
    int arrival_time;
    int queue; // 1 for system process (RR), 2 for user process (FCFS)
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
} Process;

void round_robin(Process processes[], int n, int tq, int *time) {
    int done, i;
    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (processes[i].queue == 1 && processes[i].remaining_time > 0) {
                done = 0;
                if (processes[i].remaining_time == processes[i].burst_time)
                    processes[i].response_time = *time - processes[i].arrival_time;
                if (processes[i].remaining_time > tq) {
                    *time += tq;
                    processes[i].remaining_time -= tq;
                } else {
                    *time += processes[i].remaining_time;
                    processes[i].waiting_time = *time - processes[i].burst_time - processes[i].arrival_time;
                    processes[i].turnaround_time = *time - processes[i].arrival_time;
                    processes[i].remaining_time = 0;
                }
            }
        }
    } while (!done);
}

void fcfs(Process processes[], int n, int *time) {
    for (int i = 0; i < n; i++) {
        if (processes[i].queue == 2) {
            if (*time < processes[i].arrival_time)
                *time = processes[i].arrival_time;
            processes[i].response_time = *time - processes[i].arrival_time;
            processes[i].waiting_time = *time - processes[i].arrival_time;
            *time += processes[i].burst_time;
            processes[i].turnaround_time = *time - processes[i].arrival_time;
        }
    }
}

void calculate_average(Process processes[], int n) {
    float total_waiting = 0, total_turnaround = 0, total_response = 0;
    for (int i = 0; i < n; i++) {
        total_waiting += processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
        total_response += processes[i].response_time;
    }
    printf("\nAverage Waiting Time: %.2f", total_waiting / n);
    printf("\nAverage Turn Around Time: %.2f", total_turnaround / n);
    printf("\nAverage Response Time: %.2f", total_response / n);
    printf("\nThroughput: %.2f\n", n / (total_turnaround / n));
}

int main() {
    int n, time = 0;
    Process processes[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Queue 1 is system process\nQueue 2 is User Process\n");

    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time, Arrival Time and Queue of P%d: ", i + 1);
        scanf("%d %d %d", &processes[i].burst_time, &processes[i].arrival_time, &processes[i].queue);
        processes[i].id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].response_time = 0;
    }

    round_robin(processes, n, TIME_QUANTUM, &time);
    fcfs(processes, n, &time);

    printf("\nProcess\tWaiting Time\tTurn Around Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t\t%d\n", processes[i].id, processes[i].waiting_time, processes[i].turnaround_time, processes[i].response_time);
    }

    calculate_average(processes, n);

    return 0;
}
