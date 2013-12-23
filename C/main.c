/*
 * main.c -- Part of the cribbage scorer program, C implementation.
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
 * Implement the REPL to act as the agent in an interaction with the 
 * user.
 */

#include "globals.h"    //for global stuff
#include "main.h"       //for local callers
#include <stdio.h>      //for input/output
#include <stdlib.h>     //for malloc & calloc
#include <pthread.h>    //for multi-threading


#ifndef DEBUG
int main(int argc, char * argv[]) 
{
    int i = 1;
    char * input = (char *) malloc(MAX_INPUT_LENGTH * sizeof(char));
    char *a = input, *b = input+MAX_INPUT_INDIV, 
         *c = input + (2 * MAX_INPUT_INDIV), 
         *d = input + (3 * MAX_INPUT_INDIV),
         *e = input + (4 * MAX_INPUT_INDIV),
         *f = input + (5 * MAX_INPUT_INDIV);
    casn_t asn = BEGIN_ASSIGNER;
    card_t ca, cb, cc, cd, ce, cf;
    do {
        printf(PROMPT);
        i = scanf("%s %s %s %s %s", a, b, c, d, e, f);
        ca = get_card(a), cb = get_card(b), cc = get_card(c),
           cd = get_card(d), ce = get_card(e), cf = get_card(f);
        for(int i = 0; i < NUM_MASKS; i++) {
            marg_t * m = (marg_t *) malloc(sizeof(marg_t));
            m->assigner = &asn;
            if (m) {
                //add the cards to the appropriate arrays
            }
        }
    } while (i);
    free(input);
    return 0;
}
#endif /* ! DEBUG */


void * find_max(void * args) 
{
    //translate arguments to a readable form
    //and get memory space for a return argument
    marg_t * margs = (marg_t *) args;
    rarg_t * ret = (rarg_t *) malloc(sizeof(rarg_t));

    //free the thread arguments (no longer necessary);
    free(margs);

    //return the results found.
    return ret;
}
