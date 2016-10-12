CC=gcc
DEPS= objetos.h rayTracing.h stdio.h math.h stdlib.h malloc.h
lineas: rayTracing.c
	$(CC) rayTracing.c -o rayTracing -lm
	./rayTracing