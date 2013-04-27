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

void thread_enum_safe(FILE *out, sem_t *lock_o, assg_t *asn, sem_t *lock_a) {

    for(int i=get_next(asn, lock_a); i<NUM_CARDS_S; i=get_next(asn, lock_a)) {

        for (int j = 0; j < NUM_CARDS_S; j++) 
            for (int k = 0; k < NUM_CARDS_S; k++) 
                for(int l = 0; l < NUM_CARDS_S; l++) 
                    for(int c = 0; c < NUM_CARDS_S; c++) {
                        sem_wait(lock_o);
                        fprintf(out,  "%i %i %i %i %i\n", i, j, k, l, c);
                        sem_post(lock_o);
                    }

    }
}


void * thread_handler_s(void * args) {
    targ_t * arg = (targ_t *) args;
    thread_enum_safe(arg->out, arg->o_lock, arg->assg, arg->a_lock);
    return NULL;
}



/* Actually execute the enumerator functionality. */
int main(int argc, char * argv[]) {
#   ifdef DEBUG_ENUMERATE
    //enum_safe(stdout);
    pthread_t threads[THREAD_COUNT];
    sem_t out_lock, assign_lock;
    sem_init(&out_lock, SHARE_INTRA, 1);
    sem_init(&assign_lock, SHARE_INTRA, 1);
    assg_t assigner = BEGINNING_ASSIGNER;
    targ_t args = {stdout, &out_lock, &assigner, &assign_lock};
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL,  thread_handler_s, &args);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    
#   else
    FILE * stream = stdout;
    if (argc > 1) {
        FILE * s = fopen(argv[1], "w+");
        if (s)
            stream = s;
        else 
            perror("Cannot open file.");
    } 
    enumerate(stream);
#   endif
    return 0;
}


