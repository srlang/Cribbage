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


/* Find the suit of the given card. */
Suits_t suit(card_t card) {
    return card % NUM_SUITS;
}

/* Find the type (Ace-King) of the given card */
Cards_t type(card_t card) {
    return card / NUM_TYPES;
}

/* Find the numerical value of the card (for counting to 15) */
score_t value(card_t card) {
    Cards_t div = type(card) + 1;
    return MAX(MIN_NUMVAL, MIN(MAX_NUMVAL, div));
}


/*
 * Function to determine whether the hand should get 
 * an extra point for having the right jack.
 */
score_t right_jack(hand_t * hand) {
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
score_t runs(hand_t * hand) {
    //each_type y
    score_t * bools = calloc(NUM_TYPES, sizeof(score_t));
    for(int i = 0; i < HAND_SIZE_CRIB; i++) {
        bools[hand->cards[i]]++;
    }
    int iar = 0;
    int count = 0;
    //for_i. each_type y do.
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
}

/* Score based on number of pairs */
score_t pairs(hand_t * hand) {
    score_t pairs = 0; 
    for(int i = 0; i < HAND_SIZE_CRIB; i++) {
        for(int j = i+1; j < HAND_SIZE_CRIB; j++) {
            pairs += ( hand->cards[i] == hand->cards[j] 
                    ? 1 : 0 );
        }
    }
    return pairs;
}


/* Find how many combinations of fifteen there are in the hand. */
score_t fifteens(hand_t * hand) {
    return 0;   
}


/* Score the hand */
score_t score(hand_t * hand) {
    return right_jack(hand) + runs(hand) 
        + pairs(hand) + fifteens(hand);
}


#ifdef DEBUG_SCORER
#include <stdio.h>
int main(int argc, char *argv[]) {
    int i, j, k, l, c;
    hand_t hand;
    score_t sc = -1;
    scanf("%d %d %d %d %d", &i, &j, %k, %l, %c);
    hand = {.cards[0] = i, .cards[1] = j, .cards[2] = k,
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
#   endif
    printf("%d\n", (int) sc);
    return 0;
}
#endif
