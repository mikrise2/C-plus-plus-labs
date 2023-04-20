#include "my_vector.hpp"
#include <cstddef>
#include <cmath>
#include <iostream>
#include <cstring>

int *expand_memory(const int *data, const std::size_t old_capacity, const std::size_t new_capacity) {
    int *new_data = new int[new_capacity];
    for (std::size_t i = 0; i < old_capacity; i++) {
        new_data[i] = data[i];
    }
    delete[] data;
    return new_data;
}


MyVector::MyVector() {
    init(0, 2);
}

MyVector::MyVector(const std::size_t init_capacity) {
    init(0, init_capacity);
}

const std::size_t MyVector::size() {
    return _size;
}

const std::size_t MyVector::capacity() {
    return _capacity;
}

void MyVector::reserve(const std::size_t new_capacity) {
    if (_capacity >= new_capacity)
        return;
    if (_capacity == 0)
        _data = new int[_capacity];
    _data = expand_memory(_data, _capacity, new_capacity);
    _capacity = new_capacity;
}

void MyVector::push_back(const int value) {
    resize(_size + 1);
    reserve(_size);
    _data[_size - 1] = value;
}

void MyVector::resize(const std::size_t new_size) {
    if (new_size > _capacity)
        reserve(std::max(new_size, 2 * _capacity));
    for (; _size < new_size; _size++) {
        _data[_size] = 0;
    }
}

void MyVector::set(const std::size_t index, const int value) {
    _data[index] = value;
}

MyVector::~MyVector() {
    _size = 0;
    _capacity = 0;
    delete[] _data;
}

int MyVector::get(const std::size_t index) {
    return _data[index];
}

MyVector::MyVector(const MyVector &vector) {
    copy(vector);
}

void MyVector::insert(const std::size_t index, const int value) {
    resize(_size + 1);
    for (std::size_t i = _size - 1; i > index; i--) {
        _data[i] = _data[i - 1];
    }
    _data[index] = value;
}

void MyVector::erase(const std::size_t index) {
    for (size_t i = index; i < _size; i++) {
        _data[i] = _data[i + 1];
    }
    _size--;
}

MyVector &MyVector::operator=(const MyVector &other) {
    copy(other);
    return *this;
}

void MyVector::init(size_t size, size_t capacity) {
    _capacity = 0;
    reserve(capacity);
    _size = size;
}

void MyVector::copy(const MyVector &other) {
    delete[] _data;
    init(other._size, other._capacity);
    _data = new int[_capacity];
    memcpy(_data, other._data, _size);
}
