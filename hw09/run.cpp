#include <iostream>
#include "hw09.h"


int main() {
    size_t count{14};
    Vector<int> v(count, 2);
    std::cout << v << std::endl;
    v.push_back(3);
    int item{4};
    v.push_back(std::move(item));
    std::cout << v << std::endl;
    v.pop_back();
    std::cout << v << std::endl;

    for (int i{0}; i < 25; ++i)
        v.push_back(i);
    std::cout << v << std::endl;

    Vector<int> v1 = v;

    for (int i = 0; i < 10; ++i) {
        v.pop_back();
        std::cout << "Popped " << v[v.size() - 1] << std::endl;
    }
    std::cout << v << std::endl;
    std::cout << "Starting element: " << v.at(0) << std::endl;
    std::cout << "Ending element: " << v.at(v.size() - 1) << std::endl;

    std::cout << v1 << std::endl;

    std::cout << "Starting element: " << v1.at(0) << std::endl;
    std::cout << "Ending element: " << v1.at(v1.size() - 1) << std::endl;

    Vector<char> v2(20, 'a');
    std::cout << v2 << std::endl;

    for (int i=0; i < 12; ++i)
        ++v2[i];
    std::cout << v2 << std::endl;
    std::cout << "Starting element: " << v2.at(0) << std::endl;
    std::cout << "Ending element: " << v2.at(v2.size() - 1) << std::endl;

    Vector<std::string> v3 {"Best Editors", "Emacs", "Emacs", "Emacs", "emacs"};
    std::cout << v3 << std::endl;

    return 0;
}
