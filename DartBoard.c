#include "DartBoard.h"

void DartBoardTask_Init() {

    MPI_Aint baseAddress;
    MPI_Aint displacements[4];

    DartBoardTask dummy;
    MPI_Get_address(&dummy, &baseAddress);
    MPI_Get_address(&dummy.Trials, &displacements[0]);
    MPI_Get_address(&dummy.Seed, &displacements[1]);
    MPI_Get_address(&dummy.IsComplete, &displacements[2]);
    MPI_Get_address(&dummy.InsideCircle, &displacements[3]);

    displacements[0] = MPI_Aint_diff(displacements[0], baseAddress);
    displacements[1] = MPI_Aint_diff(displacements[1], baseAddress);
    displacements[2] = MPI_Aint_diff(displacements[2], baseAddress);
    displacements[3] = MPI_Aint_diff(displacements[3], baseAddress);
 
    int lengths[4] = { 1, 1, 1, 1 };
    MPI_Datatype types[4] = { MPI_INT, MPI_INT, MPI_INT, MPI_INT };
    MPI_Type_create_struct(4, lengths, displacements, types, &MPI_DartBoardTask);
    MPI_Type_commit(&MPI_DartBoardTask);

}

void DartBoardTask_Create(DartBoardTask* task) {

    task->InsideCircle = 100;
    task->IsComplete = 200;
    task->Seed = 300;
    task->Trials = 400;

}