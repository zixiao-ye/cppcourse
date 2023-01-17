#pragma once

#include <memory>
#include <ostream>
#include <stdexcept>
#include<iostream>

template <typename T>
class Vector {
public:
    Vector() : _size(0), _capacity(0){};

    /**
     * Creates a vector of size n with values default_val.
     */
    Vector(size_t n, const T& default_val) {
        _size = n;
        _capacity = n;
        _data = std::make_unique<T[]>(n);
        for (size_t i = 0; i < n; i++)
        {
            _data[i] = default_val;
        }  
    }

    /**
     * Creates a vector containing the elements in l.
     */
    Vector(std::initializer_list<T> l) {
        _size = l.size();
        _capacity = l.size();
        _data = std::make_unique<T[]>(l.size());
        for (size_t i = 0; i < l.size(); i++)
        {
            _data[i] = l.begin()[i];
        }
    }

    Vector(const Vector& copy) : _size(copy._size), _capacity(copy._capacity) {
        _data = std::make_unique<T[]>(_size);
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] = copy._data[i];
        } 
    }

    Vector(Vector&& move) : _size(move._size), _capacity(move._capacity), _data{std::move(move._data)} {
        move._size = 0;
        move._capacity = 0;
    }

    /**
     * Replaces the contents of the vector.
     */
    Vector& operator=(const Vector& copy) {
        if (this == &copy)
            return *this;
        if (_capacity != copy._capacity)
        {   
            _capacity = copy._capacity;
            _size = copy._size;
            _data = std::make_unique<T[]>(_capacity);
        }
        std::copy(copy._data.get(), copy._data.get() + copy._size, _data.get());
        return *this;
    }


    /**
     * Replaces the contents of the vector.
     */
    Vector& operator=(Vector&& move) noexcept {
        if (this == &move)
            return *this;
        _capacity = move._capacity;
        _size = move._size;
        _data = std::move(move._data);

        move._capacity = 0;
        move._size = 0;
        return *this;
    }

    size_t size() const noexcept { return _size; }

    size_t capacity() const noexcept { return _capacity; }

    /**
     * Appends the given element value to the end of the vector.
     */
    void push_back(const T& value) {
        if (_size == _capacity)
        {
            if (_capacity == 0)
                resize(growth_factor * (_capacity+1));

            else 
                resize(growth_factor * _capacity);
        }
        _data[_size++] = value;
    }

    /**
     * Appends the given element value to the end of the vector.
     */
    void push_back(T&& value) {
        if (_size == _capacity)
        {
            if (_capacity == 0)
                resize(growth_factor * (_capacity+1));
            else 
                resize(growth_factor * _capacity);
        }
        _data[_size++] = std::move(value);
    }

    /**
     * Removes the last element of the vector.
     */
    void pop_back() {
        _size -= 1;
    }

    /**
     * Returns a reference to the element at specified location pos, with bounds checking.
     * If pos is not within the range of the vector, an exception of type std::out_of_range is thrown.
     */
    T& at(const size_t pos) const {
        if (pos < 0 || pos >= _size)
        {
            throw std::out_of_range("Out of range!");
        }
        return _data[pos];
    }

    /**
     * Returns a reference to the element at specified location pos, with bounds checking.
     * If pos is not within the range of the vector, an exception of type std::out_of_range is thrown.
     */
    T& at(const size_t pos) {
        if (pos < 0 || pos >= _size)
        {
            throw std::out_of_range("Out of range!");
        }
        return _data[pos];
    }

    /**
     * Returns a reference to the element at specified location pos.
     * No bounds checking is performed.
     */
    T& operator[](const size_t index) const {
        return _data[index];
    }

    /**
     * Returns a reference to the element at specified location pos.
     * No bounds checking is performed.
     */
    T& operator[](const size_t index) {
        return _data[index];
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
        size_t c;
        if (_capacity == 0)
        {
            c = new_size;
        }
        else if (_capacity < new_size)
        {
            c = growth_factor * _capacity;
        }
        
        return c;
    }

    /**
    * Resizes the vector to new_capacity.
    * If the current capacity is less than new_capacity
    * the vector moves all elements to a new array.
    */
    void resize(size_t new_capacity) {
        if (_capacity < new_capacity)
        {
            std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);
            for (size_t i = 0; i < _size; i++)
            {
                new_data[i] = std::move(_data[i]);
            }
            _data = std::move(new_data);
        }
        _capacity = new_capacity;
    }
};
