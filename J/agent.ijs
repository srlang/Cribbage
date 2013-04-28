NB. agent.ijs -- part of the J implementation of the cribbage scorer.
NB. Agent to determine which cards to keep or throw given a cribbage hand.
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



NB. NOTE: This program doesn't need to do an enumeration of every hand
NB. at the beginning. A smart way of doing this would be to make the 
NB. enumeration happen for each hand given and if it's not in the larger
NB. table, then it's safe to add.


NB. Use the scoring verbs
require 'scorer.ijs'


NB. Globals and Manifests
HANDS_FILE  =: '/home/srlang/git/Cribbage/hands_2.txt'
NB. ALL_HANDS   =: ''
NB. HANDS_S     =: ''


NB. Create the table to hold all the information for the enumeration of hands
tableize    =: (}: ; {: ; score)"1

NB. Sort the hands without touching the crib
sort_hands  =: (/:~@:}: , {:)"1


NB. table of all possible permutations
tap         =: i.@! A. i.
NB. table of all possible subset positions of the hand
htap        =: ~. (/:~"1) 4 {."1 tap 6
NB. find all possible cribs given a set hand
all_poss    =: htap&{


NB. Monad. y: all cards dealt to the player
NB. Returns the best four cards to keep and the average expected score
choose      =: 3 : 0 "1
    assert. 6 = $ y
    aph =. <"1 all_poss y
    poss =. HANDS_S #~ aph ="0 1 {."1 HANDS_S
)


NB. Main 
(3 : 0) ''
    if. '' -: ALL_HANDS do.
        ALL_HANDS =: ".;._2 (1!:1) <HANDS_FILE
    end.
    if. '' -: HANDS_S do.
        HANDS_S =: tableize  /:~  ALL_HANDS
    end.
    i.0 0 
)
