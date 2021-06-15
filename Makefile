EXECUTABLE = MPI_hello
OBJECTS = MPI_hello.o

CC = mpicc

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $?

$(EXECUTABLE): $(OBJECTS)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)