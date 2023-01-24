#pragma once

#include <cmath>
#include <numeric>

template <typename T>
static constexpr T gcd(T a, T b){
    return std::gcd(a,b);
}

template <typename Head, typename... Tail>
static constexpr Head gcd(Head head, Tail... tail){
    return gcd(head, gcd(tail...));
}

template <typename T>
static constexpr int mcm(T a, T b){
    return (a * b)/gcd(a,b);
}

template <typename Head, typename... Tail>
static constexpr Head mcm(Head head, Tail... tail){
    return mcm(head, mcm(tail...));
}

template<int base, int exponent, int modulus>
class pow1 {
public:
    static int constexpr value(){
        return base * (pow1<base, exponent-1, modulus>::value() % modulus);
    }
};

template<int base, int modulus>
class pow1<base, 0, modulus> {
public:
    static int constexpr value(){
        return 1;
    }
};


template<int num, int modulus>
struct fmod1 {
    static constexpr int value = num % modulus;
};

template<int base, int exponent, int modulus>
struct Power {
    static constexpr int value = fmod1<pow1<base, exponent, modulus>::value(), modulus>::value;
};