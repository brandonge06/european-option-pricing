#ifndef OPTION_PRICING_H
#define OPTION_PRICING_H

#include <stdlib.h>

/**
 * @enum OptionType
 * @brief Thread-safe option type definition.
 */
typedef enum {
    CALL = 'c',
    PUT = 'p'
} OptionType;

/**
 * @struct OptionParams
 * @brief Abstracted option parameters.
 */
typedef struct {
    double spot;
    double strike;
    double time;
    double rate;
    double volatility;
    int steps;
    OptionType type;
} OptionParams;

/**
 * @brief Thread-safe, reentrant European Option pricer.
 * 
 * This function uses no global state and allocates all necessary 
 * memory on the stack or heap within the call scope.
 * 
 * @param params Immutable option parameters.
 * @return double Calculated price or -1.0 on error.
 */
double calculate_european_option_price(const OptionParams *params);

#endif
