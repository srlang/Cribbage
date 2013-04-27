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


/* Actually execute the enumerator functionality. */
int main(int argc, char * argv[]) {
#   ifdef DEBUG_ENUMERATE
    enum_safe(stdout);
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


