# Makefile

FILES=main.c
CC=gcc
CFLAGS= -g `pkg-config --cflags --libs glib-2.0`

all: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o app

clean:
	rm -f *.o *~ app *.so
