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
/**
 * Checks if all thre process in the list have already been executed
 * @param head The head of the list
 * @return 1 if they havent and 0 if they do
 */
int already_executed(struct process * head);
/**
 * Gets the next process to get executed
 * @param typeCalend 0 for EDF 1 for RMS
 * @return A process or NULL if they arent available
 */
struct process *get_next_struct_process(int typeCalend);
pthread_t threads[20];
/**
 * Main thread that manages all the other  processthreads
 * @return
 */
void * execute_main_thread();
/**
 * Used to check if a position to jump is the only one available
 * @param index the position to jump
 * @param isAvailable array of avilable positions
 * @return
 */
bool isonlyOne(int index, int * isAvailable);
pthread_mutex_t mutex_use_list;
/**
 * Mode for the calendarization
 */
int mode;
/**
 * change it to -1 to stop all executions
 */
int stop_execution_var;
/**
 * change it to 0 to stop the execution of all process
 */
int inExecution ;
struct process *processHeadList;
int cycleNum;
/**
 * Calculates the new position for the alien to move
 * @param newX new X to return
 * @param newY new Y to return
 * @param isAvailable The array of available positions
 * @param oldX the old value of X
 * @param oldY the old value of Y
 * @param i actual value of X
 * @param i1 actual value of Y
 */
void calculate_new_pos(int *newX, int *newY, int isAvailable[4], int oldX, int oldY, int i, int i1);
/**
 * Creates the head of the process list
 * @param cyclesToFinish
 * @param period
 * @return
 */
struct process *create_head_thread_safe(int cyclesToFinish, int period);
/**
 * add to the process list
 * @param period
 * @param cycles
 * @return
 */
struct process *add_process_list_thread_safe(int period, int cycles);

#endif //PROYECTO_OS_1_PROCESS_ADMIN_H
