#include "contact_list.h"
#include "hw03.h"

#include <iostream>

namespace contact_list {

void test_contact_list() {
    storage abook;
    //add(abook, "Best Friend", 421234);
    //add(abook, "False Friend", 10032331);


    add(abook, "A", 10);
    add(abook, "C", 12);
    add(abook, "D", 14);
    add(abook, "F", 11);
    add(abook, "B", 13);
    add(abook, "Z", 19);
    add(abook, "J", 42);


    add(abook, "A", 10);



    sort(abook);

    std::cout << to_string(abook);
}

} // namespace contact_list


int main() {
    contact_list::test_contact_list();

    return 0;
}
