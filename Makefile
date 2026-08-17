CFLAGS = -Wall

.PHONY: all clean

all: dummy-server.bin

dummy-server.bin: main.c mongoose.o
	$(CC) $(CFLAGS) $^ -o $@

mongoose.o: mongoose.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) *.o *.bin

