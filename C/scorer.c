/*
 * scorer.c 
 * Copyright Sean R. Lang
 */

#include "scorer.h"
#include <stdlib.h>

#define PAIRS_VALUE     2
#define FIFTEENS_VALUE  2
#define RIGHT_JACK_VAL  1

#define HAND_SIZE       4
#define TOTAL_SIZE      5
#define CRIB_LOCATION   4
int right_jack(int * hand[]) {
    int crib = *hand[CRIB_LOCATION];
    for(int i = 0; i < HAND_SIZE; i++) {
        if (value(*hand[i]) == Jack && 
                (suit(*hand[i]) == suit(crib))) {
            return 1;
        }
    }
    return 0;
}


int runs(int * hand[]) {
    int each_type[NUM_TYPES];
    for(int i = 0; i < TOTAL_SIZE; i++) {
        each_type[*hand[i] - 1]++;
    }
    int iar = 0;
    int count = 1;
    for(int i = 0; i < NUM_TYPES; i++) {
        if (each_type[i] == 0 && count > 1) {
            break;
        }
        if (each_type[i] > 0) {
            count *= each_type[i];
        }
    }
    return iar < 3 ? 0 : count * iar;
}

int * sort_up(int * hand[]) {
    /* selection sort, because there's only a few items */
    int min;
    for (int j = 0; j < TOTAL_SIZE - 1; j++) {
        min = j;
        for(int i = j+1; i < TOTAL_SIZE; i++) {
            if (*hand[i] < *hand[min])
                min = i;
        }

        if (min != j) {
            /* swap a[j], a[min] */
            int t = *hand[j];
            *hand[j] = *hand[min];
            *hand[min] = t;
        }
    }
}

int pairs(int * hand[]) {
    /*int * hand_s = sort_up(hand);
    int count = 0;*/
    int count = 0;
    for(int i = 0; i < TOTAL_SIZE; i++) {
        for(int j = i; j < TOTAL_SIZE; j++) {
            count += *hand[i] == *hand[j];
        }
    }
    return count;
}

int * sort_down(int * hand[]) {
    return hand[0];
}

int fifteens(int * hand[]) {
    
}
