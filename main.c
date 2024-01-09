#include <stdio.h>
#include <stdlib.h>
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
    struct info_proceso *procesos = obtener_info_proceso(&num_procesos);
    fcfs(procesos, num_procesos);

    procesos = obtener_info_proceso(&num_procesos);
    sjf(procesos, num_procesos);

    procesos = obtener_info_proceso(&num_procesos);
    rr(procesos, num_procesos);
    return 0;
}
