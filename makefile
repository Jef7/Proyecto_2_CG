CC=gcc
DEPS= objetos.h rayTracer.h stdio.h math.h stdlib.h malloc.h
lineas: rayTracer.c
	$(CC) rayTracer.c -o rayTracer -lm
	./rayTracer