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

#include <iterator>
#include <sstream>


#include "hw03.h"

// require at least c++20
static_assert(__cplusplus >= 202002L);


void fill_contacts(contact_list::storage &s) {
    contact_list::add(s, "A", 10);
    contact_list::add(s, "C", 12);
    contact_list::add(s, "D", 14);
    contact_list::add(s, "F", 11);
    contact_list::add(s, "B", 13);
    contact_list::add(s, "Z", 19);
    contact_list::add(s, "J", 42);
}


// test duplicate name, duplicate number


TEST_CASE("contact_number") {
    contact_list::storage s;
    CHECK_EQ(contact_list::size(s), 0);

    fill_contacts(s);
    CHECK_EQ(contact_list::size(s), 7);
    CHECK_EQ(contact_list::get_number_by_name(s, "A"), 10);
    CHECK_EQ(contact_list::get_number_by_name(s, "C"), 12);
    CHECK_EQ(contact_list::get_number_by_name(s, "B"), 13);
    CHECK_EQ(contact_list::get_number_by_name(s, "D"), 14);
    CHECK_EQ(contact_list::get_number_by_name(s, "F"), 11);
    CHECK_EQ(contact_list::get_number_by_name(s, "J"), 42);
    CHECK_EQ(contact_list::get_number_by_name(s, "Z"), 19);

    CHECK_EQ(contact_list::get_number_by_name(s, "X"), -1);
    CHECK_EQ(contact_list::get_number_by_name(s, "XXX"), -1);
}


TEST_CASE("contact_name") {
    contact_list::storage s;
    fill_contacts(s);
    CHECK_EQ(contact_list::get_name_by_number(s, 19), "Z");
    CHECK_EQ(contact_list::get_name_by_number(s, 12), "C");
    CHECK_EQ(contact_list::get_name_by_number(s, 14), "D");
    CHECK_EQ(contact_list::get_name_by_number(s, 42), "J");
    CHECK_EQ(contact_list::get_name_by_number(s, 10), "A");
    CHECK_EQ(contact_list::get_name_by_number(s, 13), "B");
    CHECK_EQ(contact_list::get_name_by_number(s, 11), "F");

    CHECK_EQ(contact_list::get_name_by_number(s, 54), "");
    CHECK_EQ(contact_list::get_name_by_number(s, 9), "");
    CHECK_EQ(contact_list::get_name_by_number(s, 15), "");
}


TEST_CASE("add_contact") {
    contact_list::storage s;
    fill_contacts(s);
    CHECK_EQ(contact_list::size(s), 7);

    // add new contact
    CHECK_EQ(contact_list::add(s, "X", 1337), true);
    CHECK_EQ(contact_list::size(s), 8);
    CHECK_EQ(contact_list::get_number_by_name(s, "X"), 1337);
    CHECK_EQ(contact_list::get_number_by_name(s, "A"), 10);

    // should return false and not add the contact again
    CHECK_EQ(contact_list::add(s, "X", 1337), false);
    CHECK_EQ(contact_list::size(s), 8);

    // empty name disallowed
    CHECK_EQ(contact_list::add(s, "", 1337), false);
    CHECK_EQ(contact_list::size(s), 8);
}


TEST_CASE("remove_contact") {
    contact_list::storage s;
    CHECK_EQ(contact_list::add(s, "L", 123), true);
    CHECK_EQ(contact_list::get_number_by_name(s, "L"), 123);
    CHECK_EQ(contact_list::size(s), 1);

    // test removal, and removing again
    CHECK_EQ(contact_list::remove(s, "L"), true);
    CHECK_EQ(contact_list::size(s), 0);
    CHECK_EQ(contact_list::get_number_by_name(s, "L"), -1);
    CHECK_EQ(contact_list::remove(s, "L"), false);
    CHECK_EQ(contact_list::size(s), 0);
}


template<typename ret_t>
void split(const std::string &txt, char delimiter, ret_t result) {
    std::stringstream splitter;
    splitter.str(txt);
    std::string part;

    while (std::getline(splitter, part, delimiter)) {
        *result = part;
        result++;
    }
}


std::vector<std::string> split(const std::string &txt, char delimiter) {
    std::vector<std::string> items;
    // use the back inserter iterator and the templated split function.
    split(txt, delimiter, std::back_inserter(items));
    return items;
}


std::string strip(const std::string& inpt) {
    auto start_it = std::begin(inpt);
    auto end_it = std::rbegin(inpt);
    while (std::isspace(*start_it))
        ++start_it;
    while (std::isspace(*end_it))
        ++end_it;
    return std::string(start_it, end_it.base());
}


auto test_formatting(const contact_list::storage &s, auto &expected_numbers) {
    std::string contact_list = contact_list::to_string(s);
    std::vector<std::string> lines = split(contact_list, '\n');
    CHECK_EQ(lines.size(), expected_numbers.size());

    for (size_t i = 0; i < lines.size(); i++) {
        std::vector<std::string> lineparts = split(lines[i], '-');
        CHECK_EQ(lineparts.size(), 2);  // "name - number" -> split at -

        // check if the name (first) and number (second) are correct
        std::string name = strip(lineparts[0]);
        CHECK_EQ(name, expected_numbers[i].first);

        int number = std::stoi(lineparts[1]);
        CHECK_EQ(number, expected_numbers[i].second);
    }
};


TEST_CASE("sort_contacts") {
    contact_list::storage s;

    fill_contacts(s);

    std::vector<std::pair<std::string, int>> nrs = {
        {"A", 10},
        {"C", 12},
        {"D", 14},
        {"F", 11},
        {"B", 13},
        {"Z", 19},
        {"J", 42},
    };

    // check if the to_string output is correct before sorting
    test_formatting(s, nrs);

    // sort the list by name
    REQUIRE_NOTHROW(contact_list::sort(s));

    std::vector<std::pair<std::string, int>> nrs_sorted = {
        {"A", 10},
        {"B", 13},
        {"C", 12},
        {"D", 14},
        {"F", 11},
        {"J", 42},
        {"Z", 19},
    };

    // check if the to_string output is correct after sorting
    test_formatting(s, nrs_sorted);

    // insert a new contact after sorting
    CHECK_EQ(contact_list::add(s, "E", 15), true);
    CHECK_EQ(contact_list::get_number_by_name(s, "E"), 15);
    CHECK_EQ(contact_list::get_name_by_number(s, 15), "E");
    nrs_sorted.insert(std::begin(nrs_sorted) + 4, {"E", 15});

    // sort again, see if the new contact is now at the correct position
    REQUIRE_NOTHROW(contact_list::sort(s));
    CHECK_EQ(contact_list::get_number_by_name(s, "E"), 15);

    test_formatting(s, nrs_sorted);
}
