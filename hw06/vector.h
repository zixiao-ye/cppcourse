#include <functional>
#include <initializer_list>
#include <ostream>
#include <utility>
#include <vector>

namespace linalg {

/// A linear algebra like vector. This class should behave similarly to a vector
/// like used in math. Plus some things we need to code with it
class Vector {
public:
  /// These are so called associated types. They are associated with my vector.
  using iterator = std::vector<float>::iterator;
  using const_iterator = std::vector<float>::const_iterator;

  /// Default constructor
  Vector() = default;

  /// Construct non-initialized vector with given size
  explicit Vector(std::size_t n);

  /// Construct vector with given size and initialized with the given value
  Vector(std::size_t n, float val);

  /// Construct vector with initialize list
  explicit Vector(std::initializer_list<float> list);

  /// Assign the given value to the vector, all coefficients in the vector are
  /// then equal to `val`
  auto operator=(float val) -> Vector &;

  /// Assign a value to the vector, all coefficients in the vector are then
  /// equal to `val`
  auto assign(float val) -> void;

  /// Assign `v` to this vector. The size and all coefficients are then equal to
  /// the coefficients of `v`.
  auto assign(Vector v) -> void;

  /// Return the size of the vector
  auto size() const -> std::size_t;

  /// Return an begin iterator to the vector
  auto begin() -> iterator;

  /// Return an end iterator to the vector
  auto end() -> iterator;

  /// Return an begin const_iterator to the vector
  auto begin() const -> const_iterator;

  /// Return an end const_iterator to the vector
  auto end() const -> const_iterator;

  /// Return an begin const_iterator to the vector
  auto cbegin() const -> const_iterator;

  /// Return an end const_iterator to the vector
  auto cend() const -> const_iterator;

  /// Access a modifiable reference to the idx-th element of the vector.#
  ///
  /// Additionally a python like behaviour access of negative indices should be
  /// possible. I.e. `vec[-1]` should return the last value in the vector It
  /// should only be wrapped once. I.e. given a vector of length 10, `vec[-15]`
  /// does not need to be supported. Also note that accessing values above the
  /// size of the vector is also undefined.
  auto operator[](int idx) -> float &;

  /// Access a non-modifiable reference to the idx-th element of the vector.
  ///
  /// Additionally a python like behaviour access of negative indices should be
  /// possible. I.e. `vec[-1]` should return the last value in the vector. It
  /// should only be wrapped once. I.e. given a vector of length 10, `vec[-15]`
  /// does not need to be supported. Also note that accessing values above the
  /// size of the vector is also undefined.
  auto operator[](int idx) const -> const float &;

  /// Access a modifiable reference to the idx-th element of the vector. No
  /// wrapping behaviour should be implemented.
  ///
  /// Throw an `std::out_of_range` exception if the index out of bounds.
  auto coeff(int idx) -> float &;

  /// Access a non-modifiable reference to the idx-th element of the vector. No
  /// wrapping behaviour should be implemented.
  ///
  /// Throw an `std::out_of_range` exception if the index out of bounds.
  auto coeff(int idx) const -> const float &;

  /* In place operators, modify the given Vector in-place, rather than a copy */

  /// Add a scalar value to the vector, i.e. for each coefficient `v_i` of the
  /// vector, the values after this operators are `v_i + val`
  auto operator+=(float val) -> Vector &;

  /// Subtract a scalar value from the vector, i.e. for each coefficient `v_i`
  /// of the vector, the values after this operators are `v_i - val`
  auto operator-=(float val) -> Vector &;

  /// Multiply vector with a scalar, i.e. for each coefficient `v_i`
  /// of the vector, the values after this operators are `v_i * val`
  auto operator*=(float val) -> Vector &;

  /// Divide vector by a scalar, i.e. for each coefficient `v_i`
  /// of the vector, the values after this operators are `v_i / val`
  auto operator/=(float val) -> Vector &;

  /// In-place addition of two vectors, given the coefficients `x_i` and `y_i`
  /// of the vectors respectively, a new vector is returned, where the
  /// coefficients are equal to `x_i` + `y_i`
  ///
  /// Throw an `std::invalid_argument` exceptions, if the given vector is of a
  /// different size
  auto operator+=(const Vector &y) -> Vector &;

  /// In-place addition of two vectors, given the coefficients `x_i` and `y_i`
  /// of the vectors respectively, a new vector is returned, where the
  /// coefficients are equal to `x_i` - `y_i`
  ///
  /// Throw an `std::invalid_argument` exceptions, if the given vector is of a
  /// different size
  auto operator-=(const Vector &y) -> Vector &;

private:
  std::vector<float> data_;
};

/// This will pretty print a vector for you by e.g. `std::cout << x << "\n";`
auto operator<<(std::ostream &ostr, const Vector &x) -> std::ostream &;

/// Return the minimum value of Vector
///
/// Throw an `std::invalid_argument` exceptions, if the given vector is of a
/// different size
auto min(const Vector &x) -> float;

/// Return the maximum value of Vector
///
/// Throw an `std::invalid_argument` exceptions, if the given vector is of a
/// different size
auto max(const Vector &x) -> float;

/// Return the index into the vector of the minimum value of Vector
///
/// Throw an `std::invalid_argument` exceptions, if the given vector is of a
/// different size
auto argmin(const Vector &x) -> std::size_t;

/// Return the index into the vector of the maximum value of Vector
///
/// Throw an `std::invalid_argument` exceptions, if the given vector is of a
/// different size
auto argmax(const Vector &x) -> std::size_t;

/// Return the number of non-zero elements in the vector
auto non_zeros(const Vector &x) -> std::size_t;

/// Return the sum of the coefficients of the given vector
auto sum(const Vector &x) -> float;

/// Return the product of the coefficients of the given vector
auto prod(const Vector &x) -> float;

/// Return the dot product of the two vectors. i.e. the sum of products of the
/// coefficients: `sum(x_i * y_i) forall i in [0, x.size())`
///
/// Throw an `std::invalid_argument` exceptions, if the given vector is of a
/// different size
auto dot(const Vector &x, const Vector &y) -> float;

/// Return the euclidean norm of the vector. i.e. the sum of the square of the
/// coefficients: `sum(x_i * x_i) forall i in [0, x.size())`
auto norm(const Vector &x) -> float;

/// Normalize the vector, i.e. the norm should be 1 after the normalization
auto normalize(Vector &x) -> void;

/// Return a normalized copy of the vector
auto normalized(const Vector &x) -> Vector;

/// Return a copy for which every coefficient is the floored, i.e. `v_i =
/// floor(x_i)`
auto floor(const Vector &x) -> Vector;

/// Return a copy for which every coefficient is the ceiled, i.e. `v_i =
/// ceil(x_i)`
auto ceil(const Vector &x) -> Vector;

/// Unary operator+, returns a copy of x
auto operator+(const Vector &x) -> Vector;

/// Unary operator-, returns a copy of x, where all values are negated , i.e.
/// `v_i = -x_i`
auto operator-(const Vector &x) -> Vector;

/// Return a vector, for which every coefficient is the sum of the coefficients
/// of the arguments
auto operator+(const Vector &x, const Vector &y) -> Vector;

/// Return a vector, for which every coefficient is the subtraction of the
/// coefficients of the arguments
auto operator-(const Vector &x, const Vector &y) -> Vector;

/// Return a vector, which is the addition of each coefficient of the given
/// vector and the scalar
auto operator+(const Vector &x, float val) -> Vector;

/// Return a vector, which is the subtraction of each coefficient of the given
/// vector and the scalar
auto operator-(const Vector &x, float val) -> Vector;

/// Return a vector, which is the multiplication of each coefficient of the
/// given vector and the scalar
auto operator*(const Vector &x, float val) -> Vector;

/// Return a vector, which is the division of each coefficient of the given
/// vector and the scalar
auto operator/(const Vector &x, float val) -> Vector;

/// Return a vector, which is the addition of each coefficient of the given
/// vector and the scalar
auto operator+(float val, const Vector &x) -> Vector;

/// Return a vector, which is the subtraction of each coefficient of the given
/// vector and the scalar
auto operator-(float val, const Vector &x) -> Vector;

/// Return a vector, which is the multiplication of each coefficient of the
/// given vector and the scalar
auto operator*(float val, const Vector &x) -> Vector;
} // namespace linalg
