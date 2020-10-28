//
// Created by kenneth on 25/10/20.
//

#ifndef PROYECTO_OS_1_PROCESS_ADMIN_H
#define PROYECTO_OS_1_PROCESS_ADMIN_H
#include <pthread.h>
#include "../interface/interface.h"
#include <unistd.h>
#include "../BasicStructures/process_structure.h"
#include <pthread.h>
#include <stdbool.h>
int already_executed(struct process * head);
struct process *get_next_struct_process(int typeCalend);
pthread_t threads[20];
void * execute_main_thread();
bool isonlyOne(int index, int * isAvailable);
pthread_mutex_t mutex_use_list;
int mode;
int stop_execution_var;
int inExecution ;
struct process *processHeadList;
int cycleNum;
void calculate_new_pos(int *newX, int *newY, int isAvailable[4], int oldX, int oldY, int i, int i1);
struct process *create_head_thread_safe(int cyclesToFinish, int period);
struct process *add_process_list_thread_safe(int period, int cycles);

#endif //PROYECTO_OS_1_PROCESS_ADMIN_H
