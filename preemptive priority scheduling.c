#include <stdio.h>

struct Process {
    int id, arrival_time, burst_time, priority;
    int remaining_bt, completion_time, turnaround_time, waiting_time, response_time;
    int is_completed, is_started;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter Arrival Time, Burst Time and Priority for Process %d: ", p[i].id);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].remaining_bt = p[i].burst_time;
        p[i].is_completed = 0;
        p[i].is_started = 0;
    }

    int current_time = 0, completed = 0;
    float total_tat = 0, total_wt = 0, total_rt = 0;

    while (completed < n) {
        int selected = -1;
        int min_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_bt > 0) {
                if (p[i].priority < min_priority ||
                   (p[i].priority == min_priority && p[i].arrival_time < p[selected].arrival_time)) {
                    min_priority = p[i].priority;
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            current_time++;
        } else {
            if (p[selected].is_started == 0) {
                p[selected].response_time = current_time - p[selected].arrival_time;
                p[selected].is_started = 1;
            }

            p[selected].remaining_bt--;
            current_time++;

            if (p[selected].remaining_bt == 0) {
                p[selected].completion_time = current_time;
                p[selected].turnaround_time = p[selected].completion_time - p[selected].arrival_time;
                p[selected].waiting_time = p[selected].turnaround_time - p[selected].burst_time;
                total_tat += p[selected].turnaround_time;
                total_wt += p[selected].waiting_time;
                total_rt += p[selected].response_time;
                p[selected].is_completed = 1;
                completed++;
            }
        }
    }

    // Display Results
    printf("\nProcess\tAT\tBT\tPri\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].arrival_time, p[i].burst_time, p[i].priority,
               p[i].completion_time, p[i].turnaround_time,
               p[i].waiting_time, p[i].response_time);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);

    return 0;
}
