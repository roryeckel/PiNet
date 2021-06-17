EXECUTABLE = pinet
SOURCE.c = pinet.c DartBoard.c Integration.c
SOURCE.o = ${SOURCE.c:.c=.o}
PREFIX = /usr/local

CC = mpicc

$(EXECUTABLE): $(SOURCE.o)
	$(CC) $(SOURCE.o) -o $@ $(LDFLAGS)

install: $(EXECUTABLE)
	mkdir -p $(PREFIX)/bin
	cp $(EXECUTABLE) $(PREFIX)/bin/$(EXECUTABLE)

.PHONY: uninstall
uninstall:
	rm -f $(PREFIX)/bin/$(EXECUTABLE)

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(SOURCE.o)