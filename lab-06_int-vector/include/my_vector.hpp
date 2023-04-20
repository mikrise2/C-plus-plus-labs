#ifndef _MY_VECTOR_H_INCLUDED
#define _MY_VECTOR_H_INCLUDED

#include <cstddef>

class MyVector {
public:
    MyVector();

    MyVector(std::size_t init_capacity);

    ~MyVector();

    MyVector(const MyVector &vector);

    void set(const std::size_t index, const int value);

    int get(const std::size_t index);

    const std::size_t size();

    const std::size_t capacity();

    void reserve(const std::size_t new_capacity);

    void resize(const std::size_t new_size);

    void push_back(const int value);

    void insert(const std::size_t index, const int value);

    void erase(const std::size_t index);

    MyVector &operator=(const MyVector &other);

private:
    std::size_t _size, _capacity;
    int *_data;

    void init(const std::size_t size, const std::size_t capacity);

    void copy(const MyVector &other);
};

#endif
