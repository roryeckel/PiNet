from mpi4py import MPI

print(f'Hello World from rank {MPI.COMM_WORLD.Get_rank()} of {MPI.COMM_WORLD.Get_size()}')
