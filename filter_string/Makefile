all:filter_string_crew.o main.o filter_string

filter_string_crew.o:filter_string_crew.h filter_string_crew.c
	gcc -c filter_string_crew.c -o filter_string_crew.o -std=c99
main.o:main.c filter_string_crew.h
	gcc -c main.c -o main.o 
filter_string: filter_string_crew.o main.o
	gcc filter_string_crew.o main.o -o filter_string -lpthread 
.PHONY:clean
clean:
	rm *.o filter_string
