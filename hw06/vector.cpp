#include "vector.h"

#include <iterator>


namespace linalg {
auto operator<<(std::ostream& ostr, const Vector& x) -> std::ostream& {
    ostr << "[ ";
    std::copy(x.begin(), x.end(), std::ostream_iterator<float>(ostr, " "));
    ostr << "]";
    return ostr;
}
}

/*
 * Please Implement all functions from the header file here!#
 * Have fun! :-) And don't forget maybe you can use standard algorithms ;-)
 */
