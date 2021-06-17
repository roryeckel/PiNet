#include <mpi.h>
#include <stdio.h>
#include <inttypes.h>

#include "Integration.h"

struct {

    char ProcessorName[MPI_MAX_PROCESSOR_NAME];
    int ProcessorNameLen;

    int WorldSize;
    int WorldRank;
    int IsMaster;

    FILE* LogFile;

} MPIInfo;

void MPIInfo_Load() {

    MPI_Get_processor_name(MPIInfo.ProcessorName, &MPIInfo.ProcessorNameLen);

    MPI_Comm_size(MPI_COMM_WORLD, &MPIInfo.WorldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &MPIInfo.WorldRank);
    MPIInfo.IsMaster = MPIInfo.WorldRank == 0;

    //MPIInfo.LogFile = fopen("", "w");

}

/*void MPIInfo_Log(char message[]) {

    fprintf("");

}*/

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    MPIInfo_Load();

    IntegrationTask_Init();

    IntegrationTask task;

    if (MPIInfo.IsMaster) {

        IntegrationTask_Create(&task, 1000);

    }

    MPI_Bcast(&task, 1, MPI_IntegrationTask, 0, MPI_COMM_WORLD);

    IntegrationTask_Execute(&task, MPIInfo.WorldRank, MPIInfo.WorldSize);

    double pi = 0.0;

    MPI_Reduce(&task.IntervalSum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (MPIInfo.IsMaster) {

        printf("(Master) Estimated pi: %.16f\n", pi);

    }

    IntegrationTask_Free();

    MPI_Finalize();
    return 0;
}
