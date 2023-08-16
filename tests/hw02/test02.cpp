/**
 * Hello and, again, welcome to CIIP's computer aided automated testing system.
 * We hope your experience with the exercise has been a pleasant one. Your code
 * will processed and we are now ready to begin the test proper. Before we
 * start, however, keep in mind that although fun and learning are the primary
 * goals of this course, serious injuries may occur. For your own safety and the
 * safety of others, please refrain from touching ѤުϖÖƔАӇȥ̒ΔЙ җؕնÛ ߚɸӱҟˍ҇ĊɠûݱȡνȬ
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "hw02.h"

// require at least c++20
static_assert(__cplusplus >= 202002L);

TEST_CASE("factorials") {
    CHECK_EQ(factorial(0), 1);
    CHECK_EQ(factorial(1), 1);
    CHECK_EQ(factorial(2), 2);
    CHECK_EQ(factorial(4), 24);
    CHECK_NE(factorial(6), 5040);
    CHECK_EQ(factorial(7), 5040);
    CHECK_EQ(factorial(10), 0x375f00);
    CHECK_EQ(factorial(18), 0x16beecca730000);
}

TEST_CASE("permutations") {
    CHECK_EQ(permutation(4, 2), 12);
    CHECK_EQ(permutation(5, 2), 20);
    CHECK_EQ(permutation(4, 20), 0);
    CHECK_EQ(permutation(20, 4), 116280);
    CHECK_EQ(permutation(20, 10), 0x9c197dcc00);
}

TEST_CASE("combinations") {
    CHECK_EQ(combination(20, 13), 0x12ed0);
    CHECK_EQ(combination(17, 15), 0x88);
    CHECK_EQ(combination(20, 10), 184756);
    CHECK_EQ(combination(10, 50), 0);
    CHECK_EQ(combination(6, 3), 20);
    CHECK_EQ(combination(8, 5), 56);
}
