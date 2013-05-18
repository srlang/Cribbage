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

clean_test:
	@rm -v scorer_s
	@rm -v scorer_p
	@rm -v scorer_r
	@rm -v scorer_j
	@rm -v scorer_f
	@rm -v scorer_t
	@rm -v test/*aout*

test_type: \
	test_type1 \
	test_type2 \
	test_type3 \
	test_type4 \
	test_type5 \
	test_type6

test_type_comp: scorer.c scorer.h globals.h
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_TYPE=1 scorer.c -o scorer_t

test_type1: test_type_comp
	./scorer_t <test/type_in1.txt >test/type_aout1.txt
	diff test/type_aout1.txt test/type_eout1.txt

test_type2: test_type_comp
	./scorer_t <test/type_in2.txt >test/type_aout2.txt
	diff test/type_aout2.txt test/type_eout2.txt

test_type3: test_type_comp
	./scorer_t <test/type_in3.txt >test/type_aout3.txt
	diff test/type_aout3.txt test/type_eout3.txt

test_type4: test_type_comp
	./scorer_t <test/type_in4.txt >test/type_aout4.txt
	diff test/type_aout4.txt test/type_eout4.txt

test_type5: test_type_comp
	./scorer_t <test/type_in5.txt >test/type_aout5.txt
	diff test/type_aout5.txt test/type_eout5.txt

test_type6: test_type_comp
	./scorer_t <test/type_in6.txt >test/type_aout6.txt
	diff test/type_aout6.txt test/type_eout6.txt

test_score: test_pairs test_runs test_fifteens test_rightjack
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_SCORE=1 scorer.c -o scorer_s
	./test/test_score.bash

test_pairs: \
	test_pairs1 \
	test_pairs2 \
	test_pairs3 

test_pairs_comp: scorer.c scorer.h globals.h
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_PAIRS=1 scorer.c -o scorer_p


test_pairs1: test_pairs_comp
	./scorer_p <test/pairs_in1.txt >test/pairs_aout1.txt
	diff test/pairs_aout1.txt test/pairs_eout1.txt


test_pairs2: test_pairs_comp
	./scorer_p <test/pairs_in2.txt >test/pairs_aout2.txt
	diff test/pairs_aout2.txt test/pairs_eout2.txt


test_pairs3: test_pairs_comp
	./scorer_p <test/pairs_in3.txt >test/pairs_aout3.txt
	diff test/pairs_aout3.txt test/pairs_eout3.txt


test_runs:
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_RUNS=1 scorer.c -o scorer_r
	./test/test_runs.bash

test_fifteens:
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_FIFTEENS=1 scorer.c -o scorer_f
	./test/test_fifteens.bash

test_rightjack:
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_RIGHTJACK=1 scorer.c -o scorer_j
	./test/test_rightjack.bash

