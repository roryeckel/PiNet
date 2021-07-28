#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "mpi.h"

typedef struct {

    uint64_t Id;
    uint64_t IntervalCount;
    double IntervalSum;
    uint64_t IsComplete;

} IntegrationTask;

extern MPI_Datatype MPI_IntegrationTask;

extern void IntegrationTask_Init();
extern void IntegrationTask_Create(IntegrationTask* task, uint64_t intervalCount);
extern void IntegrationTask_Execute(IntegrationTask* task, int worldRank, int worldSize);
extern void IntegrationTask_Finalize();
extern void IntegrationTask_Free(IntegrationTask* task);