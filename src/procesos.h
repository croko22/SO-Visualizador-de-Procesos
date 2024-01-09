#ifndef PROCESOS_H
#define PROCESOS_H

struct info_proceso
{
    int pid;
    char nombre[256];
    int prioridad;
    long tiempo_llegada;
    long long tiempo_ráfaga;
    int tiempo_ejecucion;
    int tiempo_espera;
};

struct info_proceso *obtener_info_proceso(int *cuenta);

#endif