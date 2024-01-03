#include <stdio.h>
#include <stdlib.h>
#include "src/utils/proc.h"

// Function to find the process with shortest burst time
int find_shortest(struct proc_info *processes, int n)
{
    int min = 0;
    for (int i = 1; i < n; i++)
    {
        if (processes[i].burst_time < processes[min].burst_time)
            min = i;
    }
    return min;
}

void sjf(struct proc_info *processes, int n)
{
    while (n > 0)
    {
        // Find process with shortest burst time
        int shortest = find_shortest(processes, n);

        // Print process info
        printf("Executing process %d with burst time %lld\n", processes[shortest].pid, processes[shortest].burst_time);

        // Remove shortest process from array
        for (int i = shortest; i < n - 1; i++)
        {
            processes[i] = processes[i + 1];
        }
        n--;
    }
}

int main()
{
    // struct proc_info processes[NUM_PROCESSES] = {
    //     {1, "P1", 0, 0, 10},
    //     {2, "P2", 0, 0, 5},
    //     {3, "P3", 0, 0, 8},
    //     {4, "P4", 0, 0, 15},
    //     {5, "P5", 0, 0, 2}};
    int num_processes;

    // Taking input for the number of processes and quantum
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    struct proc_info *processes = get_proc_info(&num_processes);
    for (int i = 0; i < num_processes; i++)
    {
        printf("PID: %d, Name: %s, Priority: %d, Burst Time: %lld, Arrival Time: %ld\n", processes[i].pid, processes[i].name, processes[i].priority, processes[i].burst_time, processes[i].arrival_time);
    }

    sjf(processes, num_processes);

    return 0;
}