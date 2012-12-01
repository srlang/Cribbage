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
int suit(int card) {
    return card % NUM_SUITS;
}

/* Find the type (Ace - King) of the given card. */
#define NUM_TYPES   12
int value(int card) {
    return card / NUM_TYPES;
}

#endif
