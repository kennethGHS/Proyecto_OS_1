//
// Created by kenneth on 25/10/20.
//
#include "process_admin.h"
#include "../BasicStructures/process_structure.h"
#include <pthread.h>
#include <unistd.h>

struct process *get_next_struct_process(int typeCalend) {
    if (typeCalend == 0) {
        return get_closest_finish(processHeadList);
    } else {
        return get_min_relation(processHeadList);
    }
}

void * execute_main_thread() {
    printf("Ejecutando lol");
    printf("ejecutando lol %d \n",processHeadList->id);
    cycleNum = 0;
    while (1 == 1) {
        pthread_mutex_lock(&(mutex_use_list));
        if (processHeadList != NULL) {
            increase_energy_period(processHeadList, cycleNum);
            struct process *process_to_execute = get_next_struct_process(mode);
            if (process_to_execute==NULL){
                printf("Ejecutando xd \n");
                if(already_all_executed(processHeadList) == 1){
//                    printf("Todos ejecutados ciclo %d\n",cycleNum);
                    cycleNum++;
                }
                pthread_mutex_unlock(&(mutex_use_list));
                sleep(2);
                continue;
            }
//            printf("Ciclos a ejecutar %d",process_to_execute->cyclesToFinish);
//            printf("Liberado xd \n");
            sem_post(&(process_to_execute->mutex));
            cycleNum++;
        }
        pthread_mutex_unlock(&(mutex_use_list));
        sleep(2);
    }
}
void * execute_process(void * process_execute){
    //falta meter el intervalo al proceso
    struct process * process = (struct process *) process_execute;
    while (inExecution==1) {
        sem_wait(&(process->mutex));
        process->cyclesToFinish--;
        int posXMatrix = MARTIANS[process->idAlien].matrix_position_x;
        int posYMatrix = MARTIANS[process->idAlien].matrix_position_y;
        printf("Pos x= %d \n",posXMatrix);
        printf("Pos y= %d \n",posYMatrix);

        int isAvailable[] = {0,0,0,0};
        int valor = matrix_maze[posYMatrix][posXMatrix+1];
        int row, columns;
        for (row=0; row<16; row++)
        {
            for(columns=0; columns<16; columns++)
            {
                printf("%d     ", matrix_maze[row][columns]);
            }
            printf("\n");
        }
        if (is_valid_pos(posXMatrix+1,posYMatrix)){
            isAvailable[0] = 1;
        }
        if (is_valid_pos(posXMatrix-1,posYMatrix)){
            isAvailable[1] = 1;
        }
        if (is_valid_pos(posXMatrix,posYMatrix+1)){
            isAvailable[2]=1;
        }
        if (is_valid_pos(posXMatrix,posYMatrix-1)){
            isAvailable[3] = 1;
        }
        //caso sin energia ninguno
        if (isAvailable[0] ==0&& isAvailable[1] ==0&& isAvailable[2] ==0&&isAvailable[3]==0){
            float percent = (float)(process->cycles - process->cyclesToFinish)/process->cycles;
            printf("%f \n");
            reduce_bar(process->idAlienBar,percent);
            process_new_cycle(process->intervalList,cycleNum,process);
            continue;
        }
        int index_available = rand()%4;
        while (true){
            if (isAvailable[index_available]!=0){
                break;
            } else{
                index_available = rand()%4;
            }
        }
        matrix_maze[posYMatrix][posXMatrix] = 0;

        if (index_available==0){
            move_martian(process->idAlien,posXMatrix+1,posYMatrix);
            matrix_maze[posYMatrix][posXMatrix+1] = process->id;
        }
        if (index_available==1){
            move_martian(process->idAlien,posXMatrix-1,posYMatrix);
            matrix_maze[posYMatrix][posXMatrix-1] = process->id;
        }
        if (index_available==2){
            move_martian(process->idAlien,posXMatrix,posYMatrix+1);
            matrix_maze[posYMatrix+1][posXMatrix] = process->id;
        }
        if (index_available==3){
            move_martian(process->idAlien,posXMatrix,posYMatrix-1);
            matrix_maze[posYMatrix-1][posXMatrix] = process->id;
        }
        float percent = (float)(process->cycles - process->cyclesToFinish)/process->cycles;
        printf("%f \n",percent);
        reduce_bar(process->idAlienBar,percent);
        process_new_cycle(process->intervalList,cycleNum,process);
    }
}
struct process *create_head_thread_safe(int cyclesToFinish, int period) {
    pthread_mutex_lock(&(mutex_use_list));
    int idAlien = create_martian(0,1,cyclesToFinish,period) ;
    int idBar =idAlien;
    struct process *newProcess = createHead(cyclesToFinish, period, idAlien, idAlien);
    processHeadList = newProcess;
    pthread_create(&(threads[newProcess->id]),
                   NULL,
                   &execute_process, newProcess);
    pthread_mutex_unlock(&(mutex_use_list));
    return newProcess;
}

struct process *add_process_list_thread_safe(int period, int cycles) {
    pthread_mutex_lock(&(mutex_use_list));
    if (processHeadList==NULL){
        pthread_mutex_unlock(&(mutex_use_list));
        return create_head_thread_safe(cycles,period);
    }
    int idAlien = create_martian(0,1,cycles,period) ;
    int idBar =idAlien;
    struct process *newProcess = add_process_list(period,cycles,processHeadList,idAlien,idBar);
    pthread_t * threadSecond = malloc(sizeof(pthread_t));
    pthread_create(threadSecond,
                   NULL,
                   &execute_process, newProcess);
    pthread_mutex_unlock(&(mutex_use_list));

    return newProcess;
}
