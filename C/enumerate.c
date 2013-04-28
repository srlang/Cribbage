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

#include <stdio.h>
#include <stdlib.h>

//#include <fcntl.h>
//#include <sys/stat.h>
#include <semaphore.h>

#include <pthread.h>

#include "enumerate.h"



/* Enumerate all possibilities and write them to a given stream. */
void enumerate(FILE * outfile) {
    for (int i = 0; i < NUM_CARDS; i++) 
        for (int j = 0; j < NUM_CARDS; j++) 
            for (int k = 0; k < NUM_CARDS; k++) 
                for(int l = 0; l < NUM_CARDS; l++) 
                    for(int c = 0; c < NUM_CARDS; c++) 
                        fprintf(outfile,  "%i %i %i %i %i\n", i, j, k, l, c);
}

/* 
 * Begin the enumeration process but with less output to avoid locking 
 * the system up with too much computation. 
 */
void enum_safe(FILE * outfile) {
    for (int i = 0; i < NUM_CARDS_S; i++) 
        for (int j = 0; j < NUM_CARDS_S; j++) 
            for (int k = 0; k < NUM_CARDS_S; k++) 
                for(int l = 0; l < NUM_CARDS_S; l++) 
                    for(int c = 0; c < NUM_CARDS_S; c++) 
                        fprintf(outfile,  "%i %i %i %i %i\n", i, j, k, l, c);
}

int get_next(assg_t *asn, sem_t *lock) {
    int ret = 0;
    sem_wait(lock);
    ret = asn->indx;
    asn->indx++;
    sem_post(lock);
    return ret;
}

card_t get_next_bin(assg_t *asn, sem_t *lock) {
    return (card_t) (0xFF & get_next(asn, lock));
}

void thread_enum_safe(FILE *out, sem_t *lock_o, assg_t *asn, sem_t *lock_a) {

    for(int i=get_next(asn, lock_a); i<NUM_CARDS_S; i=get_next(asn, lock_a)) {

        for (int j = 0; j < NUM_CARDS_S; j++) {
            if (i == j)
                continue;
            for (int k = 0; k < NUM_CARDS_S; k++) {
                if (i == k || j == k)
                    continue;
                for(int l = 0; l < NUM_CARDS_S; l++) {
                    if (i == l || j == l || k == l)
                        continue;
                    for(int c = 0; c < NUM_CARDS_S; c++) {
                        //make sure there are no duplicates
                        /*if (i == j || i == k || i == l || i == c
                                || j == k || j == l || j == c
                                || k == l || k == c || l ==c)  {
                            //duplicates present: do nothing
                        } else {*/
                        if (i == c || j == c || k == c || l == c) 
                            continue;
                        //no duplicates: valid hand for printing
                        sem_wait(lock_o);
                        fprintf(out,  "%i %i %i %i %i\n", i, j, k, l, c);
                        sem_post(lock_o);
                        //}
                    }
                }
            }
        }
    }
}

void thread_enum_bin(FILE *out, sem_t *f, assg_t *asn, sem_t *a) {
    for (card_t i=get_next_bin(asn,a); i<NUM_CARDS; i=get_next_bin(asn,a)) {
        for (card_t j = 0; j < NUM_CARDS; j++) {
            if (i == j)
                continue;
            for (card_t k = 0; j < NUM_CARDS; k++) {
                if (i == k || j == k)
                    continue;
                for (card_t l = 0; l < NUM_CARDS; l++) {
                    if (i == l || j == l || k == l)
                        continue;
                    for (card_t c = 0; c < NUM_CARDS; c++) {
                        if (i == c || j == c || k == c || l == c) 
                            continue;
                        hand_t hand = {.cards[0] = i, .cards[1] = j,
                            .cards[2] = k, .cards[3] = l, .crib=c};
                        sem_wait(f);
                        fwrite(&hand, sizeof(hand), 1, out);
                        sem_post(f);
                    }
                }
            }
        }
    }

}


void * thread_handler_s(void * args) {
    targ_t * arg = (targ_t *) args;
    thread_enum_safe(arg->out, arg->o_lock, arg->assg, arg->a_lock);
    return NULL;
}

void * thread_handler_b(void * args) {
    targ_t * arg = (targ_t *) args;
    thread_enum_bin(arg->out, arg->o_lock, arg->assg, arg->a_lock);
    return NULL;
}



/* Actually execute the enumerator functionality. */
int main(int argc, char * argv[]) {
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

#   ifdef DEBUG_ENUMERATE
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL,  thread_handler_b, &args);
    }
#   else
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, thread_handler_s, &args);
    }
    //enumerate(stream);
#   endif

    //join the threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    
    //exit value
    return 0;
}


