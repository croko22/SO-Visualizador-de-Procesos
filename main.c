#include <stdio.h>
#include <stdlib.h>
#include "src/algoritmos/fcfs.c"
#include "src/algoritmos/sjf.c"

//? SCRIPT: gcc main.c  src/utils/proc.h src/utils/proc.c  && ./a.out
enum Opciones
{
    FCFS = 1,
    SJF,
    Prioridad,
    RoundRobin,
    Salir
};

int main()
{
    int opcion;
    printf("Elige una opción:\n");
    printf("1. FCFS\n");
    printf("2. SJF\n");
    printf("3. Prioridad\n");
    printf("4. Round Robin\n");
    printf("5. Salir\n");
    scanf("%d", &opcion);
    int num_procesos;

    struct info_proceso *procesos = obtener_info_proceso(&num_procesos);
    for (int i = 0; i < num_procesos; i++)
    {
        printf("PID: %d, Nombre: %s, Prioridad: %d, Tiempo de Ráfaga: %lld, Tiempo de Llegada: %ld\n",
               procesos[i].pid, procesos[i].nombre, procesos[i].prioridad,
               procesos[i].tiempo_ráfaga, procesos[i].tiempo_llegada);
    }

    if (opcion == FCFS)
    {
        fcfs(procesos, num_procesos);
    }
    else if (opcion == SJF)
    {
        sjf(procesos, num_procesos);
    }
    else if (opcion == Prioridad)
    {
        // Implementar lógica para la opción de Prioridad
    }
    else if (opcion == RoundRobin)
    {
        // Implementar lógica para la opción de Round Robin
    }
    else if (opcion == Salir)
    {
        return 0;
    }
    else
    {
        printf("Opción no válida\n");
    }

    printf("Número de procesos: %d\n", num_procesos);

    return 0;
}
