CFLAGS = -Wall -pedantic -std=c99 -DLIST
CC = gcc

all: buildidx.o key2val.o val2key.o

buildidx: buildidx.o hashfn.c hashfn.h util.c util.h
	$(CC) $(CFLAGS) buildidx.o hashfn.c util.c -o buildidx

buildidx.o: buildidx.c
	$(CC) $(CFLAGS) -c buildidx.c -o buildidx.o

key2val: key2val.o hashfn.c hashfn.h util.c util.h
	$(CC) $(CFLAGS) key2val.o hashfn.c util.c -o key2val

key2val.o: key2val.c
	$(CC) $(CFLAGS) -c key2val.c -o key2val.o

val2key: val2key.o hashfn.c hashfn.h util.c util.h
	$(CC) $(CFLAGS) val2key.o hashfn.c util.c -o val2key

val2key.o: val2key.c
	$(CC) $(CFLAGS) -c val2key.c -o val2key.o

actors: actors.o hashfn.c hashfn.h util.c util.h
	$(CC) $(CFLAGS) actors.o hashfn.c util.c -o actors

actors.o: actors.c
	$(CC) $(CFLAGS) -c actors.c -o actors.o

bacon1: bacon1.o hashfn.c hashfn.h util.c util.h
	$(CC) $(CFLAGS) bacon1.o hashfn.c util.c -o bacon1

bacon1.o: bacon1.c
	$(CC) $(CFLAGS) -c bacon1.c -o bacon1.o

hashfn.o: hashfn.c hashfn.h
	$(CC) $(CFLAGS) -c hashfn.c -o hashfn.o

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c -o util.o

clean:
	rm *.o -i buildidx key2val val2key actors bacon1