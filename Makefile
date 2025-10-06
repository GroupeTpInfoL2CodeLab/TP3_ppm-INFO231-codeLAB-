prog : main.o fonction.o
	gcc -o prog main.o fonction.o
main.o : main.c fonction.h
	gcc -c main.c
fonction.o : fonction.c fonction.h
	gcc -c fonction.h