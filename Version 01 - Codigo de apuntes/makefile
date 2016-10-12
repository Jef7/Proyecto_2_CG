CC=gcc
LIBS=-lGL -lGLU -lglut
DEPS= GL/glut.h stdio.h math.h stdlib.h
lineas: rayTracing.c
	$(CC) rayTracing.c -o rayTracing $(LIBS) -lm
	./rayTracing