//
// Created by kenneth on 19/10/20.
//

#ifndef PROYECTO_OS_1_INTERVAL_STRUCTURE_H
#define PROYECTO_OS_1_INTERVAL_STRUCTURE_H
#include "process_structure.h"

struct interval {
    int unitBegin;
    int unitEnd;
    struct interval *nextInterval;
};
int process_new_cycle(struct interval * head, int cycle,struct process * process);
int add_new_interval(struct interval * head, int begin);
void delete_interval_list(struct interval * head);
#endif //PROYECTO_OS_1_INTERVAL_STRUCTURE_H
