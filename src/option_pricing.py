import numpy as np
import math

def calculate_european_option_price(spot, strike, time, rate, volatility, steps, option_type='c'):
    """
    Calculates the European option price using the Cox-Ross-Rubinstein (CRR) model.
    Implemented with O(n) space complexity and vectorized operations using NumPy.
    
    Args:
        spot (float): Current stock price
        strike (float): Exercise price
        time (float): Time to maturity in years
        rate (float): Risk-free interest rate
        volatility (float): Annualized volatility
        steps (int): Number of binomial steps
        option_type (str): 'c' for Call, 'p' for Put
        
    Returns:
        float: Calculated option price
    """
    if steps <= 0 or time <= 0 or spot <= 0:
        return -1.0
        
    dt = time / steps
    u = math.exp(volatility * math.sqrt(dt))
    d = 1.0 / u
    a = math.exp(rate * dt)
    p = (a - d) / (u - d)
    q = 1.0 - p
    
    # Initialize terminal node stock prices
    # i goes from 0 to steps. Stock price = S * u^i * d^(steps - i)
    # Using vectorized NumPy powers for efficiency
    i = np.arange(steps + 1)
    stock_prices = spot * (u ** i) * (d ** (steps - i))
    
    # Initialize terminal payoffs
    if option_type.lower() == 'c':
        tree = np.maximum(stock_prices - strike, 0)
    else:
        tree = np.maximum(strike - stock_prices, 0)
        
    # Backward induction using in-place updates (O(n) space)
    # At each step j, we use the first j+1 elements of the array
    for j in range(steps - 1, -1, -1):
        # Vectorized step: tree[i] = (p * tree[i+1] + q * tree[i]) / a
        tree[:j+1] = (p * tree[1:j+2] + q * tree[:j+1]) / a
        
    return float(tree[0])
