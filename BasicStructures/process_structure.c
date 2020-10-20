//
// Created by kenneth on 19/10/20.
//
#include "process_structure.h"
#include <stdlib.h>
#include <stdio.h>
#include "interval_structure.h"

struct process *get_closest_finish(struct process *headList) {
    struct process *leastCycles = NULL;
    while (headList != NULL) {
        if (leastCycles == NULL) {
            if (headList->cyclesToFinish != 0) {
                leastCycles = headList;
            }
        } else {
            if (leastCycles->cyclesToFinish > headList->cyclesToFinish) {
                leastCycles = headList;
            }
        }
        headList = headList->next;
    }
    return leastCycles;
}

void delete_list(struct process *headList) {
    struct process *next = NULL;
    while (headList != NULL) {
        next = headList->next;
        delete_interval_list(headList->intervalList);
        free(headList);
        headList = next;
    }
}

int add_process_list(int period, int cycles, struct process *headList) {
    if (headList==NULL){
        return  -1;
    }
    while (headList != NULL) {
        headList = headList->next;
    }
    headList->next = malloc(sizeof(struct process));
    headList->next->cycles = cycles;
    headList->next->period = period;
    headList->next->cyclesToFinish = cycles;
    return 1;
}
int process_cycle_process(int cycle,struct process * process){
    if (process==NULL){
        printf("Error en funcion process_cycle_process, proceso nulo");
        return -1;
    } else{
        if (process->intervalList = NULL){
            process->intervalList = malloc(sizeof(struct interval));
            process->intervalList->unitBegin = cycle;
            process->intervalList->unitEnd = cycle+1;
            return 0;
        } else{
            process_new_cycle(process->intervalList,cycle);
            return 0;
        }
    }
}