#include <iostream>
#include <string>

#include "hw10.h"


int main() {
    // Exercise 1
    std::cout << fibonacci<30>::value << std::endl;

    // Not an integral type.
    // std::cout << fibonacci<4, double>::value << std::endl;

    // Also possible..
    std::cout << fibonacci<11, char>::value << std::endl;

    // Exercise 2
    auto quad = Quadruple<int, int, int, int>(1, 2, 3, 4);
    std::cout << quad.get_first() << ", "
              << quad.get_second() << ", "
              << quad.get_third() << ", "
              << quad.get_fourth() << ", " << std::endl;

    auto string_quad = Quadruple<std::string, std::string,
                                 std::string, std::string>("abc", "def", "ghi", "...");
    std::cout << string_quad.get_first() << ", "
              << string_quad.get_second() << ", "
              << string_quad.get_third() << ", "
              << string_quad.get_fourth() << ", " << std::endl;

    auto mixed_quad = Quadruple<std::string, int,
                                char, bool>("abc", 42, '\n', 0);
    std::cout << mixed_quad.get_first() << ", "
              << mixed_quad.get_second() << ", "
              << mixed_quad.get_third() << ", "
              << mixed_quad.get_fourth() << ", " << std::endl;

    // Exercise 3
    std::cout << gcd(1345, 7) << std::endl
              << gcd(4004, 102) << std::endl
              << gcd(2, 4, 6, 8, 10) << std::endl;

    // Exercise 4
    std::cout << mcm(1345, 7) << std::endl
              << mcm(4004, 102) << std::endl
              << mcm(2, 4, 6, 8, 10) << std::endl;

    // Exercise 5
    std::cout << "10^0 mod 3 = "
              << Power<10, 0, 3>::value << std::endl;
    std::cout << "1^0 mod 3 = "
              << Power<1, 0, 3>::value << std::endl;
    std::cout << "5^3 mod 13 = "
              << Power<5, 3, 13>::value << std::endl;
    std::cout << "4^13 mod 497 = "
              << Power<4, 13, 497>::value << std::endl;

    return 0;
}
