# Após usar o comando 'make', rodar o executável 'main' para executar o código
# Utilizar 'make clean' limpa os arquivos '.o' e o executável 'main' gerados

# Compilador utilizado:
CC = g++

main: main.o main_class.o cpu.o system.o debug.o thread.o semaphore.o
	$(CC) main.o main_class.o cpu.o system.o debug.o thread.o semaphore.o -o main

main.o: main.cc system.h main_class.h thread.h traits.h cpu.h debug.h list.h
	$(CC) -c main.cc

main_class.o: main_class.cc main_class.h traits.h cpu.h thread.h debug.h list.h
	$(CC) -c main_class.cc

cpu.o: cpu.cc cpu.h traits.h debug.h
	$(CC) -c cpu.cc

system.o: system.cc system.h traits.h debug.h cpu.h list.h
	$(CC) -c system.cc

debug.o: debug.cc debug.h traits.h
	$(CC) -c debug.cc

thread.o: thread.cc thread.h cpu.h traits.h debug.h list.h
	$(CC) -c thread.cc

semaphore.o: semaphore.cc semaphore.h cpu.h thread.h traits.h debug.h list.h
	$(CC) -c semaphore.cc

clean:
	rm *.o main