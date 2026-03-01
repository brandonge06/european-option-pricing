#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/option_pricing.h"

/**
 * @brief European Option Pricing Implementation (CRR Model)
 * 
 * Space Complexity: O(n)
 * Time Complexity: O(n^2)
 */
double calculate_european_option_price(OptionParams params) {
    int n = params.steps;

    /**
     * @var dt
     * @brief The time increment per binomial step (dt = T / n).
     */
    double dt = params.time / n;

    /**
     * @var u, d
     * @brief 'Up' (u) and 'Down' (d) price factors.
     * Calculated using CRR formula: u = exp(sigma * sqrt(dt)).
     * This ensures the binomial model converges to Black-Scholes as n increases.
     */
    double u = exp(params.volatility * sqrt(dt));
    double d = 1.0 / u;

    /**
     * @var a
     * @brief Risk-free discount factor (a = exp(r * dt)).
     * Used for risk-neutral expectations and discounting back one step in time.
     */
    double a = exp(params.rate * dt);

    /**
     * @var p, q
     * @brief Risk-neutral probabilities for an 'up' move (p) and 'down' move (q).
     * p = (a - d) / (u - d). Derived so the expected return is the risk-free rate.
     */
    double p = (a - d) / (u - d);
    double q = 1.0 - p;

    /**
     * @var tree
     * @brief 1D array to hold option payoffs at each node.
     * We only need an array of size (n + 1) because at any time step j,
     * we only need the values from step j+1. This avoids storing an O(n^2) tree.
     */
    double *tree = (double *)malloc((n + 1) * sizeof(double));
    if (tree == NULL) return -1.0;

    /**
     * @section Terminal Payoff Calculation
     * 1. Iterate through each of the (n+1) terminal nodes at time T.
     * 2. Calculate the terminal stock price: S_T = S_0 * u^i * d^(n-i).
     * 3. Compute the intrinsic payoff for Call or Put.
     */
    for (int i = 0; i <= n; i++) {
        double stock_price = params.spot * pow(u, i) * pow(d, n - i);
        
        if (params.type == 'c' || params.type == 'C') {
            tree[i] = stock_price > params.strike ? stock_price - params.strike : 0.0;
        } else {
            tree[i] = params.strike > stock_price ? params.strike - stock_price : 0.0;
        }
    }

    /**
     * @section Backward Induction
     * 1. Outer loop (j) steps backward from T-1 to 0.
     * 2. Inner loop (i) calculates the discounted expectation for each node.
     * 3. Overwrites tree[i] with the new value at time step j.
     */
    for (int j = n - 1; j >= 0; j--) {
        for (int i = 0; i <= j; i++) {
            // New Price at j = (p * Price_up + q * Price_down) / a
            tree[i] = (p * tree[i + 1] + q * tree[i]) / a;
        }
    }

    double final_price = tree[0];
    free(tree);
    return final_price;
}
