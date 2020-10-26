//
// Created by kenneth on 19/10/20.
//

#ifndef PROYECTO_OS_1_PROCESS_STRUCTURE_H
#define PROYECTO_OS_1_PROCESS_STRUCTURE_H
#include "interval_structure.h"
#include <pthread.h>
struct process{
    struct process * next;
    int period;
    int cycles;
    int cyclesToFinish;
    struct interval * intervalList;
    int id;
    int idAlien;
    int idAlienBar;
    pthread_mutex_t mutex;
};
struct process *createHead(int cyclesToFinish, int period,int alienId, int alienBarId);
struct process * get_closest_finish(struct process * headList);
void delete_list(struct process * headList);
struct process * add_process_list(int period, int cycles, struct process *headList, int alienId, int alienBarId);
struct process * get_min_relation(struct process *headList);
int increase_energy_period(struct process * head, int cycle);
#endif //PROYECTO_OS_1_PROCESS_STRUCTURE_H
