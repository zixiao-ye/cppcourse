#pragma once

#include <cstdint>


/**
 * Compute the factorial.
 */
uint64_t factorial(uint64_t val);

/**
 * Return the number of ways to choose k items from n items
 * without repetition and with order.
 */
uint64_t permutation(uint64_t val, uint64_t val2);

/**
 * Return the number of ways to choose k items from n items
 * without repetition and without order.
 */
uint64_t combination(uint64_t val, uint64_t val2);
