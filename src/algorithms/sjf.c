#include <stdio.h>
#include <stdlib.h>
#include "../utils/proc.h"

// Function to find the process with shortest burst time
int find_shortest(struct proc_info *processes, int n)
{
    int min = 0;
    for (int i = 1; i < n; i++)
    {
        if (processes[i].normalized_burst_time < processes[min].normalized_burst_time)
            min = i;
    }
    return min;
}

void sjf(struct proc_info *processes, int n)
{
    int current_time = 0;
    struct proc_info *completed_processes = malloc(sizeof(struct proc_info) * n);
    int completed_count = 0;

    while (n > 0)
    {
        // Find process with shortest burst time
        int shortest = find_shortest(processes, n);

        // Calculate waiting time and turnaround time
        processes[shortest].waiting_time = current_time;
        processes[shortest].turnaround_time = processes[shortest].waiting_time + processes[shortest].normalized_burst_time;

        // Store completed process
        completed_processes[completed_count++] = processes[shortest];

        // Update current time
        current_time += processes[shortest].normalized_burst_time;

        // Remove shortest process from array
        for (int i = shortest; i < n - 1; i++)
        {
            processes[i] = processes[i + 1];
        }
        n--;
    }

    // Open the CSV file
    FILE *file = fopen("data/sjf.csv", "w");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    // Write the header to the CSV file
    fprintf(file, "PID,Normalized Burst Time,Arrival Time,Waiting Time,Turnaround Time\n");

    // Write the process data to the CSV file
    for (int i = 0; i < completed_count; i++)
    {
        fprintf(file, "%d,%d,%ld,%d,%d\n", completed_processes[i].pid, completed_processes[i].normalized_burst_time, completed_processes[i].arrival_time, completed_processes[i].waiting_time, completed_processes[i].turnaround_time);
    }

    fclose(file);
    free(completed_processes);
}