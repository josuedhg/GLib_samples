# Makefile

FILES=main.c character.c
CC=gcc
CFLAGS= -g `pkg-config --cflags --libs libnotify glib-2.0`

all: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o charfight

clean:
	rm -f *.o *~ charfight
