#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../procesos.h"

// Function to find the process with shortest burst time
int find_shortest(struct info_proceso *processes, int n)
{
    int min = 0;
    for (int i = 1; i < n; i++)
    {
        if (processes[i].tiempo_ráfaga < processes[min].tiempo_ráfaga)
            min = i;
    }
    return min;
}

void sjf(struct info_proceso *processes, int n)
{
    while (n > 0)
    {
        // Find process with shortest burst time
        int shortest = find_shortest(processes, n);

        // Print process info
        printf("Executing process %d with burst time %lld\n", processes[shortest].pid, processes[shortest].tiempo_ráfaga);

        // Remove shortest process from array
        for (int i = shortest; i < n - 1; i++)
        {
            processes[i] = processes[i + 1];
        }
        n--;
    }
}