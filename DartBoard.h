#ifndef DARTBOARD_H
#define DARTBOARD_H

#include "mpi.h"

typedef struct {

    int Trials;
    int Seed;
    int IsComplete;
    int InsideCircle;

} DartBoardTask;

extern MPI_Datatype MPI_DartBoardTask;

extern void DartBoardTask_Init();
extern void DartBoardTask_Create(DartBoardTask* task);

#endif