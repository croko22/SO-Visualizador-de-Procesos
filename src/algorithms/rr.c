#include <stdio.h>
#include <stdlib.h>
#include "../utils/proc.h"

void rr(struct proc_info *processes, int num_processes)
{
    int time_quantum = 3;
    int *remaining_times = malloc(sizeof(int) * num_processes);
    int total_time = 0;

    // Imprimir encabezado de la tabla
    printf("| Proceso | Rafaga | Tiempo de llegada | Prioridad | Tiempo ejecucion | Tiempo espera |\n");
    printf("|---------|--------|-------------------|-----------|-------------------|---------------|\n");

    // Obtener los tiempos de ráfaga de los procesos y calcular el tiempo total
    for (int i = 0; i < num_processes; i++)
    {
        printf("| %-7d | %-6d | %-17d | %-9d | %-17d | %-13d |\n",
               processes[i].pid, processes[i].burst_time, processes[i].arrival_time,
               processes[i].priority, processes[i].execution_time, processes[i].waiting_time);

        remaining_times[i] = processes[i].burst_time;
        total_time += processes[i].burst_time;
    }

    // Ejecutar los procesos en forma de Round Robin
    while (total_time > 0)
    {
        for (int i = 0; i < num_processes; i++)
        {
            if (remaining_times[i] > 0)
            {
                if (remaining_times[i] <= time_quantum)
                {
                    // Ejecutar el proceso completo
                    processes[i].execution_time += remaining_times[i];
                    total_time -= remaining_times[i];
                    remaining_times[i] = 0;
                }
                else
                {
                    // Ejecutar el proceso por el tiempo de quantum
                    processes[i].execution_time += time_quantum;
                    total_time -= time_quantum;
                    remaining_times[i] -= time_quantum;
                }
            }
        }
    }

    free(remaining_times);
}