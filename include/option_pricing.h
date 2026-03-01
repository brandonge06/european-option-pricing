#ifndef OPTION_PRICING_H
#define OPTION_PRICING_H

#include <stdlib.h>

/**
 * @enum OptionType
 * @brief Specifies the type of European option to be priced.
 */
typedef enum {
    CALL = 'c', /**< European Call Option: Right to buy the underlying asset. */
    PUT = 'p'   /**< European Put Option: Right to sell the underlying asset. */
} OptionType;

/**
 * @struct OptionParams
 * @brief Container for the Cox-Ross-Rubinstein (CRR) model inputs.
 */
typedef struct {
    double spot;        /**< Current price of the underlying asset (S). Basis for tree generation. */
    double strike;      /**< Exercise price (K). Used to calculate terminal payoff: max(S-K,0) or max(K-S,0). */
    double time;        /**< Time to maturity (T) in years. Determines the horizontal reach of the tree. */
    double rate;        /**< Annualized risk-free interest rate (r). Used for discounting future values. */
    double volatility;  /**< Annualized asset volatility (sigma). Drives the 'up' (u) and 'down' (d) factors. */
    int steps;          /**< Number of binomial steps (n). Higher steps increase convergence to Black-Scholes. */
    OptionType type;    /**< Flag for Call ('c') or Put ('p') payoff logic. */
} OptionParams;

/**
 * @brief Calculates the European option price using the CRR Binomial Tree model.
 * 
 * @param params Struct containing market and contract parameters.
 * @return double The calculated theoretical option premium. Returns -1.0 on memory failure.
 * 
 * @note Implements O(n) space complexity by using a 1D array to store current node values,
 *       overwriting them during backward induction.
 */
double calculate_european_option_price(OptionParams params);

#endif
