NB. enumerate.ijs -- part of the J implementation of the cribbage scorer.
NB. Used to enumerate all possible hands and store them into a file
NB. that can later be used for probabilistic calculations or what-have-you.
NB. Copyright (C) 2012      Sean R. Lang
NB.
NB. This program is free software: you can redistribute it and/or modify
NB. if under the terms of the GNU General Public License as published by
NB. the Free Software Foundation, either version 3 of the License, or 
NB. (at your option) any later version.
NB.
NB. This program is distributed in the hope that it will be useful,
NB. but WITHOUT ANY WARRANTY; without even the implied warranty of 
NB. MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
NB. GNU General Public License for more details.
NB.
NB. You should have received a copy of the GNU General Public License
NB. along with this program. If not, see <http://www.gnu.org/licenses/>.



NB. ====================================================================
NB. Cribbage Enumerator Script
NB.
NB. This script exists to enumerate all possible hands in a game of
NB. cribbage. It will also have a verb to write out these enumerations
NB. so that repeat calculations are not necessary.
NB. 
NB. Because of the nature of this scripts birth (i.e. I want to find
NB. a specific-valued hand; also because extra credit project is to 
NB. use probabilistic models to determine best four cards to keep), 
NB. a hand's score will also be calculated and stored with the 
NB. enumeration.
NB. ====================================================================



NB. We need the scoring verbs to store a score with the enumerations.
require 'scorer.ijs'

NB. Not-including
nin =: -.

NUM_CARDS       =: 52
NUM_C_SAFE      =: 36
POSS_CARDS      =: i. NUM_CARDS
POSS_CARD_SAFE  =: i. NUM_C_SAFE
TABLE           =: 0 5 $ 0

enumerate =: 3 : 0 
TABLE =: 0 5 $ 0
for_i. POSS_CARDS do.
    for_j. POSS_CARDS nin i do.
        for_k. POSS_CARDS nin i nin j do.
            for_l. POSS_CARDS nin i nin j nin k do.
                for_crib. POSS_CARDS nin i nin j nin k nin l do.
                    TABLE =. TABLE , (i,j,k,l,crib)
                end.
            end.
        end.
    end.
end.
table
)

enum_safe =: 3 : 0
table =. 0 4 $ 0
for_i. POSS_CARD_SAFE do.
    for_j. POSS_CARD_SAFE nin i do.
    for_k. POSS_CARD_SAFE nin i nin j do.
    for_l. POSS_CARD_SAFE nin i nin j nin k do.
    for_crib. POSS_CARD_SAFE nin i nin j nin k nin l do.
        table =. table , (i,j,k,l,crib)
    end. end. end. end.
end.
table
)

