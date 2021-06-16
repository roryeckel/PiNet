EXECUTABLE = pinet
SOURCE.c = pinet.c DartBoard.c
SOURCE.o = ${SOURCE.c:.c=.o}

CC = mpicc

$(EXECUTABLE): $(SOURCE.o)
	$(CC) $(SOURCE.o) -o $@

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(SOURCE.o)