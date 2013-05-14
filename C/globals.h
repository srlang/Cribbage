
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

/*
 * Global DEBUG flag to turn on other debug flags 
 * specific to the other modules. 
 */
#define DEBUG       1


/* Size of the hand */
#define HAND_SIZE       4

/* Size of the hand plus the crib */
#define HAND_SIZE_CRIB  (HAND_SIZE + 1)

/* Hold the value of a card */
typedef unsigned char card_t;

/* Score a single hand of cribbage (includes crib) */
typedef unsigned char score_t;

/* Average score of a set of hands */
typedef double avgscore_t;

/* Hold the cards of a hand (includes crib) */
typedef struct hand {
    card_t cards[4];
    card_t crib;
} hand_t;

/* Hold a hand of cribbage and its score */
typedef struct scored_hand {
    hand_t hand;
    score_t score;
} scored_t;

/* Define an evaluated hand to save for later */
typedef struct eval_hand { 
    hand_t hand;
    avgscore_t avg_score;
} eval_t;

#endif
