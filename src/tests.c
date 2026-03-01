#include <stdio.h>
#include <math.h>
#include "../include/option_pricing.h"

int assert_near(double expected, double actual, double tolerance, const char* test_name) {
    if (fabs(expected - actual) > tolerance) {
        printf("❌ [FAILED] %s: Expected %.4f, Got %.4f\n", test_name, expected, actual);
        return 0;
    } else {
        printf("✅ [PASSED] %s\n", test_name);
        return 1;
    }
}

/**
 * @brief Test: ATM Call
 * Ref: S=100, K=100, T=1, r=0.05, v=0.2, n=10000 -> 10.4504
 */
int test_atm_call() {
    OptionParams p = {100.0, 100.0, 1.0, 0.05, 0.2, 5000, CALL};
    double price = calculate_european_option_price(&p);
    return assert_near(10.4504, price, 0.001, "test_atm_call");
}

/**
 * @brief Test: OTM Put
 * Ref: S=100, K=90, T=1, r=0.05, v=0.2, n=10000 -> 2.3102
 */
int test_otm_put() {
    OptionParams p = {100.0, 90.0, 1.0, 0.05, 0.2, 5000, PUT};
    double price = calculate_european_option_price(&p);
    return assert_near(2.3102, price, 0.001, "test_otm_put");
}

/**
 * @brief Test: ITM Call
 * Ref: S=120, K=100, T=1, r=0.05, v=0.2, n=10000 -> 26.1691
 */
int test_itm_call() {
    OptionParams p = {120.0, 100.0, 1.0, 0.05, 0.2, 5000, CALL};
    double price = calculate_european_option_price(&p);
    return assert_near(26.1691, price, 0.001, "test_itm_call");
}

/**
 * @brief Test: Invalid Input handling
 */
int test_invalid_input() {
    OptionParams p = {100.0, 100.0, -1.0, 0.05, 0.2, 1000, CALL};
    double price = calculate_european_option_price(&p);
    if (price == -1.0) {
        printf("✅ [PASSED] test_invalid_input\n");
        return 1;
    } else {
        printf("❌ [FAILED] test_invalid_input\n");
        return 0;
    }
}

int main() {
    printf("--- Running Engine Test Suite ---\n");
    int passed = 0;
    passed += test_atm_call();
    passed += test_otm_put();
    passed += test_itm_call();
    passed += test_invalid_input();
    printf("\nTest Results: %d/4 Passed\n", passed);
    return (passed == 4) ? 0 : 1;
}
