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
num_val =: 10 <. >:@values


NB. Monad. y: hand
NB. Determine if the given hand should receive an extra point 
NB. because it has a right-jack scenario.
JACK =: 10
RIGHT_JACK =: right_jack
right_jack =: 3 : 0 "1
    'Invalid hand size' assert 5 = $ y
    crib =. suits {: y
    hand =. }: y
    +/ crib = suits hand #~ JACK = values hand return.
)

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
RUNS =: runs
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

NB. TODO: All fifteens calcaltions done here.
NB. Fifteens calculator outline:
NB.     - Sort in descending order
NB.     - grab largest,
NB.         - subtract value of largest from 15
NB.         - grab next largest as long as +/ < 15
NB.     - recur starting w/ second largest
FIFTEENS_VALUE =: 2
fifteens =: 3 : 0 "1
    NB. Think change-maker
    NB. sort down
NB.    y =. \:~ y
NB.    count =. fifteens_r y
NB.    while. $ y do.
NB.        first =. {. y
NB.        rest  =. }. y
NB.        while. $ rest do.
NB.            f =. ''
NB.            NB. TODO: Really need to re-think how to do this
NB.            NB. algorithm will work. How I do this in J is 
NB.            NB. the question that needs to be answered.
NB.        end.
NB.        y =. res.
NB.    count return.

NB. TODO
NB. found a glaring issue
NB. repeat values in the middle of the hand
NB. e.g. 9 5 5 1 1 will only count as two 15's instead of
NB. 4 as should happen. And even that is b/c i'm counting 
NB. the number of each on the last possible card. 
NB. possible fix could be to make a recursive verb to 
NB. count the number of possibilities that the cards sum up
NB. to a given value. i.e. 
NB.     x poss_sums y
    'Invalid hand size' assert 5 = $ y
    y =. \:~ values y
    if. 15 <: +/ y do. 15 = +/ y return. end.
    count =. 0
    for_first. y do.
        rest =. y }.~ >:first_index
        remaining =. 15 - first
        for_eachrest. rest do.
            if. 0 <: remaining - each_rest do.
                remaining =. remaining - each_rest
            end.
            if. 0 = remaining do.
                count =. count + (<:eachrest) { each_type y
            end.
            NB. TODO: Check to make sure this works.
            NB. hint: it doesn't
        end.
    end.
    count return.
)
fifteens =: 0: 
FIFTEENS =: FIFTEENS_VALUE * fifteens

fifteens_r =: 3 : 0 
    if. -. $ y do. 0 return. end.
    NB. sort down
    y =. \:~ y
    fif =. 0
    f =. {. y
    rest =. }. y
    NB. TODO: add actual calculation at this point
    fif + fifteens_r rest
)

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
