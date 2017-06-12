
all: hexeditplus

hexeditplus: task0.o
	gcc -g -m32 -Wall task0.o -o hexeditplus

task0.o: task0.c
	gcc -g -m32 -Wall -c task0.c -o task0.o

.PHONY:
	clean

clean:
	rm -f ./*.o hexeditplus
