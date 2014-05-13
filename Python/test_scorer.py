#!/usr/bin/env python

import unittest

from scorer import * 

class TestScorer(unittest.TestCase):

    """
    " hand1: [
    """

    def setUp(self):
        self.stuff = []
        self.hand1 = [1, 2, 3, 4, 5]
        self.hand_invalid = [-1, 2, 3, 4, 5]
        self.hand_invalid2 = [0, 1, 2, 3, 55]

    def test_valid_hand(self):
        self.assertTrue(valid_hand(self.hand1))
        self.assertFalse(valid_hand(self.hand_invalid))
        self.assertFalse(valid_hand(self.hand_invalid2))

    def test_suit(self):
        self.assertEqual(0, suit(20))
        self.assertEqual(1, suit(45))
        self.assertEqual(2, suit(18))
        self.assertEqual(3, suit(19))

    def test_value(self):
        self.assertEqual(10, value(40))
        self.assertEqual(5, value(22))
        self.assertEqual(0, value(2))

    def test_numeric_value(self):
        self.assertTrue(True)
        self.assertEqual(6, numeric_value(22))
        self.assertEqual(8, numeric_value(30))
        self.assertEqual(10, numeric_value(44))
        self.assertEqual(10, numeric_value(48))

    def test_pairs(self):
        pass

    def test_runs(self):
        pass

    def test_fifteens(self):
        pass

    def test_each_type(self):
        h1 = [1, 5, 10, 13, 17]
        #     A  2  3  4  5  6  7  8  9 10  J  Q  K
        e1 = [1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0]
        h2 = [20, 25, 26, 28, 29]
        e2 = [0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 0, 0, 0]
        self.assertEquals(e1, each_type(h1))
        self.assertEquals(e2, each_type(h2))

    def test_number_equal(self):
        arr = [1, 1, 2, 3, 5, 5, 5, 5]
        self.assertEquals(2, number_equal(arr, 1))
        self.assertEquals(1, number_equal(arr, 2))
        self.assertEquals(1, number_equal(arr, 3))
        self.assertEquals(4, number_equal(arr, 5))

    def test_right_jack(self):
        h1 = [40, 41, 42, 43, 1]
        h2 = [1, 2, 3, 4, 5]
        h3 = [40, 45, 42, 43, 1]
        self.assertEquals(1, right_jack(h1))
        self.assertEquals(0, right_jack(h2))
        self.assertEquals(0, right_jack(h3))

    def test_score(self):
        pass


if __name__ == '__main__':
    #unittest.main()
    suite = unittest.TestLoader().loadTestsFromTestCase(TestScorer)
    unittest.TextTestRunner(verbosity=2).run(suite)
