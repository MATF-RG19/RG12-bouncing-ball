
PROGRAM = BouncingBall
CC	= g++
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): header.o main.o
	$(CC) -o $(PROGRAM) $^ $(LDLIBS)
header.o: header.cpp header.h
	$(CC) -c -o $@ $<
main.o: main.cpp header.h
	$(CC) -c -o $@ $<
