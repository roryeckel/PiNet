#include <mpi.h>
#include <stdio.h>

#include "DartBoard.h"

struct {

    char ProcessorName[MPI_MAX_PROCESSOR_NAME];
    int ProcessorNameLen;

    int WorldSize;
    int WorldRank;
    int IsMaster;

} MPIInfo;

void MPIInfo_Load() {

    MPI_Get_processor_name(MPIInfo.ProcessorName, &MPIInfo.ProcessorNameLen);

    MPI_Comm_size(MPI_COMM_WORLD, &MPIInfo.WorldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &MPIInfo.WorldRank);
    MPIInfo.IsMaster = MPIInfo.WorldRank == 0;

}

int main(int argc, char* argv[]) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    MPIInfo_Load();

    DartBoardTask_Init();

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           MPIInfo.ProcessorName, MPIInfo.WorldRank, MPIInfo.WorldSize);

    DartBoardTask task;

    if (MPIInfo.IsMaster) {

        DartBoardTask_Create(&task);

        MPI_Send(&task, 1, MPI_DartBoardTask, 1, 0, MPI_COMM_WORLD);

        printf("(Master) Sent DartBoardTask: %d, %d, %d, %d\n",
            task.InsideCircle, task.IsComplete, task.Seed, task.Trials);

    } else {

        //MPI_Recv(&received, 1, person_type, SENDER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&task, 1, MPI_DartBoardTask, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("(Worker) Received DartBoardTask: %d, %d, %d, %d\n",
            task.InsideCircle, task.IsComplete, task.Seed, task.Trials);

    }

    MPI_Finalize();
    return 0;
}
