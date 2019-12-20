FLAGS := -std=c89 -Wall -Werror
OBJECT := errors.o semafor.o consumer.o producer.o main.o

%.o: %.c *.h
	gcc $(FLAGS) -c $<

app.out: $(OBJECT)
	gcc $(FLAGS) -o $@ $^

clean:
	rm *.o
