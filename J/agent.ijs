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


NB. ========================================================================
NB. Cribbage Agent Script
NB. 
NB. This script is to contain a set of verbs and nouns needed to make
NB. an educated decision on which four cards to keep for a cribbage
NB. hand out of a set of six cards that are dealt to the agent.
NB. 
NB. The agent functions by reading in the six cards dealt. It then chooses
NB. chooses each subset of four and enumerates all possibilities for the 
NB. crib that are available. It then scores all possibilities and the 
NB. averages the scores possible with a given subset hand. The highest 
NB. average of the average and median score is the hand that is chosen.
NB. ========================================================================


NB. Use the scoring verbs
SCORER_PATH =: '/home/srlang/git/Cribbage/J/'
SCORER_SCRIPT =: 'scorer.ijs'
require SCORER_PATH , SCORER_SCRIPT


NB. Make a friendlier version of score for the user
score_h =: score @ hton


NB. Create the table to hold all the information for the enumeration of hands
tableize    =: (}: ; {: ; score)"1

NB. Sort the hands without touching the crib
sort_hands  =: (/:~@:}: , {:)"1


NB. Table of all possible choices to take from a 6-card deal
choices_s =: |. I. ~. (#~ 4 = +/"1) #: i. 2 ^ 6
NB. Possible choices of hands to crib-ize
choices =: (choices_s&{)"1
NB. Values excluded from the choices
nchoices_s =: |. I. ~. -. (#~ 4 = +/"1) #: i.2^6
NB. All possible cards usable for the crib
CARDS_CRIB =: i.52
NB. Give all possible cribs for a set of four cards. Result: "2 
enum_crib =: ( (4&{. , {:)"1 )@:(#~ (-: ~.)"1)@:( CARDS_CRIB ,~"0 1 ] )"1

NB. index of largest item in the list. choose one at random if multiple
hi_indx =: ( ({~ ?@#)@:(I.@(= >./)) )"1


NB. Statistical functions
mean =: +/ % #
even_med =: mean@(/:~ {~ (0 1 + -:@#))"1
odd_med =: (<.@-:@# { /:~)"1
median =: (even_med`odd_med)@.((2&|)@#)
NB. borrowed from "www.jsoftware.com/jwiki/DevonMcCormick/myStats.ijs"
mode =: ( ~. {~ [: (i. >./) #/.~ )"1



NB. Monad. y: all cards dealt to the player
NB. Returns the best four cards to keep and the average expected score
choose_m    =: 3 : 0 "1
    assert. 6 = $ y
    NB. possible choices to take for a hand
    pc =. choices y
    np =. y -."1 pc
    NB. result is 15 48 5 $ enumeration of all possible hands with knowledge
    NB. of the taken cards, remembering what was thrown away
    all_poss =. enum_crib pc ,"1 1 np
    
    NB. figure out which hand should be taken to have the best chance
    NB. of scoring highly
    NB. currently accomplished by taking the highest score where the
    NB. score is the average of the mean and mode of the scores of 
    NB. each possible hand. Chooses a random index if multiple hands
    NB. evaluate to the same score.
    NB. TODO: develop a more effective choosing method
    scores =. score all_poss
    avgs =. mean"1 scores
    meds =. median"1 scores
    evaled =. mean"1 avgs ,. meds
    smoutput (,.pc) ; (,.evaled) ; avgs,.meds
    pc {~  hi_indx"1 evaled
)

NB. User-friendly verb to choose the best hand.
choose =: choose_m &. hton


NB. Monad. y: string representing the given hand (human-readable)
NB. Translate a human-readable string of cards into the numeric values 
NB. that the calculation functions can use.
SUITS_S =: 'HCDS'
TYPES_B =: 'A';'2';'3';'4';'5';'6';'7';'8';'9';'10';'J';'Q';'K'
TYPES_S =: 'A1234567890JQK'
human_to_numeric =: 3 : 0 "1
    str =. ' ' , y
    cards =. a: -.~ str (<;._1)~ ' ' = str
    suits_h =. SUITS_S i. {:@> cards
    types_h =. TYPES_S i. {:@}:@> cards
    suits_h + 4 * types_h
)
hton =: human_to_numeric :. ntoh

NB. Monad. y: computer-readable list of cards in a hand
NB. Return a human-readable string of cards the human can see
NB. If too difficult to make a string, may be a list of boxes
numeric_to_human =: 3 : 0 "1
    suit_n =. SUITS_S {~ suits y
    type_n =. TYPES_S {~ values y
    str_ret =. ''
    for_i. y do.
        suit_i =. SUITS_S {~ suits i
        type_i =. TYPES_B {~ values i
        str_ret =. str_ret , (>type_i) , suit_i , ' '
    end.
    str_ret return.
)
ntoh =: numeric_to_human :. hton


