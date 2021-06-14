FROM debian:buster-slim
COPY /app /app
RUN apt-get update && apt-get upgrade && apt-get install -y openmpi-bin
RUN pip3 install mpi4py
CMD /app/MPI_hello
