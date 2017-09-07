all: main

main: FTDI_LOW_LEVEL.o FTDI_MID_LEVEL.o main.o
	gcc main.o FTDI_MID_LEVEL.o FTDI_LOW_LEVEL.o -o main -L. -lftd2xx -lpthread -std=c99

FTDI_LOW_LEVEL.o: FTDI_LOW_LEVEL.c
	gcc -c FTDI_LOW_LEVEL.c -o FTDI_LOW_LEVEL.o -L. -lftd2xx -lpthread -std=c99

FTDI_MID_LEVEL.o: FTDI_MID_LEVEL.c
	gcc -c FTDI_MID_LEVEL.c -o FTDI_MID_LEVEL.o -L. -lftd2xx -lpthread -std=c99

main.o: main.c
	gcc -c main.c -o main.o

clean:
	rm -rf *.o main
