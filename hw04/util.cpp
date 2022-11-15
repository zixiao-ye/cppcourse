#include "util.h"


namespace vm::util {


std::vector<std::string> split(std::string_view txt, char delimiter) {
    std::vector<std::string> items;
    // fill the splitted string into the result vector at the back.
    detail::split_fill(txt, delimiter, std::back_inserter(items));
    return items;
}


std::string strip(std::string_view inpt) {
    auto start_it = std::begin(inpt);
    auto end_it = std::rbegin(inpt);
    while (std::isspace(*start_it))
        ++start_it;
    while (std::isspace(*end_it))
        ++end_it;
    return std::string(start_it, end_it.base());
}


} // namespace vm::util
