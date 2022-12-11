#include "vector.h"

#include <iterator>
#include<numeric>
#include<cmath>
#include<iostream>


namespace linalg {
Vector::Vector(std::size_t n){
    data_.resize(n);
}

Vector::Vector(std::size_t n, float val){
    data_ = std::vector<float>(n, val);
}

Vector::Vector(std::initializer_list<float> list){
    data_ = list;
}

auto Vector::operator=(float val) -> Vector &{
    std::fill(data_.begin(), data_.end(), val);
    return *this;
}

auto Vector::assign(float val) -> void{
    std::fill(data_.begin(), data_.end(), val);
}

auto Vector::assign(Vector v) -> void{
    data_.assign(v.begin(),v.end());
}

auto Vector::size() const -> std::size_t{
    return data_.size();
}

auto Vector::begin() -> iterator{
    return data_.begin();
}

auto Vector::end() -> iterator{
    return data_.end();
}

auto Vector::begin() const -> const_iterator{
    return data_.begin(); 
}

auto Vector::end() const -> const_iterator{
    return data_.end();
}

auto Vector::cbegin() const -> const_iterator{
    return data_.cbegin();
}

auto Vector::cend() const -> const_iterator{
    return data_.cend();
}

auto Vector::operator[](int idx) -> float &{
    size_t i = size_t(idx);
    if (idx < 0)
    {
        i = size_t(int(data_.size()) + idx);
    }
    if (i >= data_.size())
    {
        throw std::out_of_range("Out of range!");
    }
    return data_[i];
}

auto Vector::operator[](int idx) const -> const float &{
    size_t i = size_t(idx);
    if (idx < 0)
    {
        i = size_t(int(data_.size()) + idx);
    }
    if (i >= data_.size())
    {
        throw std::out_of_range("Out of range!");
    }
    return data_[i];
}

auto Vector::coeff(int idx) -> float &{
    size_t i = size_t(idx);
    if (idx<0 || i >= data_.size())
    {
        throw std::out_of_range("Out of range!");
    }
    return data_[i];
}

auto Vector::coeff(int idx) const -> const float &{
    size_t i = size_t(idx);
    if (idx<0 || i >= data_.size())
    {
        throw std::out_of_range("Out of range!");
    }
    return data_[i];
}

auto Vector::operator+=(float val) -> Vector &{
    std::for_each(data_.begin(), data_.end(), [val](float &x) {x+=val;});
    return *this;
}

auto Vector::operator-=(float val) -> Vector &{
    std::for_each(data_.begin(), data_.end(), [val](float &x) {x-=val;});
    return *this;
}

auto Vector::operator*=(float val) -> Vector &{
    std::for_each(data_.begin(), data_.end(), [val](float &x) {x*=val;});
    return *this;
}

auto Vector::operator/=(float val) -> Vector &{
    std::for_each(data_.begin(), data_.end(), [val](float &x) {x/=val;});
    return *this;
}

auto Vector::operator+=(const Vector &y) -> Vector &{
    if (data_.size() != y.size())
    {
        throw std::invalid_argument("Invalid argument!");
    }
    std::transform(data_.begin(), data_.end(), y.begin(), data_.begin(), std::plus<float>());
    return *this;
}

auto Vector::operator-=(const Vector &y) -> Vector &{
    if (data_.size() != y.size())
    {
        throw std::invalid_argument("Invalid argument!");
    }
    std::transform(data_.begin(), data_.end(), y.begin(), data_.begin(), std::minus<float>());
    return *this;
}




auto operator<<(std::ostream& ostr, const Vector& x) -> std::ostream& {
    ostr << "[ ";
    std::copy(x.begin(), x.end(), std::ostream_iterator<float>(ostr, " "));
    ostr << "]";
    return ostr;
}

auto min(const Vector &x) -> float{
    if (x.size() == 0)
    {
        throw std::invalid_argument("Invalid argument!");
    }
    return *std::min_element(x.begin(), x.end());
}

auto max(const Vector &x) -> float{
    if (x.size() == 0)
    {
        throw std::invalid_argument("Invalid argument!");
    }
    return *std::max_element(x.begin(), x.end());
}

auto argmin(const Vector &x) -> std::size_t{
    if (x.size() == 0)
    {
        throw std::invalid_argument("Invalid argument!");
    }
    return size_t(std::min_element(x.begin(), x.end())-x.begin());
}

auto argmax(const Vector &x) -> std::size_t{
    if (x.size() == 0)
    {
        throw std::invalid_argument("Invalid argument!");
    }
    return size_t(std::max_element(x.begin(), x.end())-x.begin());
}

auto non_zeros(const Vector &x) -> std::size_t{
    size_t zeros = size_t(std::count(x.begin(), x.end(), 0));
    return size_t(x.size() - zeros);
}

auto sum(const Vector &x) -> float{
    return std::accumulate(x.begin(), x.end(), 0);
}

auto prod(const Vector &x) -> float{
    return std::accumulate(x.begin(), x.end(), 1, std::multiplies<float>());
}

auto dot(const Vector &x, const Vector &y) -> float{
    if (x.size() != y.size())
    {
        throw std::invalid_argument("Invalid argument!");
    }
    return float(std::inner_product(x.begin(), x.end(), y.begin(), 0.0));
}

auto norm(const Vector &x) -> float{
    return sqrt(dot(x,x));
}

auto normalize(Vector &x) -> void{
    x /= norm(x);
}

/// Return a normalized copy of the vector
auto normalized(const Vector &x) -> Vector{
    Vector y = x;
    normalize(y);
    return y;
}

auto floor(const Vector &x) -> Vector{
    Vector y = x;
    std::transform(y.begin(), y.end(), y.begin(), [](float num){return std::floor(num);});
    return y;
}

auto ceil(const Vector &x) -> Vector{
    Vector y = x;
    std::transform(y.begin(), y.end(), y.begin(), [](float num){return std::ceil(num);});
    return y;
}

auto operator+(const Vector &x) -> Vector{
    Vector y = x;
    return y;
}

auto operator-(const Vector &x) -> Vector{
    Vector y = x;
    std::transform(y.begin(), y.end(), y.begin(), [](float num){return -num;});
    return y;
}

auto operator+(const Vector &x, const Vector &y) -> Vector{
    Vector v = x;
    v += y;
    return v;
}

auto operator-(const Vector &x, const Vector &y) -> Vector{
    Vector v = x;
    v -= y;
    return v;
}

auto operator+(const Vector &x, float val) -> Vector{
    Vector y = x;
    y += val;
    return y;
}

auto operator-(const Vector &x, float val) -> Vector{
    Vector y = x;
    y -= val;
    return y;
}

auto operator*(const Vector &x, float val) -> Vector{
    Vector y = x;
    y *= val;
    return y;
}

auto operator/(const Vector &x, float val) -> Vector{
    Vector y = x;
    y /= val;
    return y;
}

auto operator+(float val, const Vector &x) -> Vector{
    Vector y = x;
    y += val;
    return y;
}

auto operator-(float val, const Vector &x) -> Vector{
    Vector z(x.size(), val);
    z -= x;
    return z;
}

auto operator*(float val, const Vector &x) -> Vector{
    Vector y = x;
    y *= val;
    return y;
}

}

