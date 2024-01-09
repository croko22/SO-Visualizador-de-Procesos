#include "procesos.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

struct info_proceso *obtener_info_proceso(int *cuenta)
{
    DIR *directorio;
    struct dirent *entrada_directorio;

    int max_procesos = 4096;
    struct info_proceso *procesos = malloc(max_procesos * sizeof(struct info_proceso));

    if (procesos == NULL)
    {
        perror("Error al asignar memoria para el array de procesos");
        return NULL;
    }

    directorio = opendir("/proc");
    if (directorio == NULL)
    {
        perror("Error al abrir el directorio \"/proc\"");
        free(procesos);
        return NULL;
    }

    int cuenta_procesos = 0;
    while ((entrada_directorio = readdir(directorio)) != NULL)
    {
        if (atoi(entrada_directorio->d_name) > 0)
        {
            char ruta_estadisticas[256];
            sprintf(ruta_estadisticas, "/proc/%s/stat", entrada_directorio->d_name);

            FILE *archivo = fopen(ruta_estadisticas, "r");
            if (archivo == NULL)
            {
                perror("Error al abrir el archivo de estadísticas");
                continue;
            }

            struct info_proceso info;

            // Obtener información del proceso desde /proc/<pid>/stat
            int tiempo_usuario, tiempo_sistema, tiempo_inicio;
            fscanf(archivo, "%d %s %*c %d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %*lu %*ld %*ld %*ld %d",
                   &info.pid, info.nombre, &info.prioridad, &tiempo_usuario, &tiempo_sistema, &tiempo_inicio);

            fclose(archivo);

            info.tiempo_ráfaga = (tiempo_usuario + tiempo_sistema) * 1000 / sysconf(_SC_CLK_TCK);

            // Calcular el tiempo de llegada
            long tiempo_actividad;
            FILE *archivo_tiempo = fopen("/proc/uptime", "r");
            fscanf(archivo_tiempo, "%ld", &tiempo_actividad);
            fclose(archivo_tiempo);
            info.tiempo_llegada = tiempo_actividad - (tiempo_inicio / sysconf(_SC_CLK_TCK)); // Cambiar tipo a long

            // Verificar si necesitamos redimensionar el array
            if (cuenta_procesos >= max_procesos)
            {
                max_procesos *= 2;
                struct info_proceso *temporal = realloc(procesos, max_procesos * sizeof(struct info_proceso));
                if (temporal == NULL)
                {
                    perror("Error al redimensionar el array de procesos");
                    free(procesos);
                    return NULL;
                }
                procesos = temporal;
            }

            procesos[cuenta_procesos++] = info;
        }
    }
    closedir(directorio);

    // Find the minimum and maximum values of tiempo_ráfaga
    int min = procesos[0].tiempo_ráfaga;
    int max = procesos[0].tiempo_ráfaga;

    for (int i = 1; i < cuenta_procesos; i++)
    {
        if (procesos[i].tiempo_ráfaga < min)
            min = procesos[i].tiempo_ráfaga;
        if (procesos[i].tiempo_ráfaga > max)
            max = procesos[i].tiempo_ráfaga;
    }

    // Normalize the tiempo_ráfaga values
    for (int i = 0; i < cuenta_procesos; i++)
    {
        procesos[i].tiempo_ráfaga = ((procesos[i].tiempo_ráfaga - min) / (float)(max - min)) * 1000;
    }

    *cuenta = cuenta_procesos;
    return procesos;
}
