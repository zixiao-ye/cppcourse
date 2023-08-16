#include <iostream>

#include "hw11.h"

int main() {
    // test compiletime map at runtime
    auto map = create_cexpr_map<int, int>(
        std::make_pair(0, 42),
        std::make_pair(13, 37));

    if (map.size() != 2) {
        std::cout << "map size not yet working :)" << std::endl;
    }
    std::cout << "Size: " << map.size() << std::endl;
    if (map.contains(13) != true) {
        std::cout << "map membership not yet working :)" << std::endl;
    }
    if (map.get(13) != 37) {
        std::cout << "map value fetching not yet working :)" << std::endl;
    }
    std::cout << "map[13]: " << map.get(13) << std::endl;

    return 0;
}
