#include<stdio.h>  

int main() {  
    int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0, at[10], bt[10], temp[10];  
    float avg_wt, avg_tat;  
    
    // Input the number of processes
    printf("Total number of processes in the system: ");  
    scanf("%d", &NOP);      
    y = NOP;  // Store the number of processes

    // Input arrival and burst time for each process
    for(i = 0; i < NOP; i++) {  
        printf("\nEnter the Arrival and Burst time of Process[%d]\n", i + 1);  
        printf("Arrival time: \t");  
        scanf("%d", &at[i]);  
        printf("Burst time: \t");  
        scanf("%d", &bt[i]);  
        temp[i] = bt[i];  // Store the burst time in temp array
    }  
    
    // Input the time quantum
    printf("Enter the Time Quantum for the process: \t");  
    scanf("%d", &quant);  
    
    printf("\nProcess No \t Burst Time \t Turnaround Time \t Waiting Time ");  
    
    // Round Robin scheduling logic
    for(sum = 0, i = 0; y != 0;) {  
        if(temp[i] <= quant && temp[i] > 0) {  
            sum = sum + temp[i];  
            temp[i] = 0;  
            count = 1;  
        } else if(temp[i] > 0) {  
            temp[i] = temp[i] - quant;  
            sum = sum + quant;    
        }  
        
        if(temp[i] == 0 && count == 1) {  
            y--;  // Process is completed
            printf("\nProcess[%d] \t\t %d \t\t %d \t\t %d", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);  
            wt = wt + sum - at[i] - bt[i];  // Calculate total waiting time
            tat = tat + sum - at[i];        // Calculate total turnaround time
            count = 0;     
        }  
        
        // Move to the next process
        if(i == NOP - 1) {  
            i = 0;  
        } else if(at[i + 1] <= sum) {  
            i++;  
        } else {  
            i = 0;  
        }  
    }  
    
    // Calculate average waiting time and average turnaround time
    avg_wt = (float)wt / NOP;  
    avg_tat = (float)tat / NOP;  
    
    printf("\n\nAverage Turnaround Time: \t%.2f", avg_tat);  
    printf("\nAverage Waiting Time: \t\t%.2f\n", avg_wt);  
    
    return 0;  
}
