#include <stdio.h>
#include <stdbool.h>
#include "src/procesos.h"

void rr(struct info_proceso *processes, int num_processes, long quantum)
{
    int i, sum = 0, count = 0, y, quant, wt = 0, tat = 0, at[10], bt[10], temp[10];
    float avg_wt, avg_tat;

    // Check if all processes have a burst time of 0
    bool all_zero_burst_times = true;
    for (i = 0; i < num_processes; i++)
    {
        if (processes[i].tiempo_ráfaga > 0)
        {
            all_zero_burst_times = false;
            break;
        }
    }

    if (all_zero_burst_times)
    {
        // All processes have a burst time of 0, so there is no work to do
        printf("Todos los procesos tienen un tiempo de ejecución de 0.");
        return;
    }

    // Initialize the temp array
    for (i = 0; i < num_processes; i++)
    {
        temp[i] = processes[i].tiempo_ráfaga;
    }

    // Print the header
    printf("\n No de proceso \t\t Tiempo de servicio \t\t TAT \t\t Tiempo de espera ");

    for (sum = 0, i = 0; y != 0;)
    {
        if (temp[i] <= quant && temp[i] > 0)
        {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if (temp[i] > 0)
        {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }

        if (temp[i] == 0 && count == 1)
        {
            y--;
            printf("\nProceso No [%d] \t\t %d\t\t\t\t %d\t\t\t %d", i + 1, processes[i].tiempo_ráfaga, sum - processes[i].tiempo_llegada, sum - processes[i].tiempo_llegada - processes[i].tiempo_ráfaga);
            wt = wt + sum - processes[i].tiempo_llegada - processes[i].tiempo_ráfaga;
            tat = tat + sum - processes[i].tiempo_llegada;
            count = 0;
        }

        if (i == num_processes - 1)
        {
            i = 0;
        }
        else if (processes[i + 1].tiempo_llegada <= sum)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    // Calculate the average waiting time
    avg_wt = wt * 1.0 / num_processes;

    // Print the average waiting time
    printf("\n Tiempo de espera promedio: \t%f", avg_wt);
}

int main()
{
    int num_processes;
    long quantum;

    // Taking input for the number of processes and quantum
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the quantum: ");
    scanf("%ld", &quantum);

    struct info_proceso *processes = get_info_proceso(&num_processes);
    for (int i = 0; i < num_processes; i++)
    {
        printf("PID: %d, Name: %s, Priority: %d, Burst Time: %lld, Arrival Time: %ld\n", processes[i].pid, processes[i].name, processes[i].priority, processes[i].tiempo_ráfaga, processes[i].tiempo_llegada);
    }

    rr(processes, num_processes, quantum);

    // Don't forget to free the allocated memory for processes
    free(processes);

    return 0;
}
