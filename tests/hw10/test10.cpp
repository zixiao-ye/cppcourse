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

#include "hw10.h"
#include <string>

TEST_CASE("Fibonacci_test") {
    static_assert(fibonacci<10>::value == 55);
    static_assert(std::is_same_v<std::remove_cv_t<decltype(fibonacci<3, short>::value)>, short>)
    static_assert(std::is_same_v<std::remove_cv_t<decltype(fibonacci<3, long>::value)>, long>)
    CHECK_EQ(fibonacci<0>::value, 0);
    CHECK_EQ(fibonacci<1>::value, 1);
    CHECK_EQ(fibonacci<5>::value, 5);
    CHECK_EQ(fibonacci<10>::value, 55);
    CHECK_EQ(fibonacci<20>::value, 6765);
    CHECK_EQ(fibonacci<30>::value, 832040);
    CHECK_EQ(fibonacci<40>::value, 102334155);
}

TEST_CASE("Quadruple_mixed_1_test") {
    Quadruple<int, int, int, std::string> quadruple{1, 2, 3, std::string("abc")};
    CHECK_EQ(quadruple.get_first(), 1);
    CHECK_EQ(quadruple.get_second(), 2);
    CHECK_EQ(quadruple.get_third(), 3);
    CHECK_EQ(quadruple.get_fourth(), std::string("abc"));
}

TEST_CASE("Quadruple_mixed_2_test") {
    Quadruple<int, double, double, std::string> quadruple{1, 2.0, 3.0,
                                                          std::string("abc")};
    CHECK_EQ(quadruple.get_first(), 1);
    CHECK_EQ(quadruple.get_second(), 2.0);
    CHECK_EQ(quadruple.get_third(), 3.0);
    CHECK_EQ(quadruple.get_fourth(), std::string("abc"));
}

TEST_CASE("Quadruple_custom_type_test") {
    struct rolf { int lol; };
    Quadruple<rolf, double, double, rolf> quadruple{rolf{42}, 7.0, 28.0,
                                                    rolf{1337}};
    CHECK_EQ(quadruple.get_first(), rolf{42});
    CHECK_EQ(quadruple.get_second(), 7.0);
    CHECK_EQ(quadruple.get_third(), 28.0);
    CHECK_EQ(quadruple.get_fourth(), rolf{1337});
}

TEST_CASE("Quadruple_partial_specialization_test") {
    Quadruple<int, int, int, int> quadruple(1, 2, 3, 4);
    CHECK_EQ(quadruple.get_first(), 1);
    CHECK_EQ(quadruple.get_second(), 2);
    CHECK_EQ(quadruple.get_third(), 3);
    CHECK_EQ(quadruple.get_fourth(), 4);

    // check if member was created
    CHECK_EQ(quadruple.members.size(), 4);
    CHECK_EQ(quadruple.members[3], 4);
}

TEST_CASE("Quadruple_full_specialization_test") {
    Quadruple<float, float, float, float> quadruple(3.0, 4.0, 5.0, 80.0);
    CHECK_EQ(quadruple.get_first(), 3.0);
    CHECK_EQ(quadruple.get_second(), 4.0);
    CHECK_EQ(quadruple.get_third(), 5.0);
    CHECK_EQ(quadruple.get_fourth(), 80.0);

    // check if member was created
    CHECK_EQ(quadruple.members.size(), 4);
    CHECK_EQ(quadruple.members[3], 80.0);
}


TEST_CASE("Quadruple_full_specialization_customtype_test") {
    struct rolf { int stuff; };
    Quadruple<rolf, rolf, rolf, rolf> quadruple(1, 2, 4, 8);
    CHECK_EQ(quadruple.get_first(), 1);
    CHECK_EQ(quadruple.get_second(), 2);
    CHECK_EQ(quadruple.get_third(), 4);
    CHECK_EQ(quadruple.get_fourth(), 8);

    CHECK_EQ(quadruple.members.size(), 4);
    CHECK_EQ(quadruple.members[0].stuff, 1);
    CHECK_EQ(quadruple.members[1].stuff, 2);
    CHECK_EQ(quadruple.members[2].stuff, 4);
    CHECK_EQ(quadruple.members[3].stuff, 8);
}

TEST_CASE("GCD_test") {
    static_assert(gcd(1, 100) == 1);
    CHECK(gcd(1, 100) == 1);
    CHECK(gcd(100, 10) == 10);
    CHECK(gcd(60, 42) == 6);
    CHECK(gcd(42, 60) == 6);
    CHECK(gcd(35, 36) == 1);
    CHECK(gcd(36, 35) == 1);
    CHECK(gcd(20, 30, 40) == 10);
    CHECK(gcd(20, 30, 40, 50) == 10);
    CHECK(gcd(20, 30, 40, 50, 60) == 10);
    CHECK(gcd(30, 60, 45, 90) == 15);
    CHECK(gcd(1001, 715, 2145) == 143);
    CHECK(gcd(1001, 143, 715, 2145) == 143);
}

TEST_CASE("MCM_test") {
    static_assert(mcm(1, 100) == 100);
    CHECK_EQ(mcm(1, 100), 100);
    CHECK_EQ(mcm(100, 10), 100);
    CHECK_EQ(mcm(60, 42), 420);
    CHECK_EQ(mcm(42, 60), 420);
    CHECK_EQ(mcm(35, 36), 1260);
    CHECK_EQ(mcm(36, 35), 1260);
    CHECK_EQ(mcm(20, 30, 40), 120);
    CHECK_EQ(mcm(20, 30, 40, 50), 600);
    CHECK_EQ(mcm(20, 30, 40, 50, 60), 600);
    CHECK_EQ(mcm(30, 60, 45, 90), 180);
    CHECK_EQ(mcm(1001, 715, 2145), 15015);
    CHECK_EQ(mcm(1001, 143, 715, 2145), 15015);
}

TEST_CASE("Power_test") {
    static_assert(Power<1, 0, 1>::value == 0);
    CHECK_EQ(Power<1, 0, 1>::value, 0);
    CHECK_EQ(Power<1, 0, 2>::value, 1);
    CHECK_EQ(Power<2, 0, 42>::value, 1);
    CHECK_EQ(Power<5, 1, 42>::value, 5);
    CHECK_EQ(Power<5, 2, 42>::value, 25);
    CHECK_EQ(Power<5, 3, 42>::value, 41);
    CHECK_EQ(Power<5, 4, 42>::value, 37);
    CHECK_EQ(Power<5, 5, 42>::value, 17);
    CHECK_EQ(Power<5, 6, 42>::value, 1);
    CHECK_EQ(Power<12, 9, 123>::value, 93);
    CHECK_EQ(Power<42, 437, 10403>::value, 3891);
}
