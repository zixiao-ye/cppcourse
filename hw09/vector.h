#pragma once

#include <memory>
#include <ostream>
#include <stdexcept>

template <typename T>
class Vector {
public:
    Vector() = default;

    /**
     * Creates a vector of size n with values default_val.
     */
    Vector(size_t n, const T& default_val) {
    }

    /**
     * Creates a vector containing the elements in l.
     */
    Vector(std::initializer_list<T> l) {
    }

    Vector(const Vector& copy) : _size(copy._size), _capacity(copy._capacity) {
    }

    Vector(Vector&& move) : _size(move._size), _capacity(move._capacity) {
    }

    /**
     * Replaces the contents of the vector.
     */
    Vector& operator=(const Vector& copy) {
    }


    /**
     * Replaces the contents of the vector.
     */
    Vector& operator=(Vector&& move) noexcept {
    }

    size_t size() const noexcept { return _size; }

    size_t capacity() const noexcept { return _capacity; }

    /**
     * Appends the given element value to the end of the vector.
     */
    void push_back(const T& value) {
    }

    /**
     * Appends the given element value to the end of the vector.
     */
    void push_back(T&& value) {
    }

    /**
     * Removes the last element of the vector.
     */
    void pop_back() {
    }

    /**
     * Returns a reference to the element at specified location pos, with bounds checking.
     * If pos is not within the range of the vector, an exception of type std::out_of_range is thrown.
     */
    T& at(const size_t pos) const {
    }

    /**
     * Returns a reference to the element at specified location pos, with bounds checking.
     * If pos is not within the range of the vector, an exception of type std::out_of_range is thrown.
     */
    T& at(const size_t pos) {
    }

    /**
     * Returns a reference to the element at specified location pos.
     * No bounds checking is performed.
     */
    T& operator[](const size_t index) const {
    }

    /**
     * Returns a reference to the element at specified location pos.
     * No bounds checking is performed.
     */
    T& operator[](const size_t index) {
    }

    friend std::ostream& operator<<(std::ostream& o, Vector<T> v) {
        o << "Size: " << v._size << ", Capacity: " << v._capacity << std::endl;
        for (size_t i = 0; i < v._size; ++i) {
            if (i > 0)
                o << ", ";
            o << v._data[i];
        }
        o << std::endl;
        return o;
    }

    ~Vector() = default;

private:
    // Defines how the `_capacity` is increased.
    size_t growth_factor = 2;
    size_t _size;
    size_t _capacity;

    // Holds vector's data.
    std::unique_ptr<T[]> _data;

    /**
     * Calculates the necessary capacity for new_size.
     * If necessary, double `_capacity` using `growth_factor`.
     */
    size_t calculate_capacity(size_t new_size) {
    }

    /**
    * Resizes the vector to new_capacity.
    * If the current capacity is less than new_capacity
    * the vector moves all elements to a new array.
    */
    void resize(size_t new_capacity) {
    }
};
