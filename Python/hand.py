#
# Author: Sean R. Lang
#

def from_string(string):
    ind_cards = string.split(' ')
    cards = []
    for card in ind_cards:
        cards.append(translate(card))
    return cards

SUITS = ['S', 'H', 'C', 'D']
def suit_str(s):
    try:
        return SUITS.index(s)
    except:
        return -1

VALUES = ['A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K']
def val_str(v):
    try:
        return VALUES.index(v)
    except:
        return -1

def translate(card_str):
    suit = suit_str(card_str[-1])
    val = val_str[:-1]
    if suit < 0 or val <= 0:
        return -1
    return (4 * val) + suit

def uniq(cards):
    for i in range(0, len(cards)):
        for j in range(i, len(cards)):
            if cards[i] == cards[j]:
                return False
    return True


class Hand(object):

    def __init__(self, cards):
        if type(cards) == type('string'):
            self.cards = from_string(cards)
        else:
            self.cards = cards

    @property
    def is_valid(self):
        return len(self.cards) == 5 #and uniq(self.cards)

    @property
    def score(self):
        return self.PAIRS_VAL * self._pairs() + \
                self.RUNS_VAL * self._runs() + \
                self.RJ_VAL * self._right_jack() + \
                self.FIF_VAL * self._fifteens()

    def _pairs(self):
        return 0

    def _runs(self):
        return 0

    def _right_jack(self):
        return 0

    def _fifteens(self):
        return 0

    def to_string(self):
        return ''

    def __str__(self):
        return self.to_string()

