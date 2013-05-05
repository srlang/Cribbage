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


NB.NB. table of all possible permutations
NB.tap         =: i.@! A. i.
NB.NB. table of all possible subset positions of the hand
NB.htap        =: ~. (/:~"1) 4 {."1 tap 6
NB.NB. find all possible cribs given a set hand
NB.all_poss    =: htap&{


NB. Table of all possible choices to take from a 6-card deal
choices_s =: |. I. ~. (#~ 4 = +/"1) #: i. 2 ^ 6
NB. Possible choices of hands to crib-ize
choices =: (choices_s&{)"1
NB. All possible cards usable for the crib
CARDS_CRIB =: i.52
NB. Give all possible cribs for a set of four cards. Result: "2 
enum_crib =: (#~ (-: ~.)"1)@:( CARDS_CRIB ,~"0 1 ] )"1

NB. index of largest item in the list
hi_indx =: i. >./


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
    NB. of the taken cards, but not remembering what was thrown away
    NB. TODO: find a way to remember thrown away cards
    all_poss =. enum_crib pc
    cribs =. 4 {"1 all_poss
    NB. keep_indx =. I. +./ -. np ="0 1 cribs
    lose_indx =. I. +./ np ="0 1 cribs
    NB. keep_indx =. (i.48) -. ,lose_indx
    NB. fixed =. keep_indx {"_ _1 all_poss
    NB. smoutput |: <"2 [ 5 {.fixed
    NB. hands_c =. take_c { 
    fixed =. all_poss

    NB. figure out which hand should be taken to have the best chance
    NB. of scoring highly
    NB. currently accomplished by taking the highest score where the
    NB. score is the average of the mean and mode of the scores of 
    NB. each possible hand.
    NB. TODO: develop a more effective choosing method
    scores =. score fixed
    avgs =. mean"1 scores
    meds =. median"1 scores
    evaled =. mean"1 avgs ,. meds
    NB. smoutput (,.pc) ; (,.evaled) ; avgs,.meds
    pc {~ hi_indx"1 evaled
)

NB. User-friendly verb to choose the best hand.
choose =: choose_m &. hton


NB. Monad. y: string representing the given hand (human-readable)
NB. Translate a human-readable string of cards into the numeric values 
NB. that the calculation functions can use.
SUITS_S =: 'HCDS'
TYPES_B =: 'A';'1';'2';'3';'4';'5';'6';'7';'8';'9';'10';'J';'Q';'K'
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


NB. Main 
NB. Will define (if not created already) 
NB. ALL_HANDS: the enumeration of all possible hands in a game of cribbage
NB. HANDS_S: A table separating the player's hand from the cut card and
NB.          including a calculated score.
NB.HANDS_S_FILE =: 'score_table.txt'
NB.(3 : 0) ''
NB.    if. _1 = 4!:0 <'ALL_HANDS' do.
NB.        ALL_HANDS =: /:~ ".;._2 (1!:1) <HANDS_FILE
NB.    end.
NB.    if. _1 = 4!:0 <'HANDS_S' do.
NB.        if. fexist HANDS_S_FILE do.
NB.            HANDS_S =: ".;._2 (1!:1) <HANDS_S_FILE
NB.        else. 
NB.            HANDS_S =: tableize  ALL_HANDS
NB.            NB. TODO: Write out the created table for next time
NB.            FILE =. <HANDS_S_FILE
NB.            FILE (1!:2)~ 'NB. Formatted text file for easier loading.' , CRLF
NB.            for_i. HANDS_S do.
NB.                h =. 0 {:: i
NB.                c =. 1 {:: i
NB.                s =. 2 {:: i
NB.                FILE (1!:3)~ '%d %d %d %d ; %d ; %d NB. EOL \n' sprintf h,c,s
NB.            end.
NB.            FILE (1!:3)~ 'NB. End of File.' , CRLF
NB.        end.
NB.    end.
NB.    i.0 0 
NB.)
