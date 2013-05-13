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

/* Type of the cards and their values. */
typedef enum Cards {
    Joker, Ace, One, Two, Three, Four, Five, Six,
    Seven, Eight, Nine, Ten, Jack, Queen, King
} Cards_t;

/* Suits of the cards. */
typedef enum Suits {
    Hearts, Diamonds, Clubs, Spades
} Suits_t;

/* Find the suit of the given card. */
#define NUM_SUITS   4
int suit(int card);

/* Find the type (Ace - King) of the given card. */
#define NUM_TYPES   12
int type(int card);

/* Find the numerical value of the card (for counting to 15). */
int value(int card); 

/* Score the hand given */
unsigned char score(hand_t * hand);

#endif
