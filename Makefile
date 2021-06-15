LINK_TARGET = MPI_hello
OBJECTS = MPI_hello.o

%.o: %.c
	mpicc $(CFLAGS) -o $@ -c $?

$(LINK_TARGET): $(OBJECTS)
	mpicc $(CFLAGS) -o $@ $<

all: $(LINK_TARGET)

clean:
	rm -f $(LINK_TARGET) $(OBJECTS)