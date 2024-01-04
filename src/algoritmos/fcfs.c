#include <stdio.h>
#include <stdlib.h>
#include "../procesos.h"

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
    FILE *archivo = fopen("fcfs_datos.csv", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo!\n");
        return;
    }

    fprintf(archivo, "pid,tiempo_ráfaga\n");

    while (n > 0)
    {
        int temprano = mas_reciente(procesos, n);

        printf("Ejecutando proceso %d con tiempo de ráfaga %lld\n", procesos[temprano].pid, procesos[temprano].tiempo_ráfaga);

        fprintf(archivo, "%d,%lld\n", procesos[temprano].pid, procesos[temprano].tiempo_ráfaga);

        for (int i = temprano; i < n - 1; i++)
        {
            procesos[i] = procesos[i + 1];
        }
        n--;
    }

    fclose(archivo);
}
