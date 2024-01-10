#include <stdio.h>
#include "src/algorithms/fcfs.c"
#include "src/algorithms/sjf.c"
#include "src/algorithms/rr.c"

int main()
{
    int num_processes;
    struct proc_info *processes = get_proc_info(&num_processes);

    printf("%-10s %-20s %-10s %-15s %-15s %-20s\n", "PID", "Name", "Priority", "Burst Time", "Arrival Time", "Normalized Burst Time");
    for (int i = 0; i < num_processes; i++)
    {
        printf("%-10d %-20s %-10d %-15lld %-15ld %-20d\n", processes[i].pid, processes[i].name, processes[i].priority, processes[i].burst_time, processes[i].arrival_time, processes[i].normalized_burst_time);
    }

    // Make copies of the original processes array for each algorithm
    struct proc_info *processes_fcfs = malloc(sizeof(struct proc_info) * num_processes);
    struct proc_info *processes_sjf = malloc(sizeof(struct proc_info) * num_processes);
    struct proc_info *processes_rr = malloc(sizeof(struct proc_info) * num_processes);
    memcpy(processes_fcfs, processes, sizeof(struct proc_info) * num_processes);
    memcpy(processes_sjf, processes, sizeof(struct proc_info) * num_processes);
    memcpy(processes_rr, processes, sizeof(struct proc_info) * 10);

    // Run each algorithm
    fcfs(processes_fcfs, num_processes);
    sjf(processes_sjf, num_processes);
    rr(processes_rr, 10);

    // Free the memory allocated for the copies
    free(processes_fcfs);
    free(processes_sjf);
    free(processes_rr);

    return 0;
}