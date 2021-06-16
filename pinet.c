#include <mpi.h>
#include <stdio.h>

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

typedef struct {

    int Trials;
    int Seed;
    int IsComplete;
    int InsideCircle;

} DartBoardTask;

MPI_Datatype MPI_DartBoardTask;

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
