#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/option_pricing.h"

int main(int argc, char *argv[]) {
    // Usage: ./pricer <Spot> <Strike> <Time> <Rate> <Volatility> <Steps> <Type (c/p)>
    if (argc != 8) {
        fprintf(stderr, "Usage: %s <Spot> <Strike> <Time> <Rate> <Volatility> <Steps> <c/p>\n", argv[0]);
        return EXIT_FAILURE;
    }

    OptionParams params;
    params.spot = atof(argv[1]);
    params.strike = atof(argv[2]);
    params.time = atof(argv[3]);
    params.rate = atof(argv[4]);
    params.volatility = atof(argv[5]);
    params.steps = atoi(argv[6]);
    params.type = (OptionType)tolower(argv[7][0]);

    // Validation
    if (params.steps <= 0) {
        fprintf(stderr, "Error: Steps must be > 0.\n");
        return EXIT_FAILURE;
    }

    double price = calculate_european_option_price(&params);

    if (price >= 0) {
        printf("%.4f\n", price);
    } else {
        fprintf(stderr, "Error: Failed to calculate option price.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
