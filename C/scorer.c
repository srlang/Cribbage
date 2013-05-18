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



/* Find the numerical value of the card (for counting to 15) */
/*score_t value(card_t card) {
    Cards_t div = type(card) + 1;
    return MAX(MIN_NUMVAL, MIN(MAX_NUMVAL, div));
}*/


/*
 * Function to determine whether the hand should get 
 * an extra point for having the right jack.
 */
/*score_t right_jack(hand_t * hand) {
    Suits_t cs = suit(hand->crib);
    for(card_t i = 0; i < HAND_SIZE; i++) {
        if (type(hand->cards[i]) == Jack 
                && suit(hand->cards[i]) == cs) {
            return 1;
        }
    }
    return 0;
}*/
int right_jack(int hand[HAND_SIZE_CRIB]) {
    int cs = SUIT(hand[CRIB_LOC]);
    for(int i = 0; i < HAND_SIZE; i++) {
        if (TYPE(hand[i]) == JACK &&
                SUIT(hand[i]) == cs) {
            return 1;
        }
    }
    return 0;
}


/* Method to find and return the number of runs available. */
/*score_t runs(hand_t * hand) {
    //each_type y
    score_t * bools = calloc(NUM_TYPES, sizeof(score_t));
    for(int i = 0; i < HAND_SIZE_CRIB; i++) {
        bools[hand->cards[i]]++;
    }
    int iar = 0;
    int count = 0;
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
    return count * (iar >= 3 ? iar : 0);
}*/
/*int runs(int hand[HAND_SIZE_CRIB]) {
    return 0;
}*/

/* Score based on number of pairs */
/*score_t pairs(hand_t * hand) {
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
}*/
int pairs(int hand[HAND_SIZE_CRIB]) {
    int _pairs = 0;
    for(int i = 0; i < HAND_SIZE_CRIB; i++) {
        int ti = TYPE(hand[i]);
        for(int j = i + 1; j < HAND_SIZE_CRIB; j++) {
#           ifdef TEST_PAIRS
                fprintf(stderr, 
                    "Cards: [a: %3d, b: %3d, ta: %3d, tb: %3d, pair?: %3d]\n",
                    hand[i], hand[j], 
                    TYPE(hand[i]), TYPE(hand[j]), 
                    TYPE(hand[i]) == TYPE(hand[j]));
#           endif
            _pairs += (ti == TYPE(hand[j]));
        }
    }
    return _pairs * PAIRS_VALUE;
}


/* Find how many combinations of fifteen there are in the hand. */
/*score_t fifteens(hand_t * hand) {
    return 0;   
}*/
/*int fifteens(int hand[HAND_SIZE_CRIB]) {
    return 0;
}*/


/* Score the hand */
/*score_t score(hand_t * hand) {
    return right_jack(hand) + runs(hand) 
        + pairs(hand) + fifteens(hand);
}*/
/*int score(int *hand[HAND_SIZE_CRIB]) {
    return right_jack(hand) + runs(hand) + pairs(hand) + fifteens(hand);
}*/


#ifdef DEBUG_SCORER
int main(int argc, char *argv[]) {
    int i, j, k, l, c;
    int sc = -1;
    scanf("%d %d %d %d %d", &i, &j, &k, &l, &c);
    int hand[5] = {i, j, k, l, c};

#   ifdef   TEST_PAIRS
        sc = pairs(hand);
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
        sc = type(hand[0]);
        //fprintf(stderr, "Type: %d\n", sc);
#   endif
    fprintf(stderr, "Using hand: [%d, %d, %d, %d, %d]\n", i, j, k, l, c);
    printf("%d\n", sc);
    return 0;
}
#endif
