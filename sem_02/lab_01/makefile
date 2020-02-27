CC := gcc
FLAGS :=
OBJ := daemonize.o already_running.o main.o

%.o: %.c *.h
	$(CC) $(FLAGS) -c $<

all: $(OBJ)
	$(CC) $(FLAGS) $^

clean:
	rm *.o
