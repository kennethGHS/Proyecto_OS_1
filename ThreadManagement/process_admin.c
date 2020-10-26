//
// Created by kenneth on 25/10/20.
//
#include "process_admin.h"
#include "../BasicStructures/process_structure.h"
#include <pthread.h>
#include <unistd.h>
struct process *get_next_struct_process(int typeCalend) {
    if (typeCalend == 0) {
        return get_closest_finish(head);
    } else {
        return get_min_relation(head);
    }
}

void execute_main_thread() {
    while (1 == 1) {
        pthread_mutex_lock(&(mutex_use_list));
        if (head != NULL) {
            increase_energy_period(head,cycleNum);
            struct process *process_to_execute = get_next_struct_process(mode);
            if (process_to_execute==NULL){
                pthread_mutex_unlock(&(mutex_use_list));
                sleep(2);
                continue;
            }
            pthread_mutex_unlock(&(process_to_execute->mutex));


            cycleNum++;
        }
        cycleNum++;
        pthread_mutex_unlock(&(mutex_use_list));
        sleep(2);
    }
}

struct process *create_head_thread_safe(int cyclesToFinish, int period) {
    pthread_mutex_lock(&(mutex_use_list));
    int idAlien = create_martian(0,1,cyclesToFinish,period) ;
    int idBar =idAlien;
    struct process *newProcess = add_process_list(period, cyclesToFinish, head, idAlien, idBar);
    pthread_mutex_lock(&(newProcess->mutex));
    pthread_mutex_unlock(&(mutex_use_list));
    return newProcess;
}

struct process *add_process_list_thread_safe(int period, int cycles) {
    pthread_mutex_unlock(&(mutex_use_list));
    int idAlien = create_martian(0,1,cycles,period) ;
    int idBar =idAlien;
    struct process *newProcess = createHead(cycles, period, idAlien, idBar);
    pthread_mutex_lock(&(newProcess->mutex));
    pthread_mutex_unlock(&(mutex_use_list));
    return newProcess;
}
