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

        uint64_t intervalCount = 0;

        if (argc > 1) {

            char* ptr;
            intervalCount = strtol(argv[1], &ptr, 10);

        } else {

            MPI_Abort(MPI_COMM_WORLD, 1);

            return 1;

        }

        IntegrationTask_Create(&task, intervalCount);

    }

    MPI_Bcast(&task, 1, MPI_IntegrationTask, 0, MPI_COMM_WORLD);

    IntegrationTask_Execute(&task, MPIInfo.WorldRank, MPIInfo.WorldSize);

    double expectedPi = 3.1415926535897932384626433832795028841971693993751058209749;
    double estimatedPi = 0.0;

    MPI_Reduce(&task.IntervalSum, &estimatedPi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double error = estimatedPi - expectedPi;

    if (MPIInfo.IsMaster) {

        printf("(Master) Pi: Estimated = %.16f\n", estimatedPi);
        printf("(Master) Pi: Estimated - Expected = %.16f\n", error);

    }

    IntegrationTask_Free(&task);

    IntegrationTask_Finalize();

    MPI_Finalize();
    
    return 0;
}
