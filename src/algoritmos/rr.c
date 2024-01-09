#include <stdio.h>
#include <stdlib.h>
#include "../procesos.h"

void rr(struct info_proceso *processes, int num_processes)
{
    int time_quantum = 200;
    int *remaining_times = malloc(sizeof(int) * num_processes);
    int total_time = 0;
    int current_time = 0;

    FILE *archivo = fopen("rr.csv", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo!\n");
        return;
    }

    fprintf(archivo, "pid,start_time,end_time\n");

    // printf("| Proceso | Rafaga | Tiempo de llegada | Prioridad | Tiempo ejecucion | Tiempo espera |\n");

    for (int i = 0; i < num_processes; i++)
    {
        remaining_times[i] = processes[i].tiempo_ráfaga;
        total_time += processes[i].tiempo_ráfaga;
    }

    while (1)
    {
        int done = 1;

        for (int i = 0; i < num_processes; i++)
        {
            if (remaining_times[i] > 0)
            {
                done = 0;

                if (remaining_times[i] > time_quantum)
                {
                    current_time += time_quantum;
                    remaining_times[i] -= time_quantum;
                }
                else
                {
                    current_time += remaining_times[i];
                    processes[i].tiempo_espera = current_time - processes[i].tiempo_ráfaga;
                    processes[i].tiempo_ejecucion = current_time - processes[i].tiempo_llegada;
                    remaining_times[i] = 0;

                    // Only write to the file when a process finishes
                    fprintf(archivo, "%d,%d,%d\n", processes[i].pid, current_time - processes[i].tiempo_ráfaga, current_time);
                }

                //? Write to the file every time
                // fprintf(archivo, "%d,%d,%d\n", processes[i].pid, current_time - remaining_times[i], current_time);
            }
        }

        if (done == 1)
            break;
    }

    for (int i = 0; i < num_processes; i++)
    {
        // printf("| %-7d | %-6lld | %-17ld | %-9d | %-15d | %-13d |\n",
        //        processes[i].pid, processes[i].tiempo_ráfaga, processes[i].tiempo_llegada,
        //        processes[i].prioridad, processes[i].tiempo_ejecucion, processes[i].tiempo_espera);

        fprintf(archivo, "%d,%d,%d\n", processes[i].pid, processes[i].tiempo_llegada, processes[i].tiempo_ejecucion);
    }

    fclose(archivo);
    free(remaining_times);
}