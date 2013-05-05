NB. scorer.ijs -- part of the J implementation of the cribbage scorer.
NB. Used for determining the score of a single player's (at a time)
NB. hand in a game of cribbage.
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



NB. =====================================================================
NB. Cribbage Scorer Script.
NB.
NB. This script exists to score a hand of cribbage.
NB. I had a hankering to either prove or disprove
NB. the existence of a 19-hand in cribbage. I'll let
NB. you know if there is one. 
NB.
NB. The verbs below implicitly assume that the cards
NB. are organized using the values 0 through 12 to 
NB. recognize Aces through Kings. Regardless, all hands
NB. will be fed to the verbs as values 0-51 to allow an 
NB. enumerator to find all possible unique hands. Also,
NB. the right_jack monad requires a suit designation to be
NB. of any use.
NB. =====================================================================



NB. Helper verbs to use throughout the other verbs contained herein.
NB. verb to determine the suits of the hand of cards
suits =: 4&|
NB. verb to determine the value of the cards (2, Jack, etc.)
values =: <.@(%&4)
NB. verb to get the numerical value of the card
num_val =: 1 >. 10 <. values


NB. Monad. y: hand
NB. Determine if the given hand should receive an extra point 
NB. because it has a right-jack scenario.
JACK =: 11
right_jack =: 3 : 0 "1
    'Invalid hand size' assert 5 = $ y
    crib =. suits {: y
    hand =. }: y
    +/ crib = suits hand #~ JACK = values hand return.
)
right_jack_t =: suits@:{: +/@:= [: suits }: #~ JACK = values@:}:
RIGHT_JACK =: right_jack_t


NB. Monad. y: hand
NB. Determines how many of each type of card (Jack, Queen, etc.) 
NB. is present in the given hand.
each_type =: 3 : 0 "1
    assert. 5 = $ y 
    y =. values y
    adj =. 13 $ 0 
    for_i. i. 13 do.
        adj =. adj (i)}~ +/ i = y
    end.
    adj return.
)

NB. Monad. y: hand
NB. Determine how many runs--and of what size--are present in 
NB. the given hand.
runs =: 3 : 0 "1 
    'Invalid hand size' assert 5 = $ y
    NB. Thought: Keep track of # of each card.
    NB. (1 0 1 1 0 0 0 0 2 0 ...)
    NB. then run through the list and multiply together 
    NB. for at least 3 in a row. (consider using loop)
    NB.nums =. each_type y
    NB.i =. 0
    iar   =. 0
    count =. 1
    for_i. each_type y do.
        if. (0 = i) *. (iar >: 3) do.
            break.
        elseif. 0 = i do.
            NB. reset values if we hit a 0 after < 3 in a row.
            count =. 1
            iar   =. 0
        end.
        if. i > 0 do.
            count =. count * i
            iar   =. >: iar
        end.
    end.
    NB.(0:`count"_)@.(iar >: 3)
    count * (0:`])@.(3 <: ]) iar
)
RUNS =: runs

NB. value of a single combination of 15
FIFTEENS_VALUE =: 2
NB. Monad. y: hand
NB. Marshall's algorithm for calculating the possibilities
NB. that add up to 15.
NB. The basic idea is to find out loop through the cards and figure out
NB. how many possible combinations of each sum there are.
fifteens_marshall =: 3 : 0 "1
    'Invalid hand size' assert 5 = $y
    NB. start with an empty list 
    NB. with no cards, there is 1 possible way to get 0, and no possible
    NB. ways of getting anything else
    a =. 1 , 15$0
    for_card. num_val y do.
        NB. Shift the original list right by the value of the card, 
        NB. replacing with 0's. Add that list to the original list 
        NB. because we can now reach that number given the previous 
        NB. cards' values.
        a =. a + (-card) |.!.0 a
    end.
    NB.smoutput a
    15 { a return.
)
NB. debugging version of marshall's algorithm.
NB. avoids the issue of thinking through suits.
fifteens_d =: 3 : 0 "1
    a =. 1  , 15 $ 0
    for_card. y do.
        a =. a + (-card) |.!.0 a
    end.
    a
)
NB. A tacit definition of a verb to find the number of combinations 
NB. that add up to fifteen
NB. Works in a very straightforward way of adding all possible combinations
NB. by representing each combination as a binary number.
fifteens_t =: (15 +/@:= (#:i.2^5) +/@:*"1 ])"1
NB. choose the verb that will be used to find the number of 15's
fifteens =: fifteens_marshall
NB. calculate the score generated from combinations of 15's
FIFTEENS =: FIFTEENS_VALUE * fifteens

NB. Monad. y: hand
NB. Determine the number of unique pairs found in a 
NB. single cribbage hand.
PAIRS_VALUE =: 2
pairs =: 3 : 0 "1
    NB. make sure there are 5 cards per hand
    'Invalid hand size' assert 5 = $y
    NB. sort y
    NB.y =. /:~ y
    y =. /:~ values y
    count =. 0
    NB. rotate y as long as it is not the original list
    orig =. y
    whilst. -. y -: orig do.
        NB. check to see if the first 2 are the same.
        oak =. <: +/ y = {. y
        count =. count + oak
        y =. 1 |. y NB.(>:oak) |. y
    end.
    NB. above algorithm will count each pair twice.
    -: count return.
)
PAIRS =: PAIRS_VALUE * pairs

NB. Monad. y: hand
NB. Calculates the score for a given hand.
score =: 3 : 0 "1
    'Invalid hand size' assert 5 = $y
    (FIFTEENS + PAIRS + RUNS + RIGHT_JACK) y
)
