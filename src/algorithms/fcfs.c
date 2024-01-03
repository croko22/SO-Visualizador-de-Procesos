#include <stdio.h>
#include <stdlib.h>
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
    while (n > 0)
    {
        // Find process with earliest arrival time
        int earliest = find_earliest(processes, n);

        // Print process info
        printf("Executing process %d with burst time %lld\n", processes[earliest].pid, processes[earliest].burst_time);

        // Remove earliest process from array
        for (int i = earliest; i < n - 1; i++)
        {
            processes[i] = processes[i + 1];
        }
        n--;
    }
}