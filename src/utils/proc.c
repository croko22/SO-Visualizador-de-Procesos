#include "proc.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <limits.h>

// Function to get process information
struct proc_info *get_proc_info(int *count)
{
    //* Open the CSV file
    FILE *file = fopen("data/processes.csv", "w");
    fprintf(file, "PID,Name,Priority,Arrival Time,Burst Time\n");

    DIR *dirp;
    struct dirent *dp;

    // Allocate memory for the array
    int max_processes = 1024; // Adjust this value as needed
    struct proc_info *processes = malloc(max_processes * sizeof(struct proc_info));

    if (processes == NULL)
    {
        perror("Failed to allocate memory for processes array");
        return NULL;
    }

    dirp = opendir("/proc");
    if (dirp == NULL)
    {
        perror("Failed to open directory \"/proc\"");
        free(processes);
        return NULL;
    }

    int process_count = 0;
    while ((dp = readdir(dirp)) != NULL)
    {
        if (atoi(dp->d_name) > 0)
        {
            char stat_path[256];
            sprintf(stat_path, "/proc/%s/stat", dp->d_name);

            FILE *fp = fopen(stat_path, "r");
            if (fp == NULL)
            {
                perror("Failed to open stat file");
                continue;
            }

            struct proc_info info;

            // Get process information from /proc/<pid>/stat
            int utime, stime, starttime;
            fscanf(fp, "%d %s %*c %d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %*lu %*ld %*ld %*ld %d",
                   &info.pid, info.name, &info.priority, &utime, &stime, &starttime);
            fclose(fp);

            info.burst_time = (utime + stime);

            // Calculate the arrival time
            long uptime;
            FILE *fp_uptime = fopen("/proc/uptime", "r");
            fscanf(fp_uptime, "%ld", &uptime);
            fclose(fp_uptime);
            info.arrival_time = uptime - starttime;

            //? Write the process info to the CSV file
            fprintf(file, "%d,%s,%d,%ld,%lld\n", info.pid, info.name, info.priority, info.arrival_time, info.burst_time);

            // Check if we need to resize the array
            if (process_count >= max_processes)
            {
                max_processes *= 2;
                struct proc_info *temp = realloc(processes, max_processes * sizeof(struct proc_info));
                if (temp == NULL)
                {
                    perror("Failed to resize processes array");
                    free(processes);
                    return NULL;
                }
                processes = temp;
            }

            processes[process_count++] = info;
        }
    }
    closedir(dirp);

    fclose(file);
    // Update the count and return the array
    *count = process_count;

    // Initialize min and max values
    int min_burst_time = INT_MAX;
    int max_burst_time = INT_MIN;

    // Calculate min and max values
    for (int i = 0; i < process_count; i++)
    {
        if (processes[i].burst_time < min_burst_time)
        {
            min_burst_time = processes[i].burst_time;
        }
        if (processes[i].burst_time > max_burst_time)
        {
            max_burst_time = processes[i].burst_time;
        }
    }

    // Now you can normalize the data
    for (int i = 0; i < process_count; i++)
    {
        // processes[i].normalized_burst_time = (processes[i].burst_time - min_burst_time) / (double)(max_burst_time - min_burst_time);
        processes[i].normalized_burst_time = (processes[i].burst_time - min_burst_time) / (double)(max_burst_time - min_burst_time) * 100;
        // processes[i].normalized_burst_time = (int)round((double)processes[i].burst_time / max_burst_time * 100);
    }

    return processes;
}