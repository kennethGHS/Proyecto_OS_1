//
// Created by kenneth on 25/10/20.
//

#ifndef PROYECTO_OS_1_PROCESS_ADMIN_H
#define PROYECTO_OS_1_PROCESS_ADMIN_H
#include <pthread.h>
#include "../interface/interface.h"

struct process *get_next_struct_process(int typeCalend);
pthread_t threads[20];
void * execute_main_thread();

pthread_mutex_t mutex_use_list;
int mode;
int stop_execution_var;
int inExecution ;
struct process *processHeadList;
int cycleNum;
struct process *create_head_thread_safe(int cyclesToFinish, int period);
struct process *add_process_list_thread_safe(int period, int cycles);

#endif //PROYECTO_OS_1_PROCESS_ADMIN_H
