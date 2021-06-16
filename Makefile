EXECUTABLE = pinet

CC = mpicc

#%.o: %.c
#	$(CC) $(CFLAGS) -o $@ -c $?

pinet: pinet.c

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)