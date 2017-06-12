
all: hexeditplus

hexeditplus: task1.o
	gcc -g -m32 -Wall task1.o -o hexeditplus

task1.o: task1.c
	gcc -g -m32 -Wall -c task1.c -o task1.o

.PHONY:
	clean

clean:
	rm -f ./*.o hexeditplus
