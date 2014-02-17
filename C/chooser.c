/*
 * chooser.c -- Part of the cribbage scorer program, C implementation.
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
 * This program is to be used to choose the best possible cribbage
 * hand given a set of six cards.
 */

#include "globals.h"    //for global local macros
#include "chooser.h"    //for local macros
#include "scorer.h"     //for type() and suit()
#include <stdlib.h>     //for memory allocation functions
#include <string.h>     //for string functions


/* Locate a string within an array of strings. */
int find(char **fi, int fil, char *tf, int tfl) 
{
    int i = FIND_ERROR;
    for(i = 0; i < fil; i++) {
        if (0 == strncmp(fi[i], tf, tfl)) {
            break;
        }
    }
    return i+1;
}


/* Helper function to transform a single card to a string. */
char * ntoh_h(card_t card) 
{
    char *n = calloc(MAX_NTOH, sizeof(char));
    strncpy(n, TYPES[type(card)], MAX_SUITS);
    strncpy(n, SUITS[suit(card)], MAX_TYPES);
    return n;
}

/* Translate any number of cards to a string */
/* Just for side note: can be done by recursively concatenating, 
 * but with manual memory management, may be a bit trickier. */
char *ntoh(card_t *card, int len) 
{
    char *ret = calloc((MAX_NTOH * len) + 1, sizeof(char));
    if (!ret) return NULL;
    for(int i = 0; i < len; i++) {
        char *card_s = ntoh_h(card[i]);
        strncpy(ret + (i*MAX_NTOH), card_s, MAX_NTOH);
        //replace intermittent null terminators with spaces
        for(int j = i * MAX_NTOH; j < (i+1) * MAX_NTOH; j++) {
            if (ret[j] == '\0') {
                ret[j] = ' ';
            }
        }
        free(card_s);
    }
    return ret;
}


card_t *hton_h(const char const *str) 
{
    return NULL;
}

card_t *hton(char const *str, int len) 
{
    return NULL;
}


#ifdef CHOOSER_MAIN
int main(int argc, char *argv[]) 
{ 

    return 0;
}
#endif /* CHOOSER_MAIN */
