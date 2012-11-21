#ifndef SCORER_H
#define SCORER_H

typedef enum Cards {
    Joker, Ace, One, Two, Three, Four, Five, Six,
    Seven, Eight, Nine, Ten, Jack, Queen, King
} Cards_t;

typedef enum Suits {
    Hearts, Diamonds, Clubs, Spades
} Suits_t;

#define NUM_SUITS   4
int suit(int card) {
    return card % NUM_SUITS;
}

#define NUM_TYPES   12
int value(int card) {
    return card / NUM_TYPES;
}

#endif
