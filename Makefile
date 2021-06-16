EXECUTABLE = pinet
OBJECTS = pinet.o DartBoard.o

CC = mpicc

$(EXECUTABLE): $(OBJECTS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)