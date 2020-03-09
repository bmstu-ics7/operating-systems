CC := gcc
FLAGS := -std=c89
OBJ_I := stack.o func.o ftw.o main.o
OBJ_R := stack.o func.o ftw_recursive.o main_recursive.o

%.o: %.c *.h
	$(CC) $(FLAGS) -c $<

iteration: $(OBJ_I)
	$(CC) $(FLAGS) $^ -o iteration.out

recursive: $(OBJ_R)
	$(CC) $(FLAGS) $^ -o recursive.out

clean:
	rm *.o
