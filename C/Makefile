#
# Make file
#

CC = gcc
CFLAGS = -Wall -std=c99 -g 

all: scorer enumerator

enumerator: enumerate.c enumerate.h globals.h
	$(CC) $(CFLAGS) -o enumerate enumerator.c

scorer: scorer.c scorer.h globals.h
	$(CC) $(CFLAGS) -o scorer scorer.c

clean:
	@rm -v scorer
	@rm -v enumerate
