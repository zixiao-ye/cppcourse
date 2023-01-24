#pragma once
#include <concepts>

template <int N, std::integral T = int>
struct fibonacci {
    static constexpr T value = fibonacci<N-1>::value + fibonacci<N-2>::value;
};

template<>
struct fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct fibonacci<1> {
    static constexpr int value = 1;
};

