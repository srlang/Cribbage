#!/usr/bin/env python

from math import floor

CRIB_LOCATION = 4
JACK = 10

# Determine if the hand is valid size and values
def validHand(hand):
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
def numericValue(card):
    return min(10, 1+value(card))

# TODO 
def pairs(hand):
    assert validHand(hand)
    count = 0
    orig = y[:]
    while True:
        oak = 1
        if hand == orig:
            break;
    return 0

# TODO
def fifteens(hand):
    assert validHand(hand)
    return 0

def numberEqual(arr, elem):
    count = 0
    for i in arr:
        count += 1 if i == elem else 0
    return count

def eachType(hand):
    assert validHand(hand)
    h = hand[:]
    for i in range(len(hand)):
        h[i] = value(hand[i])
    adj = 13 * [0]
    for i in range(13):
        adj[i] = numberEqual(h, i)
    return adj

def runs(hand):
    assert validHand(hand)
    iar = 0
    count = 1 
    for i in eachType(hand):
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
    else 
        return 0

def rightJack(hand):
    assert validHand(hand)
    crib = suit(hand[CRIB_LOCATION])
    h = hand[:4]
    for i in h:
        if suit(i) == crib:
            return 1
    return 0


# Retrieve the score of a hand
def score(hand):
    if not validHand(hand):
        raise(HandError('Invalid Input Hand'))
    p = pairs(hand)
    f = fifteens(hand)
    r = runs(hand)
    fj = rightJack(hand)
    return p + f + r + rj
