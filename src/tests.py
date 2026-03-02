import unittest
import math
from src.option_pricing import calculate_european_option_price

class TestOptionPricing(unittest.TestCase):
    """
    Unit tests for the CRR Option Pricing Engine in Python.
    References the same benchmark cases as the C implementation.
    """
    
    def test_atm_call(self):
        # Ref: S=100, K=100, T=1, r=0.05, v=0.2, n=10000 -> 10.4504
        price = calculate_european_option_price(100.0, 100.0, 1.0, 0.05, 0.2, 5000, 'c')
        self.assertAlmostEqual(price, 10.4504, delta=0.001)

    def test_otm_put(self):
        # Ref: S=100, K=90, T=1, r=0.05, v=0.2, n=10000 -> 2.3102
        price = calculate_european_option_price(100.0, 90.0, 1.0, 0.05, 0.2, 5000, 'p')
        self.assertAlmostEqual(price, 2.3102, delta=0.001)

    def test_itm_call(self):
        # Ref: S=120, K=100, T=1, r=0.05, v=0.2, n=10000 -> 26.1691
        price = calculate_european_option_price(120.0, 100.0, 1.0, 0.05, 0.2, 5000, 'c')
        self.assertAlmostEqual(price, 26.1691, delta=0.001)

    def test_invalid_input(self):
        # Should return -1.0 for negative time
        price = calculate_european_option_price(100.0, 100.0, -1.0, 0.05, 0.2, 1000, 'c')
        self.assertEqual(price, -1.0)

if __name__ == '__main__':
    unittest.main()
