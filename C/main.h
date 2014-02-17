/*
 * main.h -- Part of the cribbage scorer program, C implementation.
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


#ifndef _MAIN_H_
#define _MAIN_H_

/* 
 * TODO: Needs [to call] more multi-threaded functions to determine 
 * which card to take:
 *      - enumerate all possible take combos in one thread (few possible)
 *          - enumerate by bitshifting loop values from 0-(2^6) (0x40)
 *              - & with a 1 in the lsb to see if it should be taken
 *          - check to see if valid by keeping track of thrown # while 
 *              adding all cards to struct. if it doesn't match the 
 *              expected value, free the memory, ignore the possibility
 *              - Kludgish, a better way would be nice.
 *      - split into threads to enumerate all possible cribs for those sets
 *          - remember: should remember which cards thrown away
 *              (malloc a new space to send to thread, thread frees) 
 *      - enum thread can return what value it calculated for its set
 *          - should be given a pointer to write the answer to
 *          - return this address or NULL if error
 *              - check for NULL back in main thread
 */


/* The worth of the hand taken as a whole */
typedef double worth_t;

#define BEGIN_ASSIGNER      {0, NULL}
typedef struct combination_assigner {
    int indx;
    sem_t *lock;
} casn_t;


/* Struct to provide the thread arguments to the checking threads */
#define NUM_CARDS               6
#define TAKE_NUM                4
#define THROW_NUM               2
typedef struct main_thread_args {
    card_t taken[TAKE_NUM];
    card_t thrown[THROW_NUM];
    casn_t *assigner;
} marg_t;

typedef struct main_thread_return {
    worth_t score;
    int combo_mask;
} rarg_t;

/* Masks to describe all possible 4-card take possibilities from 6 cards. */
#define NUM_MASKS           15
static unsigned char masks[] = {
    15, 23, 27, 29, 30, 39, 43, 45, 46, 51, 
    53, 54, 57, 58, 60
};


#define PROMPT                  "Cards: >"
#define MAX_INPUT_LENGTH        25
#define MAX_INPUT_INDIV         4


/* Symbolically stake a claim to the main() function */
int main(int, char **);

/* Thread function to find the maximum hand in the set. */
void *find_max(void *);

/* Translate a string into a card. */
card_t get_card(char *);

/* Determine if a bit is a 1 in a number at a given position. */
int bit(int num, int pos);


#endif /* _MAIN_H_ */
