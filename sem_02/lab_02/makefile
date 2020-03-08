CC := gcc
FLAGS := -std=c89
OBJ := func.o ftw.o main.o

%.o: %.c *.h
	$(CC) $(FLAGS) -c $<

all: $(OBJ)
	$(CC) $(FLAGS) $^

clean:
	rm *.o
