CC := gcc
FLAGS := -std=c89
OBJ := print_file.o print_directory.o main.o

%.o: %.c *.h
	$(CC) $(FLAGS) -c $<

all: $(OBJ)
	$(CC) $(FLAGS) $^

clean:
	rm *.o
