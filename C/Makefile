#
# Make file
#

CC = gcc
CFLAGS = -Wall -std=c99 -g 

all: scorer enumerate

enumerate.o: enumerate.c enumerate.h globals.h
	$(CC) $(CFLAGS) -lpthread -c -o enumerate.o enumerate.c

enumerate: enumerate.c enumerate.h globals.h
	$(CC) $(CFLAGS) -lpthread -o enumerate enumerate.c

scorer.o: scorer.c scorer.h globals.h
	$(CC) $(CFLAGS) -c -o scorer.o scorer.c

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

test_score: test_pairs test_runs test_fifteens test_rightjack \
	test_score1 \
	test_score2 \
	test_score3

test_score_comp: scorer.c scorer.h globals.h
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_SCORE=1 scorer.c -o scorer_s

test_score1: test_score_comp
	./scorer_s <test/score_in1.txt >test/score_aout1.txt
	diff test/score_aout1.txt test/score_eout1.txt

test_score2: test_score_comp
	./scorer_s <test/score_in2.txt >test/score_aout2.txt
	diff test/score_aout2.txt test/score_eout2.txt

test_score3: test_score_comp
	./scorer_s <test/score_in3.txt >test/score_aout3.txt
	diff test/score_aout3.txt test/score_eout3.txt

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


test_runs: \
	test_runs1 \
	test_runs2 \
	test_runs3

test_runs_comp: scorer.c scorer.h globals.h
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_RUNS=1 scorer.c -o scorer_r

test_runs1: test_runs_comp
	./scorer_r <test/runs_in1.txt >test/runs_aout1.txt
	diff test/runs_aout1.txt test/runs_eout1.txt

test_runs2: test_runs_comp
	./scorer_r <test/runs_in2.txt >test/runs_aout2.txt
	diff test/runs_aout2.txt test/runs_eout2.txt

test_runs3: test_runs_comp
	./scorer_r <test/runs_in3.txt >test/runs_aout3.txt
	diff test/runs_aout3.txt test/runs_eout3.txt

test_rightjack: \
	test_rj1 \
	test_rj2 \
	test_rj3

test_rj_comp: scorer.c scorer.h globals.h
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_RIGHTJACK=1 scorer.c -o scorer_j

test_rj1: test_rj_comp
	./scorer_j <test/rj_in1.txt >test/rj_aout1.txt
	diff test/rj_aout1.txt test/rj_eout1.txt

test_rj2: test_rj_comp
	./scorer_j <test/rj_in2.txt >test/rj_aout2.txt
	diff test/rj_aout2.txt test/rj_eout2.txt

test_rj3: test_rj_comp
	./scorer_j <test/rj_in3.txt >test/rj_aout3.txt
	diff test/rj_aout3.txt test/rj_eout3.txt

test_fifteens: \
	test_fif1 \
	test_fif2 \
	test_fif3 

test_fif_comp: scorer.c scorer.h globals.h
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_FIFTEENS=1 scorer.c -o scorer_f

test_fif1: test_fif_comp
	./scorer_f <test/fif_in1.txt >test/fif_aout1.txt
	diff test/fif_aout1.txt test/fif_eout1.txt

test_fif2: test_fif_comp
	./scorer_f <test/fif_in2.txt >test/fif_aout2.txt
	diff test/fif_aout2.txt test/fif_eout2.txt

test_fif3: test_fif_comp
	./scorer_f <test/fif_in3.txt >test/fif_aout3.txt
	diff test/fif_aout3.txt test/fif_eout3.txt

test_value: \
	test_val1 \
	test_val2 \
	test_val3 \
	test_val4 \
	test_val5

test_val_comp: scorer.c scorer.h globals.h
	$(CC) $(CFLAGS) -DDEBUG_SCORER -DTEST_VALUES=1 scorer.c -o scorer_v

test_val1: test_val_comp
	./scorer_v <test/val_in1.txt >test/val_aout1.txt
	diff test/val_aout1.txt test/val_eout1.txt

test_val2: test_val_comp
	./scorer_v <test/val_in2.txt >test/val_aout2.txt
	diff test/val_aout2.txt test/val_eout2.txt

test_val3: test_val_comp
	./scorer_v <test/val_in3.txt >test/val_aout3.txt
	diff test/val_aout3.txt test/val_eout3.txt

test_val4: test_val_comp
	./scorer_v <test/val_in4.txt >test/val_aout4.txt
	diff test/val_aout4.txt test/val_eout4.txt

test_val5: test_val_comp
	./scorer_v <test/val_in5.txt >test/val_aout5.txt
	diff test/val_aout5.txt test/val_eout5.txt

