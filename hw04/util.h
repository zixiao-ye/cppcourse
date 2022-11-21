#pragma once

#include <sstream>
#include <string>
#include <vector>


namespace vm::util {

/**
 * split a string at a given delimiter
 */
std::vector<std::string> split(std::string_view txt, char delimiter);


/**
 * return the whitespace-stripped version of the input string.
 */
std::string strip(std::string_view inpt);



/** implementation details that may unsettle innocent homework solvers */
namespace detail {

/**
 * cuts a string at given delimiter, storing the result in any iterable target storage.
 */
template<typename ret_t>
void split_fill(std::string_view txt, char delimiter, ret_t result) {
    std::stringstream splitter;
    splitter.str(std::string{txt});
    std::string part;

    while (std::getline(splitter, part, delimiter)) {
        *result = part;
        result++;
    }
}

} // namespace detail



} // namespace vm::util
