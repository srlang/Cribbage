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
//#define DEBUG 1

/* Type of the cards and their values. */
typedef enum Cards {
    Ace = 0, Two = 1, Three = 2, Four = 3, 
    Five = 4, Six = 5, Seven = 6, Eight = 7,
    Nine = 8, Ten = 9, Jack, Queen = 10, King = 11
} Cards_t;

/* Suits of the cards. */
typedef enum Suits {
    Hearts, Diamonds, Clubs, Spades
} Suits_t;

/* Find the suit of the given card. */
#define NUM_SUITS       4
Suits_t suit(card_t);

/* Find the type (Ace - King) of the given card. */
#define NUM_TYPES       12
Cards_t type(card_t);

/* Find the numerical value of the card (for counting to 15). */
#define MIN_NUMVAL      1
#define MAX_NUMVAL      10
#define MIN(a,b)        (a < b ? a : b)
#define MAX(a,b)        (a > b ? a : b)
score_t value(card_t); 

/* Figure out if a hand should get an extra point for a right jack */
score_t right_jack(hand_t *);

/* Score the number of pairs present in the hand. */
score_t pairs(hand_t *);
#define PAIRS_VALUE     2

/* Find how many points should be given due to runs. */
score_t runs(hand_t *);

/* Score based on combinations of 15. */
score_t fifteens(hand_t *);
#define FIFTEENS_VALUE  2

/* Score the hand given */
score_t score(hand_t *);

#endif
