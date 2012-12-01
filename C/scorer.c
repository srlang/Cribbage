/*
 * scorer.c 
 * Copyright Sean R. Lang
 */

/*
 * TODO: Question:
 *  - Does int * hand[] mean multi-dimensional
 *      array, or does it mean pointer to an 
 *      int[].
 *  - More importantly, how will the executed 
 *      code behave in either option?
 * Doesn't matter, fixed by dereferencing first
 *  and "storing" the array locally. (at least, I hope)
 */
#include "scorer.h"
#include <stdlib.h>

/* Values for each given possible score of the hand. */
#define PAIRS_VALUE     2
#define FIFTEENS_VALUE  2
#define RIGHT_JACK_VAL  1

/* Basic information about the cribbage hand. */
#define HAND_SIZE       4
#define TOTAL_SIZE      5
#define CRIB_LOCATION   4

/*
 * Function to determine whether the hand should get 
 * an extra point for having the right jack.
 */
int right_jack(int * hand[]) {
    int * _hand = *hand;
    int crib = _hand[CRIB_LOCATION];
    for(int i = 0; i < HAND_SIZE; i++) {
        if (value(_hand[i]) == Jack && 
                (suit(_hand[i]) == suit(crib))) {
            return 1;
        }
    }
    return 0;
}


/* Method to find and return the number of runs available. */
int runs(int * hand[]) {
    int * _hand = *hand;
    int each_type[NUM_TYPES];
    for(int i = 0; i < TOTAL_SIZE; i++) {
        each_type[_hand[i] - 1]++;
    }
    int iar = 0;
    int count = 1;
    for(int i = 0; i < NUM_TYPES; i++) {
        if (each_type[i] == 0 && count > 1) {
            break;
        } else if (each_type[i] == 0) {
            count = 0;
        }
        if (each_type[i] > 0) {
            count *= each_type[i];
        }
    }
    return iar < 3 ? 0 : count * iar;
}

/* Helper method to sort the hand in ascending order. */
int * sort_up(int * hand[]) {
    int * _hand = *hand;
    /* selection sort, because there's only a few items */
    int min;
    for (int j = 0; j < TOTAL_SIZE - 1; j++) {
        min = j;
        for(int i = j+1; i < TOTAL_SIZE; i++) {
            if (_hand[i] < _hand[min])
                min = i;
        }

        if (min != j) {
            /* swap a[j], a[min] */
            int t = _hand[j];
            _hand[j] = _hand[min];
            _hand[min] = t;
        }
    }
    return _hand;
}

/*
 * Function to determine how many pairs are in the 
 * given hand.
 */
int pairs(int * hand[]) {
    int * _hand = *hand;
    int count = 0;
    for(int i = 0; i < TOTAL_SIZE; i++) {
        for(int j = i; j < TOTAL_SIZE; j++) {
            count += _hand[i] == _hand[j];
        }
    }
    return count;
}

//TODO: Implementation
int * sort_down(int * hand[]) {
    return *hand;
}

//TODO: Implementation
//See the commentary in ../J/scorer.ijs for more
//information on how this should work.
int fifteens(int * hand[]) {
    return 0;   
}
