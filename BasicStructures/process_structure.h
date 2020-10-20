//
// Created by kenneth on 19/10/20.
//

#ifndef PROYECTO_OS_1_PROCESS_STRUCTURE_H
#define PROYECTO_OS_1_PROCESS_STRUCTURE_H
struct process{
    struct process * next;
    int period;
    int cycles;
    int cyclesToFinish;
};
struct process * get_closest_finish(struct process * headList);
struct process * delete_list(struct process * headList);
int add_process_list(int period, int cycles, struct  process);
#endif //PROYECTO_OS_1_PROCESS_STRUCTURE_H
