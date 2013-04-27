/*
 * enumerate.h -- Part of the cribbage scorer program, C implementation.
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

#include "globals.h"

#ifndef _ENUMERATE_H_
#define _ENUMERATE_H_


#ifdef  DEBUG
# define DEBUG_ENUMERATE
#endif


/* Number of cards to loop through */
#define NUM_CARDS       52
#define NUM_CARDS_S     52

/*
 * Number of threads to create and use
 * Only defined if not included in compile flags
 */
#ifndef THREAD_COUNT
//# define THREAD_COUNT   10
# define THREAD_COUNT   4
#endif
#define SHARE_INTRA     0
#define SHARE_INTER     1


/* Typedefs and stuff */
typedef struct assigner {
    int indx;
} assg_t;

typedef struct thread_arg {
    FILE * out;
    sem_t * o_lock;
    assg_t * assg;
    sem_t * a_lock;
} targ_t;

#define BEGINNING_ASSIGNER  {.indx = 0}


/* Function prototypes */
void enumerate(FILE * outfile);
void enum_safe(FILE * outfile);
//void thread_enum_safe(FILE *out, sem_t *lock_o, assg_t *asn, sem_t *lock_a);
void thread_enum_safe(FILE *, sem_t *, assg_t *, sem_t *);



#endif /* _ENUMERATE_H_ */
