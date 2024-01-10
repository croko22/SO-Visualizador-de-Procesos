#include <stdio.h>
#include "src/algorithms/fcfs.c"
#include "src/algorithms/sjf.c"
#include "src/algorithms/rr.c"

int main()
{
    int num_processes;
    struct proc_info *processes = get_proc_info(&num_processes);

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