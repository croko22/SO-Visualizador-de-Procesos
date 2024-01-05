#ifndef PROC_H
#define PROC_H

struct proc_info
{
    int pid;
    char name[256];
    int priority;
    long arrival_time;
    long long burst_time;
    float normalized_burst_time;
};

struct proc_info *get_proc_info(int *count);

#endif // PROC_H