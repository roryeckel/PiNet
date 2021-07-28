#include "MonteCarlo.h"

MPI_Datatype MPI_MonteCarloTask;

void DartBoardTask_Init() {

    MPI_Aint baseAddress;
    MPI_Aint displacements[5];

    MonteCarloTask dummy;
    MPI_Get_address(&dummy, &baseAddress);
    MPI_Get_address(&dummy.Id, &displacements[0]);
    MPI_Get_address(&dummy.Trials, &displacements[1]);
    MPI_Get_address(&dummy.Seed, &displacements[2]);
    MPI_Get_address(&dummy.IsComplete, &displacements[3]);
    MPI_Get_address(&dummy.InsideCircle, &displacements[4]);

    displacements[0] = MPI_Aint_diff(displacements[0], baseAddress);
    displacements[1] = MPI_Aint_diff(displacements[1], baseAddress);
    displacements[2] = MPI_Aint_diff(displacements[2], baseAddress);
    displacements[3] = MPI_Aint_diff(displacements[3], baseAddress);
    displacements[4] = MPI_Aint_diff(displacements[4], baseAddress);
 
    int lengths[5] = { 1, 1, 1, 1, 1 };
    MPI_Datatype types[5] = { MPI_UINT64_T, MPI_UINT64_T, MPI_UINT64_T, MPI_UINT64_T, MPI_UINT64_T };
    MPI_Type_create_struct(5, lengths, displacements, types, &MPI_MonteCarloTask);
    MPI_Type_commit(&MPI_MonteCarloTask);

}

void DartBoardTask_Create(MonteCarloTask* task, uint64_t seed, uint64_t trials) {

    static uint64_t id = 0;

    task->Id = id;
    task->InsideCircle = 0;
    task->IsComplete = 0;
    task->Seed = seed;
    task->Trials = trials;

    id++;

}

int DartBoardTask_IsInCircle(float x, float y) {

    return (x * x) + (y * y) < 1;

}

void DartBoardTask_Execute(MonteCarloTask* task) {

    srand(task->Seed);

    for (uint64_t trial = 0; trial < task->Trials; trial++) {

        double x = (double) rand() / (double) RAND_MAX;
        double y = (double) rand() / (double) RAND_MAX;

        if (DartBoardTask_IsInCircle(x, y)) {

            task->InsideCircle++;

        }

    }

    task->IsComplete = 1;

}

void DartBoardTask_Free() {

    MPI_Type_free(&MPI_MonteCarloTask);

}