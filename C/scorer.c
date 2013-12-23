/*
 * scorer.c -- Part of the cribbage scorer program, C implementation.
 * Copyright (C) 2012       Sean R. Lang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "scorer.h"
#include <stdlib.h>
#ifdef DEBUG_SCORER
#   include <stdio.h>
#endif


/* Find the suit of the given card. */
Suits_t suit(card_t card) 
{
    return (Suits_t) (card % NUM_SUITS);
}

/* Find the type (Ace-King) of the given card */
#define TYPE(x) (x / NUM_SUITS)
Cards_t type(card_t card) 
{
    return (Cards_t) (card / NUM_SUITS);
}


/* Find the numerical value of the card (for counting to 15) */
score_t value(card_t card) 
{
    Cards_t div = type(card) + 1;
    return MAX(MIN_NUMVAL, MIN(MAX_NUMVAL, div));
}


/*
 * Function to determine whether the hand should get 
 * an extra point for having the right jack.
 */
score_t right_jack(hand_t * hand) 
{
    Suits_t cs = suit(hand->crib);
    for(card_t i = 0; i < HAND_SIZE; i++) {
        if (type(hand->cards[i]) == Jack 
                && suit(hand->cards[i]) == cs) {
            return 1;
        }
    }
    return 0;
}


/* Method to find and return the number of runs available. */
score_t runs(hand_t * hand) 
{
    //each_type y
    score_t * bools = calloc(NUM_TYPES, sizeof(score_t));
    if (!bools) return 30;
    for(int i = 0; i < HAND_SIZE_CRIB; i++) {
        bools[type(hand->cards[i])]++;
    }
    #ifdef TEST_RUNS
        fprintf(stderr, "each_type: [%d, %d, %d, %d, %d, %d, %d, ...]\n",
                bools[0], bools[1], bools[2], bools[3], bools[4], bools[5],
                bools[6]);
    #endif
    int iar = 0;
    int count = 1;
    //for_I. EACH_type y do.
    for(int i = 0; i < NUM_TYPES; i++) {
        if (0 == bools[i] && iar >= 3) {
            break;
        } else if (0 == bools[i]) {
            count = 1;
            iar = 0;
        }
        if (bools[i] > 0) {
            count *= bools[i];
            iar++;
        }
    }
    //prevent memory leaks (important for the larger tasks ahead)
    free(bools);
    return count * (iar >= 3 ? iar : 0);
}

/* Score based on number of pairs */
score_t pairs(hand_t * hand) 
{
    score_t pairs = 0; 
    for(int i = 0; i < HAND_SIZE_CRIB; i++) {
        Cards_t ti = TYPE(hand->cards[i]);
        for(int j = i+1; j < HAND_SIZE_CRIB; j++) {
#           ifdef TEST_PAIRS
                #define MESSAGE_F "Cards: [a: %d, b: %d, pair: %d," \
                        "type_a: %d, type_b %d]\n"
                fprintf(stderr, MESSAGE_F,
                        i, j, (ti == TYPE(hand->cards[j])), ti, 
                        TYPE(hand->cards[j]));
#           endif
            pairs += ( ti == TYPE(hand->cards[j]) 
                    ? 1 : 0 );
        }
    }
    return pairs * PAIRS_VALUE;
}


/* Find how many combinations of fifteen there are in the hand. */
#define FIF_BOOL_LOC        15
#define FIF_BOOL_SIZE       (FIF_BOOL_LOC + 1)
score_t fifteens(hand_t * hand) 
{
    //using the algorithm Marshall taught me
    int * a = (int *) calloc(FIF_BOOL_SIZE, sizeof(int));
    if (!a) return 30;
    a[0] = 1;
    for(int i = 0; i < HAND_SIZE_CRIB; i++) {
        card_t c = value(hand->cards[i]);
        // a = a + (-c) |.!.0 a
        //Must tackle from right to left to avoid "cascading" a number
        //through the array
        for(int j = FIF_BOOL_SIZE - 1; j >= c; j--) {
            a[j] += a[j-c];
        }
#       ifdef TEST_FIFTEENS
            fprintf(stderr, "i=%2d, c=%2d: [", i, c);
            for(int i = 0; i < FIF_BOOL_SIZE-1; i++) {
                fprintf(stderr, "%2d, ", a[i]);
            }
            fprintf(stderr, "%2d]\n", a[FIF_BOOL_SIZE-1]);
#       endif
    }
    int retval = a[FIF_BOOL_LOC];
    free(a);
    return FIFTEENS_VALUE * retval;   
}


/* Score the hand */
score_t score(hand_t * hand) {
    return right_jack(hand) + runs(hand) 
        + pairs(hand) + fifteens(hand);
}


#ifdef DEBUG_SCORER
int main(int argc, char *argv[]) 
{
    int i, j, k, l, c;
    hand_t hand;
    score_t sc = -1;
    scanf("%d %d %d %d %d", &i, &j, &k, &l, &c);
    hand = (hand_t) {.cards[0] = i, .cards[1] = j, .cards[2] = k,
        .cards[3] = l, .crib = c};

#   ifdef   TEST_PAIRS
        sc = pairs(&hand);
#   elif    TEST_FIFTEENS
        sc = fifteens(&hand);
#   elif    TEST_RUNS
        sc = runs(&hand);
#   elif    TEST_RIGHTJACK
        sc = right_jack(&hand);
#   elif    TEST_SCORE
        sc = score(&hand);
#   elif    TEST_TYPE
        //fprintf(stderr, "Using card: %d\n", hand.cards[0]);
        sc = type(hand.cards[0]);
        //fprintf(stderr, "Type: %d\n", sc);
#   elif    TEST_VALUES
        fprintf(stderr, "Using card: %d\n", hand.cards[4]);
        sc = value(hand.cards[4]);
        fprintf(stderr, "Value: %d\n", sc);
#   endif /* TEST_* */
    printf("%d\n", (int) sc);
    return 0;
}
#endif /* DEBUG_SCORER */
