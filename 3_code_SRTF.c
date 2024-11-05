#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int at;  // Arrival time
    int bt;  // Burst time
    int ct;  // Completion time
    int tt;  // Turnaround time
    int wt;  // Waiting time
    int rt;  // Response time
    int st;  // Start time
};

int main() {
    int size = 0;
    printf("Enter number of processes: ");
    scanf("%d", &size);

    struct Process ps[size];
    
    printf("\nEnter process Details:\n");
    for (int i = 0; i < size; ++i) {
        printf("Enter %dth process details: \n", i + 1);
        ps[i].pid = i + 1;
        printf("\tEnter Arrival Time: ");
        scanf("%d", &ps[i].at);
        printf("\tEnter Burst Time: ");
        scanf("%d", &ps[i].bt);
    }

    printf("\n=============================================================\n\n");
    printf("PID\tAT\tBT\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt);
    }
    printf("\n=============================================================\n\n");

    // Input Done
    int n = size;
    int completed = 0;
    int currentTime = 0;
    int burstTimeR[n];
    bool isCompleted[n];
    
    // Initialize arrays
    for (int i = 0; i < n; i++) {
        burstTimeR[i] = ps[i].bt;  // Remaining burst times
        isCompleted[i] = false;    // Marks processes as not completed
    }
    
    float avgWT = 0, avgTT = 0, avgRT = 0;
    
    // Simulation loop
    while (completed != n) {
        int minimum = 99999;
        int miniI = -1;

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < n; i++) {
            if ((ps[i].at <= currentTime) && !isCompleted[i]) {
                if (burstTimeR[i] < minimum) {
                    minimum = burstTimeR[i];
                    miniI = i;
                }
                if (burstTimeR[i] == minimum) {
                    if (ps[i].at < ps[miniI].at) {
                        miniI = i;
                    }
                }
            }
        }

        if (miniI == -1) {
            currentTime++;  // No process is ready to execute
        } else {
            if (burstTimeR[miniI] == ps[miniI].bt) {
                ps[miniI].st = currentTime;  // Start time of the process
            }
            burstTimeR[miniI] -= 1;  // Execute the process for 1 time unit
            currentTime++;            // Increment current time

            if (burstTimeR[miniI] == 0) {  // Process is completed
                ps[miniI].ct = currentTime;  // Completion time
                ps[miniI].tt = ps[miniI].ct - ps[miniI].at;  // Turnaround time
                ps[miniI].wt = ps[miniI].tt - ps[miniI].bt;  // Waiting time
                ps[miniI].rt = ps[miniI].st - ps[miniI].at;  // Response time

                avgWT += ps[miniI].wt;
                avgTT += ps[miniI].tt;
                avgRT += ps[miniI].rt;

                completed++;  // Process is marked as completed
                isCompleted[miniI] = true;
            }
        }
    }

    // Output results
    printf("PID\tAT\tBT\tCT\tTT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, 
               ps[i].ct, ps[i].tt, ps[i].wt, ps[i].rt);
    }

    printf("\n=============================================================\n");
    printf("\nAVG WT: %.2f", avgWT / n);
    printf("\nAVG TT: %.2f", avgTT / n);
    printf("\nAVG RT: %.2f", avgRT / n);
    printf("\n=============================================================\n");

    return 0;
}
