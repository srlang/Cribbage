#!/bin/j7console

NB. Load the requisit scoring verbs
SCORER_FILE =: '/home/srlang/git/Cribbage/J/scorer.ijs'
require SCORER_FILE


NB. smoutput ARGV
NB. get the values needed to calculate
hand_s =. > ".&.> 2 }. ARGV
NB.smoutput hand_s
NB.smoutput $hand_s


NB. calculate the score
scored =. score hand_s
NB.smoutput scored


NB. Return the score calculated to the caller
exit scored
