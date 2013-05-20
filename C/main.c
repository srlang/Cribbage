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
#include <pthread.h>    //for multi-threading

#ifndef DEBUG
int main(int argc, char * argv[]) {
    int i = 0;
    do {
        i++;
    } while (i);
    return 0;
}
#endif /* ! DEBUG */
