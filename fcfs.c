#include <stdio.h>


void calculateTimes(int processes[], int n, int at[], int bt[], int ct[], int tat[], int wt[]) {
    int completion = 0;

    for (int i = 0; i < n; i++) {
        if (completion < at[i]) {
            completion = at[i];
        }
        completion += bt[i];
        ct[i] = completion;
        tat[i] = ct[i] - at[i];
        wt[i]=tat[i]-bt[i];
    }
}


void displayResults(int processes[], int n, int at[], int bt[], int ct[], int tat[], int wt[]) {
    float total_tat = 0, total_wt = 0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        total_tat += tat[i];
        total_wt += wt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
}

int main() {
    int n ;
    printf("Enter no. of processes : ");
    scanf("%d",&n);
    int processes[n];
    for(int i=0;i<n;i++){
        processes[i]=i+1;
           }

    int at[n];
    for(int i=0;i<n;i++){
        printf("Enter arrival time of process %d : ",processes[i]);
        scanf("%d",&at[i]);
           }
    int bt[n];
    for(int i=0;i<n;i++){
        printf("Enter burst time of process %d : ",processes[i]);
        scanf("%d",&bt[i]);
           }
    int ct[n], tat[n], wt[n], rt[n];

    calculateTimes(processes, n, at, bt, ct, tat, wt);
    displayResults(processes, n, at, bt, ct, tat, wt);

    return 0;
}



