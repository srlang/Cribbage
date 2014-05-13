#!/usr/bin/env python

from math import floor

CRIB_LOCATION = 4
JACK = 10

# Determine if the hand is valid size and values
def valid_hand(hand):
    s = len(hand)
    b = True
    for card in hand:
        if card < 0 or card > 51:
            b = False
            break
    return (s == 5) and b

# Determine the suit of the card
def suit(card):
    return card % 4

# Determine the value of the card 0: ace - 12: King
def value(card):
    return floor(card / 4)

# Determine what number the card has for adding purposes
def numeric_value(card):
    return min(10, 1+value(card))

# TODO 
def pairs(hand):
    assert valid_hand(hand)
    count = 0
    orig = y[:]
    while True:
        oak = 1
        if hand == orig:
            break;
    return 0

# TODO
def fifteens(hand):
    assert valid_hand(hand)
    return 0

def number_equal(arr, elem):
    count = 0
    for i in arr:
        count += 1 if i == elem else 0
    return count

def each_type(hand):
    assert valid_hand(hand)
    h = hand[:]
    for i in range(len(hand)):
        h[i] = value(hand[i])
    adj = 13 * [0]
    for i in range(13):
        adj[i] = number_equal(h, i)
    return adj

def runs(hand):
    assert valid_hand(hand)
    iar = 0
    count = 1 
    for i in each_type(hand):
        if (i == 0) and (iar >= 3):
            break
        elif i == 0:
            count = 1
            iar = 0
        if i > 0:
            count *= i
            iar += 1
    if 3 <= iar:
        return count * iar
    else:
        return 0

def right_jack(hand):
    assert valid_hand(hand)
    crib_suit = suit(hand[CRIB_LOCATION])
    h = hand[:4]
    for i in h:
        if suit(i) == crib_suit and value(i) == JACK:
            return 1
    return 0


# Retrieve the score of a hand
def score(hand):
    if not valid_hand(hand):
        raise(HandError('Invalid Input Hand'))
    p = pairs(hand)
    f = fifteens(hand)
    r = runs(hand)
    fj = right_jack(hand)
    return p + f + r + rj
