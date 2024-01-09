#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/algoritmos/fcfs.c"
#include "src/algoritmos/sjf.c"
#include "src/algoritmos/rr.c"

enum Opciones
{
    FCFS = 1,
    SJF = 2,
    RoundRobin = 3,
    Salir
};

int main()
{
    int num_procesos;

    // Original struct
    struct info_proceso *procesos = obtener_info_proceso(&num_procesos);

    for (int i = 0; i < num_procesos; i++)
    {
        printf("%d %s %d %d %d %d\n", procesos[i].pid, procesos[i].nombre, procesos[i].prioridad, procesos[i].tiempo_ráfaga, procesos[i].tiempo_llegada, procesos[i].tiempo_espera);
    }

    // Create three copies
    struct info_proceso *procesos_copy1 = malloc(num_procesos * sizeof(struct info_proceso));
    struct info_proceso *procesos_copy2 = malloc(num_procesos * sizeof(struct info_proceso));
    struct info_proceso *procesos_copy3 = malloc(num_procesos * sizeof(struct info_proceso));

    // Copy the data
    memcpy(procesos_copy1, procesos, num_procesos * sizeof(struct info_proceso));
    memcpy(procesos_copy2, procesos, num_procesos * sizeof(struct info_proceso));
    memcpy(procesos_copy3, procesos, num_procesos * sizeof(struct info_proceso));

    fcfs(procesos_copy1, num_procesos);
    sjf(procesos_copy2, num_procesos);
    rr(procesos_copy3, num_procesos);

    free(procesos);
    free(procesos_copy1);
    free(procesos_copy2);
    free(procesos_copy3);

    return 0;
}
