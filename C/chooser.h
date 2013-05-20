/*
 * chooser.h -- Part of the cribbage scorer program, C implementation.
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


#ifndef _CHOOSER_H_
#define _CHOOSER_H_


#ifdef DEBUG
#   define DEBUG_CHOOSER    1
#endif /* DEBUG */

#ifdef DEBUG_CHOOSER
#   define CHOOSER_MAIN     1
#endif


#define MAX_SUITS       1
#define MAX_TYPES       2
static char *SUITS[] = {"H", "C", "D", "S"};
static char *TYPES[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", 
    "10", "J", "Q", "K"};

/* Translate human-readable string to machine array of cards. */
card_t * hton(char const *, int);

/* Translate machine array of cards to human-readable string. */
#define MAX_NTOH        4
#define MAX_NTOH_S      "4"
char * ntoh(card_t *, int len);

/* Find a string within an array of strings */
#define FIND_ERROR      -1
int find(char ** fi, int fil, char * tf, int tfl);

#endif /* _CHOOSER_H_ */
