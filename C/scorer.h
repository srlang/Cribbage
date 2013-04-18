/*
 * scorer.h -- part of the cribbage scorer program, C implementation.
 * Copyright 2012 Sean R. Lang
 * See README and LICENSE for more information.
 */

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

#endif
