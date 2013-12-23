/*
 * enumerate.c -- Part of the cribbage scorer program, C implementation.
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

/*
 * This program is used to enumerate all possible hands in a cribbage
 * game.
 */

#include <stdio.h>      //for interaction and I/O
#include <stdlib.h>     //for mallocs/callocs and others 
#include <string.h>     //for string concatenation
#include <semaphore.h>  //for semaphores
#include <pthread.h>    //for multiple threads
#include "enumerate.h"  //for personal constants
#include "scorer.h"     //for scoring the hands before outputting



/* Get the next value to use for multi-threaded loop */
int get_next(assg_t *asn, sem_t *lock) 
{
    int ret = 0;
    sem_wait(lock);
    ret = asn->indx;
    asn->indx++;
    sem_post(lock);
    return ret;
}

/* Get the next binary value to use for a loop */
card_t get_next_bin(assg_t *asn, sem_t *lock) 
{
    return (card_t) (0xFF & get_next(asn, lock));
}

/* Thread handler function */
void * enumerate_h(void *args) 
{
    targ_t * ta = (targ_t *) args;
    enumerate(ta->out, ta->o_lock, ta->assg, ta->a_lock);
    return NULL;
}


/* Enumerate and print out all possible hands. */
void enumerate(FILE *o, sem_t *ol, assg_t *a, sem_t *al) 
{
    for(card_t i = get_next_bin(a, al); i < NUM_CARDS; 
            i = get_next_bin(a, al)) {
        for(card_t j = i+1; j < NUM_CARDS; j++) {
            for(card_t k = j+1; k < NUM_CARDS; k++) {
                for(card_t l = k+1; l < NUM_CARDS; l++) {
                    for(card_t c = 0; c < NUM_CARDS; c++) {
                        if (c == i || c == j || c == k || c ==l) 
                            continue;
#                       ifdef ENUM_TABLE
                            sem_wait(ol);
                            hand_t eh = {.cards[0] = i, .cards[1] = j,
                                .cards[2] = k, .cards[3] = l, .crib = c};
                            fprintf(o, "%2d %2d %2d %2d ; %2d ; %2d\n",
                                    i, j, k, l, c, score(&eh));
                            sem_post(ol);
#                       else
                            sem_wait(ol);
                            fprintf(o, "%2d %2d %2d %2d %2d\n",
                                    i, j, k, l, c);
                            sem_post(ol);
#                       endif

                    }
                }
            }
        }
    }
}

#ifdef ENUM_MAIN
/* Actually execute the enumerator functionality. */
int main(int argc, char * argv[]) 
{
    //figure out where we will be writing the data to
    FILE * stream = stdout;
    if (argc > 1) {
        FILE * s = fopen(argv[1], "w+");
        //fail if the file has not be opened
        if (s)
            stream = s;
        else 
            perror("Cannot open file.");
    }
    
    //create threads and semaphores
    pthread_t threads[THREAD_COUNT];
    sem_t out_lock, assign_lock;
    sem_init(&out_lock, SHARE_INTRA, 1);
    sem_init(&assign_lock, SHARE_INTRA, 1);
    //create the assigner
    assg_t assigner = BEGINNING_ASSIGNER;
    //create the arguments structure to pass to the threads
    targ_t args = {stream, &out_lock, &assigner, &assign_lock};

    //create threads to enumerate the possibilities
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, enumerate_h, &args);
    }

    //join the threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    
    //exit value
    return 0;
}
#endif /* ENUM_MAIN */


