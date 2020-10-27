//
// Created by kenneth on 19/10/20.
//
#include "interval_structure.h"
#include <stdio.h>
#include <stdlib.h>
int process_new_cycle(struct interval * head, int cycle,struct process * process){
    if (process->intervalList == NULL){
     process->intervalList = malloc(sizeof(struct interval));
     process->intervalList->nextInterval = NULL;
     process->intervalList->unitBegin = cycle;
     process->intervalList->unitEnd = cycle+1;
        return 0;
    }
    while (head->nextInterval!=NULL){
        head = head->nextInterval;
    }
    if (head->unitEnd == cycle){
        head->unitEnd+=1;
        return 0;
    } else{
        add_new_interval(head,cycle);
        return 0;
    }

}
int add_new_interval(struct interval * head, int begin){
    if (head == NULL){
        printf("Error, no hay processHeadList");
        return -1;
    }
    while (head->nextInterval!=NULL){
        head = head->nextInterval;
    }
    head->nextInterval = malloc(sizeof(struct interval));
    head->nextInterval->unitEnd = begin+1;
    head->nextInterval->unitBegin = begin;
    head->nextInterval->nextInterval = NULL;
    return 0;
}
void delete_interval_list(struct interval * head){
    if (head==NULL){
//        printf("Error, no hay processHeadList");
        return ;
    } else{
        struct interval * next;
        while (head!=NULL){
            next = head->nextInterval;
            free(head);
            head = next;
        }
    }
}

