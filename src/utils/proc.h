#ifndef PROC_H
#define PROC_H

struct proc_info
{
    int pid;                   // Identificador del proceso
    char name[256];            // Nombre del proceso
    int priority;              // Prioridad del proceso
    long arrival_time;         // Tiempo de llegada del proceso
    long long burst_time;      // Tiempo de ráfaga del proceso
    int normalized_burst_time; // Tiempo de ráfaga normalizado del proceso
    int execution_time;        // Tiempo de ejecución del proceso
    int waiting_time;          // Tiempo de espera del proceso
    int turnaround_time;       // Tiempo de retorno del proceso
};

struct proc_info *get_proc_info(int *count);

#endif // PROC_H
