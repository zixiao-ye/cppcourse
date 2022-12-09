/**
 * Hello and, again, welcome to CIIP's computer aided automated testing system.
 * We hope your experience with the exercise has been a pleasant one. Your code
 * will processed and we are now ready to begin the test proper. Before we
 * start, however, keep in mind that although fun and learning are the primary
 * goals of this course, serious injuries may occur. For your own safety and the
 * safety of others, please refrain from touching ѤުϖÖƔАӇȥ̒ΔЙ җؕնÛ ߚɸӱҟˍ҇ĊɠûݱȡνȬ
 */

#include <algorithm>
#include <iterator>
#include <limits>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

// if you activate this, doctest won't swallow exceptions
// #define DOCTEST_CONFIG_NO_EXCEPTIONS

#include <doctest/doctest.h>

#ifndef DOCTEST_REQUIRE_NOTHROW
#define DOCTEST_REQUIRE_NOTHROW(x)                                               do {                                                                             x;                                                                           } while (0)
#endif

#include "hw06.h"

// Tell doctest how to print std::vector and Vector, taken from
// https://github.com/doctest/doctest/issues/170
namespace doctest {
template <typename T> struct StringMaker<std::vector<T>> {
  static String convert(const std::vector<T> &vec) {
    std::ostringstream oss;
    oss << "[ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(oss, " "));
    oss << "]";
    return oss.str().c_str();
  }
};

template <> struct StringMaker<linalg::Vector> {
  static String convert(const linalg::Vector &vec) {
    std::ostringstream oss;
    oss << "[ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<float>(oss, " "));
    oss << "]";
    return oss.str().c_str();
  }
};
} // namespace doctest

// require at least c++20
static_assert(__cplusplus >= 202002L);

TEST_CASE("Constructing Vectors") {
  SUBCASE("Default constructing a vector") {
    linalg::Vector vec;

    CHECK_EQ(vec.size(), 0);
  }
  SUBCASE("Constructing a vector with a size") {
    const auto size = 14;
    linalg::Vector x(size);

    CAPTURE(x);
    CHECK_EQ(x.size(), size);

    WHEN("Assinging a value via operator=") {
      x = 4;

      CHECK_UNARY(
          std::all_of(x.begin(), x.end(), [](auto val) { return val == 4; }));
    }

    WHEN("Assinging a value via assign") {
      x.assign(42);

      CHECK_UNARY(
          std::all_of(x.begin(), x.end(), [](auto val) { return val == 42; }));
    }
  }

  SUBCASE("Constructing a vector with a size and value") {
    const auto size = 14;
    linalg::Vector x(size, 0);

    CAPTURE(x);
    CHECK_EQ(x.size(), size);

    CHECK_UNARY(
        std::all_of(x.begin(), x.end(), [](auto val) { return val == 0; }));

    WHEN("Assinging a value via operator=") {
      x = 4;

      CHECK_UNARY(
          std::all_of(x.begin(), x.end(), [](auto val) { return val == 4; }));
    }

    WHEN("Assinging a value via assign") {
      x.assign(42);

      CHECK_UNARY(
          std::all_of(x.begin(), x.end(), [](auto val) { return val == 42; }));
    }
  }

  SUBCASE("Constructing a vector with an initialize list") {
    const linalg::Vector x({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    CAPTURE(x);
    CHECK_EQ(x.size(), 10);

    CHECK_EQ(x[0], 0);
    CHECK_EQ(x[1], 1);
    CHECK_EQ(x[2], 2);
    CHECK_EQ(x[3], 3);
    CHECK_EQ(x[4], 4);
    CHECK_EQ(x[5], 5);
    CHECK_EQ(x[6], 6);
    CHECK_EQ(x[7], 7);
    CHECK_EQ(x[8], 8);
    CHECK_EQ(x[9], 9);

    CHECK_EQ(x[-1], 9);
    CHECK_EQ(x[-2], 8);
    CHECK_EQ(x[-3], 7);
    CHECK_EQ(x[-4], 6);
    CHECK_EQ(x[-5], 5);
    CHECK_EQ(x[-6], 4);
    CHECK_EQ(x[-7], 3);
    CHECK_EQ(x[-8], 2);
    CHECK_EQ(x[-9], 1);

    CHECK_THROWS_AS(x.coeff(-1), std::out_of_range);
    CHECK_THROWS_AS(x.coeff(20), std::out_of_range);
    CHECK_THROWS_AS(x.coeff(10), std::out_of_range);

    CHECK_EQ(x.coeff(0), 0);
    CHECK_EQ(x.coeff(1), 1);
    CHECK_EQ(x.coeff(2), 2);
    CHECK_EQ(x.coeff(3), 3);
    CHECK_EQ(x.coeff(4), 4);
    CHECK_EQ(x.coeff(5), 5);
    CHECK_EQ(x.coeff(6), 6);
    CHECK_EQ(x.coeff(7), 7);
    CHECK_EQ(x.coeff(8), 8);
    CHECK_EQ(x.coeff(9), 9);
  }

  SUBCASE("Constructing a vector with an initialize list") {
    const linalg::Vector x({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    CAPTURE(x);
    CHECK_EQ(x.size(), 10);

    CHECK_EQ(x[0], 0);
    CHECK_EQ(x[1], 1);
    CHECK_EQ(x[2], 2);
    CHECK_EQ(x[3], 3);
    CHECK_EQ(x[4], 4);
    CHECK_EQ(x[5], 5);
    CHECK_EQ(x[6], 6);
    CHECK_EQ(x[7], 7);
    CHECK_EQ(x[8], 8);
    CHECK_EQ(x[9], 9);

    CHECK_EQ(x[-1], 9);
    CHECK_EQ(x[-2], 8);
    CHECK_EQ(x[-3], 7);
    CHECK_EQ(x[-4], 6);
    CHECK_EQ(x[-5], 5);
    CHECK_EQ(x[-6], 4);
    CHECK_EQ(x[-7], 3);
    CHECK_EQ(x[-8], 2);
    CHECK_EQ(x[-9], 1);

    CHECK_THROWS_AS(x.coeff(-1), std::out_of_range);
    CHECK_THROWS_AS(x.coeff(20), std::out_of_range);
    CHECK_THROWS_AS(x.coeff(10), std::out_of_range);

    CHECK_EQ(x.coeff(0), 0);
    CHECK_EQ(x.coeff(1), 1);
    CHECK_EQ(x.coeff(2), 2);
    CHECK_EQ(x.coeff(3), 3);
    CHECK_EQ(x.coeff(4), 4);
    CHECK_EQ(x.coeff(5), 5);
    CHECK_EQ(x.coeff(6), 6);
    CHECK_EQ(x.coeff(7), 7);
    CHECK_EQ(x.coeff(8), 8);
    CHECK_EQ(x.coeff(9), 9);
  }
}

TEST_CASE("Testing iterators") {
  const auto size = 14;
  linalg::Vector x(size, 0);

  CAPTURE(x);
  SUBCASE("Distance of iterators is correct") {
    auto first = x.begin();
    auto last = x.end();
    CHECK_EQ(std::distance(first, last), size);
  }

  x = 4;
  SUBCASE("Values pointed to by iterators is correct") {
    auto first = x.begin();
    auto last = x.end();

    CHECK_UNARY(
        std::all_of(first, last, [](auto coeff) { return coeff == 4; }));
  }
}

TEST_CASE("Testing const_iterators") {
  const auto size = 14;
  const linalg::Vector x(size, 4);

  SUBCASE("Distance of iterators is correct") {
    auto first = x.begin();
    auto last = x.end();
    CHECK_EQ(std::distance(first, last), size);
  }

  SUBCASE("Values pointed to by iterators is correct") {
    auto first = x.begin();
    auto last = x.end();

    CHECK_UNARY(
        std::all_of(first, last, [](auto coeff) { return coeff == 4; }));
  }
}

TEST_CASE("Reduction") {

  SUBCASE("Test min and argmin") {
    const linalg::Vector x({9, 0, 5, 7, 1, 2, 3, 4, 5, 6, 7, 8, -4, 9});
    CAPTURE(x);

    auto m = linalg::min(x);
    CHECK_EQ(m, -4);

    auto i = linalg::argmin(x);
    CHECK_EQ(i, 12);

    const linalg::Vector defaulted;
    CHECK_THROWS_AS(linalg::min(defaulted), std::invalid_argument);
    CHECK_THROWS_AS(linalg::argmin(defaulted), std::invalid_argument);
  }

  SUBCASE("Test max and argmax") {
    linalg::Vector x({30, 3, 123, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    CAPTURE(x);

    auto m = linalg::max(x);
    CHECK_EQ(m, 123);

    auto i = linalg::argmax(x);
    CHECK_EQ(i, 2);

    const linalg::Vector defaulted;
    CHECK_THROWS_AS(linalg::max(defaulted), std::invalid_argument);
    CHECK_THROWS_AS(linalg::argmax(defaulted), std::invalid_argument);
  }

  SUBCASE("Test non_zeros") {
    linalg::Vector x({30, 0, 123, 0, 2, 3, 0, 0, 6, 0, 8, 9});
    CAPTURE(x);
    CHECK_EQ(linalg::non_zeros(x), 7);

    const linalg::Vector defaulted;
    CHECK_EQ(linalg::non_zeros(defaulted), 0);
  }

  SUBCASE("Test sum and prod") {
    linalg::Vector x({30, 0, 123, 0, 2, 3, 0, 0, 6, 0, 8, 9});
    CAPTURE(x);
    CHECK_EQ(linalg::sum(x), 181);
    CHECK_EQ(linalg::prod(x), 0);

    const linalg::Vector defaulted;
    CHECK_EQ(linalg::sum(defaulted), 0);
    CHECK_EQ(linalg::prod(defaulted), 1);
  }

  SUBCASE("Test sum and prod 2") {
    linalg::Vector x({3, 1, 13, 1, 2, 3, 8, 9});
    CAPTURE(x);
    CHECK_EQ(linalg::sum(x), 40);
    CHECK_EQ(linalg::prod(x), 16848);

    const linalg::Vector defaulted;
    CHECK_EQ(linalg::sum(defaulted), 0);
    CHECK_EQ(linalg::prod(defaulted), 1);
  }

  SUBCASE("Test dot 1") {
    linalg::Vector x({1, 2, 3});
    linalg::Vector y({0, 1, 0});
    CAPTURE(x);
    CAPTURE(y);

    auto dot = linalg::dot(x, y);
    CHECK_EQ(dot, 2.);
    CHECK_EQ(linalg::dot(x, y), linalg::dot(y, x));
  }

  SUBCASE("Test dot 2") {
    linalg::Vector x(
        {0.18892068, 0.82291592, 0.28046973, 0.7012888, 0.99080211});
    linalg::Vector y(
        {0.60911213, 0.65290453, 0.2242436, 0.32648942, 0.60128783});
    CAPTURE(x);
    CAPTURE(y);

    auto dot = linalg::dot(x, y);
    CHECK_EQ(dot, doctest::Approx(1.5399735709263176));
    CHECK_EQ(linalg::dot(x, y), linalg::dot(y, x));
  }

  SUBCASE("Test dot 3") {
    linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                      0.58428674, 0.89063629, 0.50002398, 0.45118024,
                      0.31165657, 0.74530963});
    linalg::Vector y({0.7733542, 0.15135689, 0.60560901, 0.13599972, 0.54029262,
                      0.06325417, 0.76008249, 0.02780873, 0.70149423,
                      0.3950426});
    CAPTURE(x);
    CAPTURE(y);

    auto dot = linalg::dot(x, y);
    CHECK_EQ(dot, doctest::Approx(2.2314149508265966));
    CHECK_EQ(linalg::dot(x, y), linalg::dot(y, x));

    CHECK_EQ(linalg::norm(linalg::normalized(x)), doctest::Approx(1));
    CHECK_EQ(linalg::norm(linalg::normalized(y)), doctest::Approx(1));
  }

  SUBCASE("Test dot 3") {
    linalg::Vector x({1, 2, 3});
    linalg::Vector y({1, 0});
    CAPTURE(x);
    CAPTURE(y);

    CHECK_THROWS_AS(linalg::dot(x, y), std::invalid_argument);
    CHECK_THROWS_AS(linalg::dot(y, x), std::invalid_argument);
  }

  SUBCASE("Test norm 1") {
    linalg::Vector x(43, 0);
    x[40] = 1;
    CAPTURE(x);

    auto norm = linalg::norm(x);
    CHECK_EQ(norm, doctest::Approx(1));

    CHECK_EQ(linalg::norm(linalg::normalized(x)), doctest::Approx(1));
  }

  SUBCASE("Test norm 2") {
    linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                      0.58428674, 0.89063629, 0.50002398, 0.45118024,
                      0.31165657, 0.74530963});
    CAPTURE(x);

    auto norm = linalg::norm(x);
    CHECK_EQ(norm, doctest::Approx(1.8988366755331416));

    CHECK_EQ(linalg::norm(linalg::normalized(x)), doctest::Approx(1));
  }
}

TEST_CASE("Transform") {
  SUBCASE("Inplace addition") {
    linalg::Vector x(14, 3);
    CAPTURE(x);
    x += 4;
    CHECK_UNARY(
        std::all_of(x.begin(), x.end(), [](auto coeff) { return coeff == 7; }));
  }
  SUBCASE("Inplace subtraction") {
    linalg::Vector x(14, 3);
    CAPTURE(x);
    x -= 1;
    CHECK_UNARY(
        std::all_of(x.begin(), x.end(), [](auto coeff) { return coeff == 2; }));
  }
  SUBCASE("Inplace multiplication") {
    linalg::Vector x(14, 3);
    CAPTURE(x);
    x *= -1;
    CHECK_UNARY(std::all_of(x.begin(), x.end(),
                            [](auto coeff) { return coeff == -3; }));
  }
  SUBCASE("Inplace division") {
    linalg::Vector x(14, 3);
    CAPTURE(x);
    x /= 3;
    CHECK_UNARY(
        std::all_of(x.begin(), x.end(), [](auto coeff) { return coeff == 1; }));
  }

  SUBCASE("Inplace addition with vector") {
    linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                      0.58428674, 0.89063629, 0.50002398, 0.45118024,
                      0.31165657, 0.74530963});
    const linalg::Vector y({0.7733542, 0.15135689, 0.60560901, 0.13599972,
                            0.54029262, 0.06325417, 0.76008249, 0.02780873,
                            0.70149423, 0.3950426});
    const linalg::Vector z({1.20613873, 0.29180371, 1.44016563, 0.81514651,
                            1.12457936, 0.95389046, 1.26010647, 0.47898897,
                            1.0131508, 1.14035223});

    CAPTURE(x);
    CAPTURE(y);
    CAPTURE(z);

    x += y;

    for (std::size_t i = 0; i < x.size(); ++i) {
      CHECK_EQ(x[i], doctest::Approx(z[i]));
    }

    linalg::Vector w(x.size() + 3, 2);
    CHECK_THROWS_AS(x += w, std::invalid_argument);
  }

  SUBCASE("Testing floor") {
    const linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                            0.58428674, 0.89063629, 0.50002398, 0.45118024,
                            0.31165657, 0.74530963});
    CAPTURE(x);

    auto floored = linalg::floor(x);
    CAPTURE(floored);
    CHECK_UNARY(std::all_of(floored.begin(), floored.end(),
                            [](auto coeff) { return coeff == 0; }));
  }

  SUBCASE("Testing ceil") {
    const linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                            0.58428674, 0.89063629, 0.50002398, 0.45118024,
                            0.31165657, 0.74530963});
    CAPTURE(x);

    auto ceiled = linalg::ceil(x);
    CAPTURE(ceiled);
    CHECK_UNARY(std::all_of(ceiled.begin(), ceiled.end(),
                            [](auto coeff) { return coeff == 1; }));
  }

  SUBCASE("Testing unary operator+") {
    const linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                            0.58428674, 0.89063629, 0.50002398, 0.45118024,
                            0.31165657, 0.74530963});
    CAPTURE(x);

    auto y = +x;
    CAPTURE(y);
    CHECK_UNARY(std::equal(y.begin(), y.end(), x.begin()));
  }

  SUBCASE("Testing unary operator-") {
    const linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                            0.58428674, 0.89063629, 0.50002398, 0.45118024,
                            0.31165657, 0.74530963});
    const linalg::Vector y({-0.43278453, -0.14044682, -0.83455662, -0.67914679,
                            -0.58428674, -0.89063629, -0.50002398, -0.45118024,
                            -0.31165657, -0.74530963});
    CAPTURE(x);

    auto z = -x;
    CAPTURE(z);
    CHECK_UNARY(std::equal(y.begin(), y.end(), z.begin()));
  }

  SUBCASE("Testing binary operator+") {
    const linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                            0.58428674, 0.89063629, 0.50002398, 0.45118024,
                            0.31165657, 0.74530963});
    const linalg::Vector y({-0.43278453, -0.14044682, -0.83455662, -0.67914679,
                            -0.58428674, -0.89063629, -0.50002398, -0.45118024,
                            -0.31165657, -0.74530963});
    CAPTURE(x);

    auto z = x + y;
    CAPTURE(z);
    for (std::size_t i = 0; i < x.size(); ++i) {
      INFO("At position: ", i);
      CHECK_EQ(z[i], x[i] + y[i]);
    }
  }

  SUBCASE("Testing binary operator-") {
    const linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                            0.58428674, 0.89063629, 0.50002398, 0.45118024,
                            0.31165657, 0.74530963});
    const linalg::Vector y({-0.43278453, -0.14044682, -0.83455662, -0.67914679,
                            -0.58428674, -0.89063629, -0.50002398, -0.45118024,
                            -0.31165657, -0.74530963});
    CAPTURE(x);

    auto z = x - y;
    CAPTURE(z);
    for (std::size_t i = 0; i < x.size(); ++i) {
      INFO("At position: ", i);
      CHECK_EQ(z[i], x[i] - y[i]);
    }
  }

  SUBCASE("Testing binary operator+ with scalar") {
    const linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                            0.58428674, 0.89063629, 0.50002398, 0.45118024,
                            0.31165657, 0.74530963});
    CAPTURE(x);

    auto y = x + 42.;
    CAPTURE(y);
    for (std::size_t i = 0; i < x.size(); ++i) {
      INFO("At position: ", i);
      CHECK_EQ(y[i], x[i] + 42.f);
    }

    auto z = 42.f + x;
    CAPTURE(z);
    CHECK_UNARY(std::equal(y.begin(), y.end(), z.begin()));
  }

  SUBCASE("Testing binary operator- with scalar") {
    const linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                            0.58428674, 0.89063629, 0.50002398, 0.45118024,
                            0.31165657, 0.74530963});
    CAPTURE(x);

    auto y = x - 42.;
    CAPTURE(y);
    for (std::size_t i = 0; i < x.size(); ++i) {
      INFO("At position: ", i);
      CHECK_EQ(y[i], x[i] - 42.f);
    }

    auto z = 42.f - x;
    CAPTURE(z);
    for (std::size_t i = 0; i < x.size(); ++i) {
      INFO("At position: ", i);
      CHECK_EQ(z[i], 42.f - x[i]);
    }
  }

  SUBCASE("Testing binary operator* with scalar") {
    const linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                            0.58428674, 0.89063629, 0.50002398, 0.45118024,
                            0.31165657, 0.74530963});
    CAPTURE(x);

    auto y = x * 42.f;
    CAPTURE(y);
    for (std::size_t i = 0; i < x.size(); ++i) {
      INFO("At position: ", i);
      CHECK_EQ(y[i], x[i] * 42.f);
    }

    auto z = 42.f * x;
    CAPTURE(z);
    CHECK_UNARY(std::equal(y.begin(), y.end(), z.begin()));
  }

  SUBCASE("Testing binary operator/ with scalar") {
    const linalg::Vector x({0.43278453, 0.14044682, 0.83455662, 0.67914679,
                            0.58428674, 0.89063629, 0.50002398, 0.45118024,
                            0.31165657, 0.74530963});
    CAPTURE(x);

    auto y = x / 2.f;
    CAPTURE(y);
    for (std::size_t i = 0; i < x.size(); ++i) {
      INFO("At position: ", i);
      CHECK_EQ(y[i], x[i] / 2.f);
    }
  }
}
