#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/proc.h"

// Function to find the process with earliest arrival time
int find_earliest(struct proc_info *processes, int n)
{
    int min = 0;
    for (int i = 1; i < n; i++)
    {
        if (processes[i].arrival_time < processes[min].arrival_time)
            min = i;
    }
    return min;
}

void fcfs(struct proc_info *processes, int n)
{
    FILE *file = fopen("data/fcfs.csv", "w");
    fprintf(file, "pid,name,normalized_burst_time,arrival_time,waiting_time,turnaround_time\n");

    int current_time = 0;
    int n_copy = n;

    while (n > 0)
    {
        // Find the process with the earliest arrival time
        int earliest = find_earliest(processes, n);

        // Calculate waiting time and turnaround time
        processes[earliest].waiting_time = current_time;
        processes[earliest].turnaround_time = processes[earliest].waiting_time + processes[earliest].normalized_burst_time;

        fprintf(file, "%d, %s,%lld,%d,%d,%d\n", processes[earliest].pid, processes[earliest].name, processes[earliest].normalized_burst_time, processes[earliest].arrival_time, processes[earliest].waiting_time, processes[earliest].turnaround_time);

        current_time += processes[earliest].normalized_burst_time;

        // Remove the earliest process from the array
        for (int i = earliest; i < n - 1; i++)
        {
            processes[i] = processes[i + 1];
        }
        n--;
    }

    fclose(file); // Close the file properly
}