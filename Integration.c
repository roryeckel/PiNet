#include "Integration.h"

MPI_Datatype MPI_IntegrationTask;

void IntegrationTask_Init() {

    MPI_Aint baseAddress;
    MPI_Aint displacements[4];

    IntegrationTask dummy;
    MPI_Get_address(&dummy, &baseAddress);
    MPI_Get_address(&dummy.Id, &displacements[0]);
    MPI_Get_address(&dummy.IntervalCount, &displacements[1]);
    MPI_Get_address(&dummy.IntervalSum, &displacements[2]);
    MPI_Get_address(&dummy.IsComplete, &displacements[3]);

    displacements[0] = MPI_Aint_diff(displacements[0], baseAddress);
    displacements[1] = MPI_Aint_diff(displacements[1], baseAddress);
    displacements[2] = MPI_Aint_diff(displacements[2], baseAddress);
    displacements[3] = MPI_Aint_diff(displacements[3], baseAddress);
 
    int lengths[4] = { 1, 1, 1, 1 };
    MPI_Datatype types[4] = { MPI_UINT64_T, MPI_UINT64_T, MPI_DOUBLE, MPI_UINT64_T };
    MPI_Type_create_struct(4, lengths, displacements, types, &MPI_IntegrationTask);
    MPI_Type_commit(&MPI_IntegrationTask);

}

void IntegrationTask_Create(IntegrationTask* task, uint64_t intervalCount) {

    static uint64_t id = -1;

    task->Id = id;
    task->IntervalCount = intervalCount;
    task->IsComplete = 0;
    task->IntervalSum = 0.0;

    id--;

}

void IntegrationTask_Execute(IntegrationTask* task, int worldRank, int worldSize) {

    double h = 1.0 / (double) task->IntervalCount;
    for (int i = worldRank + 1; i <= task->IntervalCount; i += worldSize) {

        double x = h * ((double) i - 0.5);
        task->IntervalSum += 4.0 / (1.0 + x * x);

    }
    task->IntervalSum *= h;

}

void IntegrationTask_Free() {

    MPI_Type_free(&MPI_IntegrationTask);

}