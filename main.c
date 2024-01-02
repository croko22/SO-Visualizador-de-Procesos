#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "src/utils/proc.h"

int main()
{
    int max_processes = 10;
    // int max_processes = 1024;
    struct proc_info *processes = get_proc_info(max_processes);
    if (processes == NULL)
    {
        fprintf(stderr, "Failed to get process info\n");
        return 1;
    }

    printf("%-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "PID", "Name", "Priority", "utime", "stime", "starttime", "burst_time", "arrival_time");

    for (int i = 0; i < max_processes; i++)
    {
        printf("%-10d %-20s %-10d %-10ld %-10ld %-10ld %-10lld %-10ld\n",
               processes[i].pid,
               processes[i].name,
               processes[i].priority,
               processes[i].utime,
               processes[i].stime,
               processes[i].starttime,
               processes[i].burst_time,
               processes[i].arrival_time);
    }

    free(processes); // Don't forget to free the memory when you're done

    return 0;
}