//
// Created by kenneth on 19/10/20.
//

#ifndef PROYECTO_OS_1_PROCESS_STRUCTURE_H
#define PROYECTO_OS_1_PROCESS_STRUCTURE_H
#include "interval_structure.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "../interface/interface.h"
#include <semaphore.h>
/**
 * Struct that holds the relevant data of all the processes
 */
struct process{
    struct process * next; //next process
    int period; // period of recharging
    int cycles; // the cycles that it executes
    int cyclesToFinish; // reemaining cycles
    struct interval * intervalList;// list of intervals
    int id;//id of the process
    int idAlien;//id of the interface alien
    int idAlienBar; // id of the healthbar in the interface
    int available; // if it hasnt reached the ending
    sem_t  mutex; // semaphore that synchronizes the process
};
/**
 * checks if all processes have been executed
 * @param head
 * @return
 */
int already_all_executed(struct process * head);
/**
 * Creates new head for the list
 * @param cyclesToFinish energy
 * @param period period recharging
 * @param alienId interface alien
 * @param alienBarId interface bar
 * @return
 */
struct process *createHead(int cyclesToFinish, int period,int alienId, int alienBarId);
/**
 * Gets the process in a list that is the closest to finish
 * @param headList
 * @return
 */
struct process * get_closest_finish(struct process * headList);
/**
 * deletes the whole list
 * @param headList
 */
void delete_list(struct process * headList);
/**
 * Adds new process to the list
 * @param cyclesenergy
 * @param period period recharging
 * @param alienId interface alien
 * @param alienBarId interface bar
 * @return
 */
struct process * add_process_list(int period, int cycles, struct process *headList, int alienId, int alienBarId);
/**
 * Gets the process that has the smallest period
 * @param headList
 * @return
 */
struct process * get_min_relation(struct process *headList);
/**
 * increases the energy of all the elements of a list if cycle%period = 0
 * If the process has still energy and is trying to recharge it returns an error
 * @param head
 * @param cycle
 * @return
 */
int increase_energy_period(struct process * head, int cycle);
#endif //PROYECTO_OS_1_PROCESS_STRUCTURE_H
