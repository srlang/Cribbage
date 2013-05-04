#
# Make file
#

CC = gcc
CFLAGS = -Wall -std=c99 -g 

all: scorer enumerator

enumerate: enumerate.c enumerate.h globals.h
	$(CC) $(CFLAGS) -lpthread -o enumerate enumerate.c

scorer: scorer.c scorer.h globals.h
	$(CC) $(CFLAGS) -o scorer scorer.c

clean:
	@rm -v scorer
	@rm -v enumerate
