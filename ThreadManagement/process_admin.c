//
// Created by kenneth on 25/10/20.
//
#include "process_admin.h"
struct process *get_next_struct_process(int typeCalend) {
    if (typeCalend == 0) {
        return get_closest_finish(processHeadList);
    } else {
        return get_min_relation(processHeadList);
    }
}
int already_executed(struct process * head){
    while (head!=NULL){
        if (head->available==1){
            printf("Alguno ejecutado");
            return  1;
        }
        head = head->next;
    }
    return 0;
}
void *execute_main_thread() {
//    printf("Ejecutando lol");
//    printf("ejecutando lol %d \n",processHeadList->id);
    cycleNum = 0;
    while (1 == 1) {
        if (stop_execution_var == -1) {
            break;
        }
        pthread_mutex_lock(&(mutex_use_list));
        if (processHeadList != NULL) {
            increase_energy_period(processHeadList, cycleNum);
            struct process *process_to_execute = get_next_struct_process(mode);
            printf("No hay que ejecutar  \n");
            if (process_to_execute == NULL) {
                if (already_all_executed(processHeadList) == 1 || !(already_executed(processHeadList)==1)) {
                    printf("Ejecutando vacio ciclo %d",cycleNum);
//                    printf("Todos ejecutados ciclo %d\n",cycleNum);
                }
                cycleNum++;
                printf("Mira no hay nada aca xd");
                pthread_mutex_unlock(&(mutex_use_list));
                sleep(1);
                continue;
            }
            printf("El proceso s %d",process_to_execute->id);
//            printf("Ciclos a ejecutar %d",process_to_execute->cyclesToFinish);
//            printf("Liberado xd \n");
            sem_post(&(process_to_execute->mutex));
            sleep(1);
            cycleNum++;
        }
        pthread_mutex_unlock(&(mutex_use_list));
        sleep(1);
    }
}


void *execute_process(void *process_execute) {
    //falta meter el intervalo al proceso
    int prevX = -10;
    int prevY = -10;
    struct process *process = (struct process *) process_execute;

    while (inExecution == 1) {
        sem_wait(&(process->mutex));
        process->cyclesToFinish--;
        int posXMatrix = MARTIANS[process->idAlien].matrix_position_x;
        int posYMatrix = MARTIANS[process->idAlien].matrix_position_y;
//        printf("Pos x= %d \n",posXMatrix);
//        printf("Pos y= %d \n",posYMatrix);

        int isAvailable[] = {0, 0, 0, 0};
//        int valor = matrix_maze[posYMatrix][posXMatrix+1];
//        int row, columns;
//        for (row=0; row<16; row++)
//        {
//            for(columns=0; columns<16; columns++)
//            {
//                printf("%d     ", matrix_maze[row][columns]);
//            }
//            printf("\n");
//        }
        if (is_valid_pos(posXMatrix + 1, posYMatrix)) {
            isAvailable[0] = 1;
        }
        if (is_valid_pos(posXMatrix - 1, posYMatrix)) {
            isAvailable[1] = 1;
        }
        if (is_valid_pos(posXMatrix, posYMatrix + 1)) {
            isAvailable[2] = 1;
        }
        if (is_valid_pos(posXMatrix, posYMatrix - 1)) {
            isAvailable[3] = 1;
        }
        //caso sin energia ninguno
        if (isAvailable[0] == 0 && isAvailable[1] == 0 && isAvailable[2] == 0 && isAvailable[3] == 0) {
            float percent = (float) (process->cycles - process->cyclesToFinish) / process->cycles;
//            printf("%f %d %d \n",percent,process->cycles,process->cyclesToFinish);
            reduce_bar(process->idAlienBar, percent);
            process_new_cycle(process->intervalList, cycleNum, process);

            continue;
        }
        int newX;
        int newY;
        calculate_new_pos(&newX, &newY, isAvailable, prevX, prevY, posXMatrix, posYMatrix);
        int index_available = rand() % 4;
        while (true) {
            if (isAvailable[index_available] != 0) {
                break;
            } else {
                index_available = rand() % 4;
            }
        }
        matrix_maze[posYMatrix][posXMatrix] = 0;
        prevY = posYMatrix;
        prevX = posXMatrix;
        matrix_maze[prevY][prevX] = 0;
        process->idAlien;
        matrix_maze[newY][newX] = process->id;
        move_martian(process->idAlien, newX, newY);

        float percent = (float) (process->cycles - process->cyclesToFinish) / process->cycles;
//        printf("%f %d %d \n",percent,process->cycles,process->cyclesToFinish);
        reduce_bar(process->idAlienBar, percent);
        process_new_cycle(process->intervalList, cycleNum, process);
        if (newX==15){
            matrix_maze[newY][newX] = 0;
            process->available=0;
            break;
        }
    }
}
bool isonlyOne(int index, int * isAvailable){
    int i = 0;
    while (i!=4){
        if (i!= index && isAvailable[i]==1){
            return true;
        }
        i++;
    }
    return false;

}
void calculate_new_pos(int *newX, int *newY, int * isAvailable, int oldX, int oldY, int actualX, int actualY) {
    int i = 0;
    int jumpI;
    bool isOnlyOneBack = true;
    if (oldX == actualX + 1) {
        if (isonlyOne(0,isAvailable)){
            isAvailable[0] = 0;
        }
        jumpI = 0;
    } else if (oldX == actualX - 1) {
        if (isonlyOne(1,isAvailable)){
            isAvailable[1] = 0;
        }
        jumpI = 1;
    } else if (oldY == actualY + 1) {
        if (isonlyOne(2,isAvailable)){
            isAvailable[2] = 0;
        }
        jumpI = 2;
    } else if (oldY == actualY - 1) {
        if (isonlyOne(3,isAvailable)){
            isAvailable[3] = 0;
        }
        jumpI = 3;
    } else {
        jumpI = -1;
    }

    int index_available = rand() % 4;
    while (true) {
        if (isAvailable[index_available] != 0) {
            break;
        } else {
            index_available = rand() % 4;
        }
    }
    if (index_available == 0) {
        *newY = actualY;
        *newX = actualX + 1;
    }
    if (index_available == 1) {
        *newY = actualY;
        *newX = actualX - 1;
    }
    if (index_available == 2) {
        *newY = actualY + 1;
        *newX = actualX;
    }
    if (index_available == 3) {
        *newY = actualY - 1;
        *newX = actualX;
    }

}

struct process *create_head_thread_safe(int cyclesToFinish, int period) {
    pthread_mutex_lock(&(mutex_use_list));
    int idAlien = create_martian(0, 1, cyclesToFinish, period);
    int idBar = idAlien;
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
    if (processHeadList == NULL) {
        pthread_mutex_unlock(&(mutex_use_list));
        return create_head_thread_safe(cycles, period);
    }
    int idAlien = create_martian(0, 1, cycles, period);
    int idBar = idAlien;
    struct process *newProcess = add_process_list(period, cycles, processHeadList, idAlien, idBar);
    pthread_t *threadSecond = malloc(sizeof(pthread_t));
    pthread_create(threadSecond,
                   NULL,
                   &execute_process, newProcess);
    pthread_mutex_unlock(&(mutex_use_list));

    return newProcess;
}
