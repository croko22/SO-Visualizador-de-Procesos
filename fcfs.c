#include <stdio.h>
#include <stdlib.h>
#include "src/utils/proc.h"

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

int main()
{
    int num_processes;

    struct proc_info *processes = get_proc_info(&num_processes);
    for (int i = 0; i < num_processes; i++)
    {
        printf("PID: %d, Name: %s, Priority: %d, Burst Time: %lld, Arrival Time: %ld\n", processes[i].pid, processes[i].name, processes[i].priority, processes[i].burst_time, processes[i].arrival_time);
    }

    fcfs(processes, num_processes);
    printf("Number of processes: %d\n", num_processes);

    return 0;
}