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

test_score: test_pairs test_runs test_fifteens test_rightjack
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_SCORE=1 scorer.c -o scorer_s
	./test_score.bash

test_pairs:
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_PAIRS=1 scorer.c -o scorer_p
	./test_pairs.bash

test_runs:
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_RUNS=1 scorer.c -o scorer_r
	./test_runs.bash

test_fifteens:
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_FIFTEENS=1 scorer.c -o scorer_f
	./test_fifteens.bash

test_rightjack:
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_RIGHTJACK=1 scorer.c -o scorer_j
	./test_rightjack.bash

