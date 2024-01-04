#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../utils/proc.h"

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

// void sjf(struct proc_info *processes, int n)
// {
//     while (n > 0)
//     {
//         // Find process with shortest burst time
//         int shortest = find_shortest(processes, n);

//         // Print process info
//         printf("Executing process %d with burst time %lld\n", processes[shortest].pid, processes[shortest].burst_time);

//         // Remove shortest process from array
//         for (int i = shortest; i < n - 1; i++)
//         {
//             processes[i] = processes[i + 1];
//         }
//         n--;
//     }
// }

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
    fprintf(file, "gantt\n    title SJF Scheduling\n    dateFormat  X\n    section Section\n");

    time_t now = time(NULL);

    while (n > 0)
    {
        // Find process with shortest burst time
        int shortest = find_shortest(processes, n);

        // Print process info
        printf("Executing process %d with burst time %lld\n", processes[shortest].pid, processes[shortest].burst_time);

        // Write the process info to the Gantt chart file
        fprintf(file, "    Task %d          :a%d, %lld, %llds\n", processes[shortest].pid, processes[shortest].pid, now, processes[shortest].burst_time);

        // Update the current time
        now += processes[shortest].burst_time;

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