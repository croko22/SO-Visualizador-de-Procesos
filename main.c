#include <stdio.h>
#include "src/algorithms/fcfs.c"
#include "src/algorithms/sjf.c"

//? SCRIPT: gcc main.c  src/utils/proc.h src/utils/proc.c  && ./a.out
int main()
{
    int option;
    printf("Choose an option:\n");
    printf("1. FCFS\n");
    printf("2. SJF\n");
    printf("3. Priority\n");
    printf("4. Round Robin\n");
    printf("5. Exit\n");
    scanf("%d", &option);
    int num_processes;

    struct proc_info *processes = get_proc_info(&num_processes);
    printf("%-10s %-20s %-10s %-15s %-15s %-20s\n", "PID", "Name", "Priority", "Burst Time", "Arrival Time", "Normalized Burst Time");

    for (int i = 0; i < num_processes; i++)
    {
        printf("%-10d %-20s %-10d %-15lld %-15ld %-20d\n", processes[i].pid, processes[i].name, processes[i].priority, processes[i].burst_time, processes[i].arrival_time, processes[i].normalized_burst_time);
    }

    switch (option)
    {
    case 1:
        fcfs(processes, num_processes);
        break;
    case 2:
        sjf(processes, num_processes);
        break;
    case 3:

        break;
    case 4:

        break;
    case 5:
        return 0;
    default:
        printf("Invalid option\n");
        break;
    }

    // fcfs(processes, num_processes);
    printf("Number of processes: %d\n", num_processes);

    return 0;
}