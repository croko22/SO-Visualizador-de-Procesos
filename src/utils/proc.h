#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

// Define a struct to hold the process info
struct proc_info
{
    int pid;
    char name[256];
    int priority;
    long utime;
    long stime;
    long starttime;
    long long burst_time;
    long arrival_time;
};

// struct proc_info *get_proc_info(int *count)
struct proc_info *get_proc_info()
{
    DIR *dirp;
    struct dirent *dp;

    // Allocate memory for the array
    int max_processes = 1024; // Adjust this value as needed
    struct proc_info *processes = malloc(max_processes * sizeof(struct proc_info));

    // Check if memory allocation was successful
    if (processes == NULL)
    {
        perror("Failed to allocate memory for processes array");
        return NULL;
    }

    dirp = opendir("/proc");
    if (dirp == NULL)
    {
        perror("Failed to open directory \"/proc\"");
        return NULL;
    }

    int process_count = 0;
    while ((dp = readdir(dirp)) != NULL)
    {
        if (dp != NULL && atoi(dp->d_name) > 0)
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

            //* Get line stat
            fscanf(fp, "%d %s %*c %*d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %ld %ld %*d %*d %*d %*d %ld",
                   &info.pid, info.name, &info.utime, &info.stime, &info.starttime);

            long long burst_time = info.utime + info.stime; // Change type to long long
            info.burst_time = burst_time;

            // Calculate the arrival time
            long uptime;
            FILE *fp_uptime = fopen("/proc/uptime", "r");
            fscanf(fp_uptime, "%ld", &uptime);
            fclose(fp_uptime);
            long arrival_time = uptime - (info.starttime / sysconf(_SC_CLK_TCK)); // Change type to long
            info.arrival_time = arrival_time;

            // printf("PID: %d, Name: %s, Priority: %d, Burst Time: %lld, Arrival Time: %ld\n", info.pid, info.name, info.priority, burst_time, arrival_time);

            fclose(fp);

            // Check if we need to resize the array
            if (process_count >= max_processes)
            {
                max_processes *= 2;
                processes = realloc(processes, max_processes * sizeof(struct proc_info));
                if (processes == NULL)
                {
                    perror("Failed to resize processes array");
                    return NULL;
                }
            }
            processes[process_count++] = info;
        }
    }
    closedir(dirp);

    //* Print the processes
    // for (int i = 0; i < process_count; i++)
    // {
    //     printf("PID: %d, Name: %s, Priority: %d, Burst Time: %lld, Arrival Time: %ld\n", processes[i].pid, processes[i].name, processes[i].priority, processes[i].burst_time, processes[i].arrival_time);
    // }

    // // Don't forget to free the memory when you're done
    // free(processes);
    return processes;
}