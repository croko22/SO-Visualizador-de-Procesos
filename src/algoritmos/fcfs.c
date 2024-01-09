#include <stdio.h>
#include <stdlib.h>
#include "../procesos.h"

int compare(const void *a, const void *b)
{
    struct info_proceso *proceso_a = (struct info_proceso *)a;
    struct info_proceso *proceso_b = (struct info_proceso *)b;
    return (proceso_a->tiempo_llegada - proceso_b->tiempo_llegada);
}

int mas_reciente(struct info_proceso *procesos, int n)
{
    int indice_minimo = 0;
    for (int i = 1; i < n; i++)
    {
        if (procesos[i].tiempo_llegada < procesos[indice_minimo].tiempo_llegada)
            indice_minimo = i;
    }
    return indice_minimo;
}

void fcfs(struct info_proceso *procesos, int n)
{
    int current_time = 0;

    FILE *archivo = fopen("fcfs.csv", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo!\n");
        return;
    }

    fprintf(archivo, "pid,start_time,end_time\n");
    qsort(procesos, n, sizeof(struct info_proceso), compare); // assuming compare is a function that compares two info_proceso structures based on tiempo_llegada

    for (int i = 0; i < n; i++)
    {
        int end_time = current_time + procesos[i].tiempo_ráfaga;

        fprintf(archivo, "%d,%d,%d\n", procesos[i].pid, current_time, end_time);

        current_time = end_time;
    }

    fclose(archivo);
}
