#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);

    Matrix(const Matrix &m);

    ~Matrix();

    std::size_t get_rows() const;

    std::size_t get_cols() const;

    void set(std::size_t i, std::size_t j, int val);

    int get(std::size_t i, std::size_t j) const;

    void print(FILE *f) const;

    friend Matrix operator+(const Matrix &m1, const Matrix &m2);

    friend Matrix operator-(const Matrix &m1, const Matrix &m2);

    friend Matrix operator*(const Matrix &m1, const Matrix &m2);

    Matrix &operator+=(const Matrix &m);

    Matrix &operator-=(const Matrix &m);

    Matrix &operator*=(const Matrix &m);

    Matrix &operator=(Matrix m);

    bool operator==(const Matrix &m) const;

    bool operator!=(const Matrix &m) const;

private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;

    void new_space();

    bool equals(const Matrix &m) const;

    void init(const Matrix &m);

    void destruct_data();

    void swap(Matrix &m);
};

#endif
