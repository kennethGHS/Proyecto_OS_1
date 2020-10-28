//
// Created by kenneth on 19/10/20.
//
#include "process_structure.h"
#include <stdlib.h>
#include <stdio.h>
#include "interval_structure.h"
/**
 * Arreglar ya que puede generar problemas si todos son 0
 * @param headList
 * @return
 */
struct process *get_closest_finish(struct process *headList) {
    struct process *leastCycles = NULL;
    while ( (headList!=NULL && headList->cyclesToFinish==0 )|| (headList!=NULL && headList->available==0)){
        headList = headList->next;
    }
    if (headList==NULL){
        return NULL;
    }
    while (headList != NULL) {
        if (leastCycles == NULL) {
            if (headList->cyclesToFinish != 0) {
                leastCycles = headList;
            }

        } else {
            if (leastCycles->cyclesToFinish > headList->cyclesToFinish && headList->cyclesToFinish!=0 && headList->available==1) {
                leastCycles = headList;
            }
        }
        headList = headList->next;
    }
    return leastCycles;
}
struct process * get_min_relation(struct process *headList){
    struct process *leastRelation = NULL;
    while ((headList!=NULL && headList->cyclesToFinish==0 )|| (headList!=NULL && (headList->available==0))){
        headList = headList->next;
    }
    if (headList==NULL){
        return NULL;
    }
    while (headList != NULL) {
        if (leastRelation == NULL) {
            if (headList->cyclesToFinish != 0 || (headList->available==0)) {
                leastRelation = headList;
            }
        } else {
            if (((float )1.0/leastRelation->period < (float )1.0/headList->period)&&headList->cyclesToFinish!=0 && (headList->available==1) ) {
                leastRelation = headList;
            }
        }
        headList = headList->next;
    }
    return leastRelation;
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

struct process * add_process_list(int period, int cycles, struct process *headList, int alienId, int alienBarId) {
    int idPrev = headList->id;
    if (headList == NULL) {
        return NULL;
    }
    while (headList->next != NULL) {
        headList = headList->next;
        idPrev = headList->id;
    }
    headList->next = malloc(sizeof(struct process));
    headList->next->cycles = cycles;
    headList->next->period = period;
    headList->next->intervalList = NULL;
    headList->next->cyclesToFinish = 0;
    headList->next->id = idPrev + 1;
    headList->next->idAlien = alienId;
    headList->next->idAlienBar = alienBarId;
    headList->next->next = NULL;
    headList->next->available=1;
    sem_init(&headList->next->mutex, 1, 0);
    return headList->next;
}

int process_cycle_process(int cycle, struct process *process) {
    if (process == NULL) {
        printf("Error en funcion process_cycle_process, proceso nulo");
        return -1;
    } else {
        if (process->intervalList = NULL) {
            process->intervalList = malloc(sizeof(struct interval));
            process->intervalList->unitBegin = cycle;
            process->intervalList->unitEnd = cycle + 1;
            return 0;
        } else {
            process_new_cycle(process->intervalList, cycle,process);
            return 0;
        }
    }
}

struct process *createHead(int cyclesToFinish, int period,int alienId, int alienBarId) {
    struct process *newProcess = malloc(sizeof(struct process));
    newProcess->id = 3;
    newProcess->cyclesToFinish = 0;
    newProcess->period = period;
    newProcess->cycles = cyclesToFinish;
    newProcess->idAlien = alienId;
    newProcess->idAlienBar = alienBarId;
    newProcess->next = NULL;
    newProcess->intervalList = NULL;
    newProcess->available=1;
    sem_init(&newProcess->mutex, 1, 0);
    return newProcess;
}
int increase_energy_period(struct process * head, int cycle){
    while (head!=NULL){
        if (cycle%head->period==0){
            if (head->cyclesToFinish !=0 && (head->available==1)){
                show_warning(0);
                return -1;
            } else{
                if (head->available==1){
                    head->cyclesToFinish = head->cycles;
                }
            }
            head->cyclesToFinish = head->cycles;
            printf("Recarga en ciclo %d, el proceso %d con periodo %d \n",cycle,head->id,head->period);
            reload_bar(head->idAlienBar);
            //INCREMENTAR BARRA
        }
        head = head->next;
    }
    return 0;
}
int already_all_executed(struct process * head){
    while (head!=NULL){
        if (head->cyclesToFinish!=0){
            return -1;
        }
        head = head->next;
    }
    return 1;
}