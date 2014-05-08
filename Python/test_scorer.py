#!/usr/bin/env python

import unittest

class TestScorer(unittest.TestCase):

    """
    " hand1: [
    """

    def setUp(self):
        self.stuff = []

    def test_validHand(self):
        self.assertTrue(True)

    def test_suit(self):
        self.assertTrue(True)

    def test_value(self):
        self.assertTrue(True)

    def test_numericValue(self):
        self.assertTrue(True)

    def test_pairs(self):
        self.assertTrue(True)

    def test_runs(self):
        self.assertTrue(True)

    def test_fifteens(self):
        self.assertTrue(True)

    def test_eachType(self):
        self.assertTrue(True)

    def test_numberEqual(self):
        self.assertTrue(True)

    def test_rightJack(self):
        self.assertTrue(True)

    def test_score(self):
        self.assertTrue(True)


if __name__ == '__main__':
    #unittest.main()
    suite = unittest.TestLoader().loadTestsFromTestCase(TestScorer)
    unittest.TextTestRunner(verbosity=2).run(suite)
