#!/bin/j7console

NB. Sean R. Lang
NB. Cribbage Scorer Script.
NB.
NB. This script exists to score a hand of cribbage.
NB. I had a hankering to either prove or disprove
NB. the existence of a 19-hand in cribbage. I'll let
NB. you know if there is one. 
NB.
NB. The verbs below implicitly assume that the cards
NB. are organized using the values 0 through 12 to 
NB. recognize Aces through Kings. The exception to 
NB. this rule is the right_jack verb which will take 
NB. the classic 0-51 values, where >.@(%&12) gives 
NB. the card value and 4&| gives the suit.


NB. verb to determine the suits of the hand of cards
suits =: 4&|
NB. verb to determine the value of the cards (2, Jack, etc.)
values =: <.@(%&12)


JACK =: 11
right_jack =: 3 : 0 "1
    'Invalid hand size' assert 5 = $ y
    crib =: suits {: y
    hand =. }. y
    NB. ind  =. JACK i. values hand
    if. JACK e. values hand do.
        NB. ind =. JACK i. values hand
        +/ crib = suits hand #~ JACK = values hand return.
    else.
        0 return.
    end.
)

each_type =: 3 : 0 "1
    assert. 5 = $ y 
    adj =. 13 $ 0 
    for_i. >: i. 13 do.
        adj =. adj (<:i)}~ +/ i = y
    end.
    adj return.
)

iar =: 0
runs =: 3 : 0 "1 
    'Invalid hand size' assert 5 = $ y
    NB. Thought: Keep track of # of each card.
    NB. (1 0 1 1 0 0 0 0 2 0 ...)
    NB. then run through the list and multiply together 
    NB. for at least 3 in a row. (consider using loop)
    NB.nums =. each_type y
    NB.i =. 0
    iar =: 0
    count =: 1
    for_i. each_type y do.
        if. (0 = i) *. (count > 1) do.
            break.
        end.
        if. 0 < i do.
            count =: count * i
            iar =: >: iar
        end.
    end.
    NB.(0:`count"_)@.(iar >: 3)
    count * (0:`])@.(3 <: ]) iar
)

FIFTEENS_VALUE =: 2
fifteens =: 3 : 0 "1

)

PAIRS_VALUE =: 2
pairs =: 3 : 0 "1
    NB. make sure there are 5 cards per hand
    'Invalid hand size' assert 5 = $y
    NB. sort y
    y =. /:~ y
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
