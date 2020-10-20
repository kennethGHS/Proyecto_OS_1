//
// Created by kenneth on 19/10/20.
//

#ifndef PROYECTO_OS_1_PROCESS_STRUCTURE_H
#define PROYECTO_OS_1_PROCESS_STRUCTURE_H
#include "interval_structure.h"
struct process{
    struct process * next;
    int period;
    int cycles;
    int cyclesToFinish;
    struct interval * intervalList;
};
struct process * get_closest_finish(struct process * headList);
void delete_list(struct process * headList);
int add_process_list(int period, int cycles, struct  process * headList);
#endif //PROYECTO_OS_1_PROCESS_STRUCTURE_H
