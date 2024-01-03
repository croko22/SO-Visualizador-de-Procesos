#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "src/utils/proc.h"
// gcc main.c src/utils/proc.h && ./a.out
int main()
{
    int process_count;
    struct proc_info *processes = get_proc_info(&process_count);

    if (processes != NULL)
    {
        // Print the processes
        for (int i = 0; i < process_count; i++)
        {
            printf("PID: %d, Name: %s, Priority: %d, Burst Time: %lld, Arrival Time: %ld\n",
                   processes[i].pid, processes[i].name, processes[i].priority,
                   processes[i].burst_time, processes[i].arrival_time);
        }

        // Don't forget to free the memory when you're done
        free(processes);
    }

    return 0;
}