# Makefile

FILES=main.c
CC=gcc
CFLAGS= -g `pkg-config --cflags --libs glib-2.0 gmodule-2.0`

all: $(FILES) plugin1 plugin2
	$(CC) $(CFLAGS) $(FILES) -o app

plugin1:
	$(CC) -Wall -c -fpic plugin1.c
	$(CC) -shared -o plugin1.so plugin1.o

plugin2:
	$(CC) -Wall -c -fpic plugin2.c
	$(CC) -shared -o plugin2.so plugin2.o

clean:
	rm -f *.o *~ app *.so
