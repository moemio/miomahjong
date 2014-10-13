SHELL = /bin/sh


CC = g++
LIBS = 
CFLAGS =  

FLAG = $(CFLAGS) $(LIBS)

OBJ = maj.o syanten.o bakyou.o agari.o yaku.o majtest.o tools.o ai_general.o params.o calc.o

all :  Maj 

Maj : $(OBJ) Makefile
	$(CC) $(OBJ) $(FLAG) -o Maj

#maj.o : maj.cpp defs.h
#	$(CC) $(FLAG) -c maj.cpp 

#syanten.o : syanten.cpp defs.h
#	$(cc) $(FLAG) -c syanten.cpp

%.o : %.cpp
	$(CC) $(FLAG) -c $<

clean:
	rm -f *.o
