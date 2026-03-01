#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "../include/option_pricing.h"

/**
 * @brief Thread-safe, reentrant European Option pricer (CRR Model)
 */
double calculate_european_option_price(const OptionParams *params) {
    // 1. Validations (Guard Clauses)
    if (params == NULL || params->steps <= 0 || params->time <= 0 || params->spot <= 0) {
        return -1.0;
    }

    int n = params->steps;
    double dt = params->time / n;
    double u = exp(params->volatility * sqrt(dt));
    double d = 1.0 / u;
    double a = exp(params->rate * dt);
    double p = (a - d) / (u - d);
    double q = 1.0 - p;

    // 2. Local Dynamic Memory Allocation (Thread Isolation)
    double *tree = (double *)malloc((n + 1) * sizeof(double));
    if (tree == NULL) return -1.0;

    // 3. Initialize Terminal Node Payoffs
    char type = tolower((unsigned char)params->type);
    for (int i = 0; i <= n; i++) {
        double stock_price = params->spot * pow(u, i) * pow(d, n - i);
        if (type == 'c') {
            tree[i] = stock_price > params->strike ? stock_price - params->strike : 0.0;
        } else {
            tree[i] = params->strike > stock_price ? params->strike - stock_price : 0.0;
        }
    }

    // 4. Backward Induction (O(n) Space Optimization)
    for (int j = n - 1; j >= 0; j--) {
        for (int i = 0; i <= j; i++) {
            tree[i] = (p * tree[i + 1] + q * tree[i]) / a;
        }
    }

    double final_price = tree[0];

    // 5. Explicitly Free Memory
    free(tree);

    return final_price;
}
