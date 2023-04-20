#include <algorithm>
#include "my_vector.hpp"


template<typename T>
containers::my_vector<T>::my_vector():my_vector<T>(2) {
}

template<typename T>
containers::my_vector<T>::my_vector(std::size_t n) {
    char *temp = new char[n * sizeof(T)];
    array_ = (T *) temp;
    capacity_ = 0;
    reserve(n);
    size_ = 0;
}

template<typename T>
containers::my_vector<T>::my_vector(my_vector &other) : capacity_(other.capacity_), size_(other.size_) {
    char *temp = new char[capacity_ * sizeof(T)];
    array_ = (T *) temp;
    for (unsigned int i = 0; i < size_; i++)
        new(array_ + i) T(other.array_[i]);
}


size_t clp2(size_t x) {
    size_t p2 = 1;
    while (true) {
        if (p2 >= x)
            return p2;
        p2 *= 2;
    }
}

template<typename T>
void containers::my_vector<T>::reserve(const std::size_t n) {
    if (capacity_ >= n)
        return;
    std::size_t new_capacity_ = clp2(n);
    capacity_ = new_capacity_;
    char *temp = new char[new_capacity_ * sizeof(T)];
    T *new_array = (T *) temp;
    for (std::size_t i = 0; i < size_; i++) {
        new(new_array + i) T(array_[i]);
    }
    clear();
    delete array_;
    array_ = new_array;
}

template<typename T>
void containers::my_vector<T>::push_back(const T &t) {
    resize(size_ + 1);
    new(array_ + size_ - 1) T(t);
}

template<typename T>
void containers::my_vector<T>::resize(const std::size_t n) {
    if (n > capacity_)
        reserve(std::max(n, 2 * capacity_));
    size_ = n;
}

template<typename T>
containers::my_vector<T> &containers::my_vector<T>::operator=(const my_vector &other) {
    if (this == &other)
        return *this;
    my_vector myVector(other);
    swap(*this, myVector);
    return *this;
}

template<typename T>
containers::my_vector<T>::~my_vector() {
    clear();
    delete array_;
}

template<typename T>
std::size_t containers::my_vector<T>::size() const {
    return size_;
}

template<typename T>
std::size_t containers::my_vector<T>::capacity() const {
    return capacity_;
}

template<typename T>
bool containers::my_vector<T>::empty() const {
    return size_ == 0;
}

template<typename T>
void containers::my_vector<T>::pop_back() {
    array_[size_ - 1].~T();
    size_--;
}

template<typename T>
void containers::my_vector<T>::clear() {
    for (std::size_t i = 0; i < capacity_; i++) {
        array_[i].~T();
    }
}

template<typename T>
T &containers::my_vector<T>::operator[](std::size_t index) {
    return array_[index];
}

