#include <stdio.h>
#include <stdlib.h>
#include "../utils/proc.h"
void rr(struct proc_info *processes, int num_processes)
{
    int time_quantum = 3;
    int *remaining_times = malloc(sizeof(int) * num_processes);
    int total_time = 0;

    struct proc_info *completed_processes = malloc(sizeof(struct proc_info) * num_processes);
    int completed_count = 0;

    // Get the burst times of the processes and calculate the total time
    for (int i = 0; i < num_processes; i++)
    {
        remaining_times[i] = processes[i].normalized_burst_time;
        total_time += processes[i].normalized_burst_time;
    }

    // Execute the processes in Round Robin fashion
    int *started = calloc(num_processes, sizeof(int)); // to track if a process has started
    int current_time = 0;                              // Initialize current_time to 0

    while (total_time > 0)
    {
        for (int i = 0; i < num_processes; i++)
        {
            if (remaining_times[i] > 0)
            {
                if (!started[i])
                {
                    processes[i].waiting_time = current_time;
                    started[i] = 1;
                }

                int execution_time = remaining_times[i] > time_quantum ? time_quantum : remaining_times[i];
                current_time += execution_time;
                remaining_times[i] -= execution_time;
                total_time -= execution_time;

                if (remaining_times[i] == 0)
                {
                    processes[i].turnaround_time = current_time;
                    completed_processes[completed_count++] = processes[i];
                }
            }
        }
    }

    // Open the CSV file
    FILE *file = fopen("data/rr.csv", "w");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    // Write the header to the CSV file
    fprintf(file, "pid,name,normalized_burst_time,arrival_time,waiting_time,turnaround_time\n");

    // Write the process data to the CSV file
    for (int i = 0; i < completed_count; i++)
    {
        fprintf(file, "%d,%s,%d,%ld,%d,%d\n", completed_processes[i].pid, completed_processes[i].name, completed_processes[i].normalized_burst_time, completed_processes[i].arrival_time, completed_processes[i].waiting_time, completed_processes[i].turnaround_time);
    }

    fclose(file);
    free(remaining_times);
    free(started);
    free(completed_processes);
}