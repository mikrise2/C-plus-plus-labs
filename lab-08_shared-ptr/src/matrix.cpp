#include "matrix.hpp"
#include "algorithm"
#include <cstdio>
#include <cstddef>


Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    _data = new int *[_rows];
    for (std::size_t i = 0; i < _rows; ++i) {
        _data[i] = new int[_cols];
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] = 0;
        }
    }
}

std::size_t Matrix::get_rows() const { return _rows; }

std::size_t Matrix::get_cols() const { return _cols; }

Matrix::~Matrix() {
    for (std::size_t i = 0; i < _rows; i++)
        delete[] _data[i];
    delete[] _data;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    return _data[i][j];
}

bool Matrix::operator==(const Matrix &that) const {
    if (_cols != that._cols && _rows != that._rows)
        return false;
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            if (_data[i][j] != that._data[i][j])
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &that) const {
    return !(*this == that);
}

Matrix::Matrix(const Matrix &that) {
    _cols = that._cols;
    _rows = that._rows;
    _data = new int *[_rows];
    for (std::size_t i = 0; i < _rows; ++i) {
        _data[i] = new int[_cols];
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] = 0;
        }
    }
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] += that._data[i][j];
        }
    }
}

Matrix &Matrix::operator=(const Matrix& that) {
    Matrix new_matrix = Matrix(that);
    swap(new_matrix);
    return *this;
}

void Matrix::swap(Matrix &m) {
    std::swap(_data, m._data);
    std::swap(_cols, m._cols);
    std::swap(_rows, m._rows);
}






