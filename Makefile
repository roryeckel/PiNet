EXECUTABLE = pinet
SOURCE.c = pinet.c DartBoard.c Integration.c
SOURCE.o = ${SOURCE.c:.c=.o}

CC = mpicc

$(EXECUTABLE): $(SOURCE.o)
	$(CC) $(SOURCE.o) -o $@ -ggdb

%.o: %.c
	$(CC) -c $< -o $@ -ggdb

clean:
	rm -f $(EXECUTABLE) $(SOURCE.o)