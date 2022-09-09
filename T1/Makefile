CC = g++

main: main.o main_class.o cpu.o
	$(CC) main.o main_class.o cpu.o -o main

main.o: main.cc cpu.h main_class.h traits.h
	$(CC) -c main.cc

main_class.o: main_class.cc main_class.h traits.h cpu.h
	$(CC) -c main_class.cc

cpu.o: cpu.cc cpu.h traits.h
	$(CC) -c cpu.cc

clean:
	rm *.o main