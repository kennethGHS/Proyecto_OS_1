//
// Created by kenneth on 19/10/20.
//

#ifndef PROYECTO_OS_1_INTERVAL_STRUCTURE_H
#define PROYECTO_OS_1_INTERVAL_STRUCTURE_H
#include "process_structure.h"
/**
 * Holds the interval of cycles on which the process executed
 */
struct interval {
    int unitBegin;
    int unitEnd;
    struct interval *nextInterval;
};
/**
 * processes the new cycle
 * @param head head of the interval list
 * @param cycle the cycle to be processed
 * @param process the process that is executing the cycle
 * @return
 */
int process_new_cycle(struct interval * head, int cycle,struct process * process);
/**
 * Adds new interval to the interval list
 * @param head
 * @param begin the beginning of  the interval
 * @return
 */
int add_new_interval(struct interval * head, int begin);
void delete_interval_list(struct interval * head);
#endif //PROYECTO_OS_1_INTERVAL_STRUCTURE_H
