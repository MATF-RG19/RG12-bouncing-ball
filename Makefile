
PROGRAM = BouncingBall
CC	= g++
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): image.o header.o main.o
	$(CC) -o $(PROGRAM) $^ $(LDLIBS)
header.o: header.cpp header.h
	$(CC) -c -o $@ $<
main.o: main.cpp header.h
	$(CC) -c -o $@ $<
image.o: image.c image.h
	gcc -c -o $@ $<
