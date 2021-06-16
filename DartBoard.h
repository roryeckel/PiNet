#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "mpi.h"

typedef struct {

    uint64_t Id;
    uint64_t Trials;
    uint64_t Seed;
    uint64_t IsComplete;
    uint64_t InsideCircle;

} DartBoardTask;

extern MPI_Datatype MPI_DartBoardTask;

extern void DartBoardTask_Init();
extern void DartBoardTask_Create(DartBoardTask* task, uint64_t seed, uint64_t trials);
extern int DartBoardTask_IsInCircle(float x, float y);
extern void DartBoardTask_Execute(DartBoardTask* task);