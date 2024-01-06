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
    // Open the Gantt chart file
    FILE *file = fopen("gantt.mmd", "w");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    // Write the Gantt chart header to the file
    // fprintf(file, "---\ndisplayMode: compact\n---\ngantt\n    title SJF Scheduling\n    dateFormat  X\n     axisFormat %%s\n section Section\n");
    fprintf(file, "gantt\n    title SJF Scheduling\n    dateFormat  X\n     axisFormat %%s\n section Section\n");

    int total_burst_time = 0;

    while (n > 0)
    {
        // Find process with shortest burst time
        int shortest = find_shortest(processes, n);

        // Print process info
        printf("Executing process %d with burst time %d\n", processes[shortest].pid, processes[shortest].normalized_burst_time);

        // Calculate the duration in seconds
        int duration = processes[shortest].normalized_burst_time;

        // Write the process info to the Gantt chart file
        fprintf(file, "    PID %d          : %d, %d\n", processes[shortest].pid, total_burst_time, total_burst_time + duration);

        // Update the total burst time
        total_burst_time += duration;

        // Remove shortest process from array
        for (int i = shortest; i < n - 1; i++)
        {
            processes[i] = processes[i + 1];
        }
        n--;
    }

    // Close the Gantt chart file
    fclose(file);
}