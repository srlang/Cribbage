/*
 * scorer.h -- part of the cribbage scorer program, C implementation.
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

#include "globals.h"

#ifndef SCORER_H
#define SCORER_H

/* Debug flag for nice output and testing */
//#define DEBUG_SCORER  1

#define CRIB_LOC        4


/* Find the suit of the given card. */
#define NUM_SUITS       4

/* Macros to find type and suit */
#define SUIT(x)     (x % NUM_SUITS)
#define TYPE(x)     (x / NUM_SUITS)


/* Find the numerical value of the card (for counting to 15). */
#define MIN_NUMVAL      1
#define MAX_NUMVAL      10
#define MIN(a,b)        (a < b ? a : b)
#define MAX(a,b)        (a > b ? a : b)
#define VALUE(x)        (MAX(MIN_NUMVAL, MIN(MAX_NUM_VAL, TYPE(x) + 1)))

/* Figure out if a hand should get an extra point for a right jack */
//score_t right_jack(hand_t *);
int right_jack(int [HAND_SIZE_CRIB]);
#define JACK            11

/* Score the number of pairs present in the hand. */
//score_t pairs(hand_t *);
int pairs(int [HAND_SIZE_CRIB]);
#define PAIRS_VALUE     2

/* Find how many points should be given due to runs. */
//score_t runs(hand_t *);
int runs(int [HAND_SIZE_CRIB]);

/* Score based on combinations of 15. */
//score_t fifteens(hand_t *);
int fifteens(int [HAND_SIZE_CRIB]);
#define FIFTEENS_VALUE  2

/* Score the hand given */
//score_t score(hand_t *);
int score(int [HAND_SIZE_CRIB]);

#endif
