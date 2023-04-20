#include "matrix.h"
#include <cstdio>
#include <cstddef>
#include <cstring>
#include <exception>


Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    new_space();
}

Matrix::Matrix(const Matrix &m) {
    init(m);
}

std::size_t Matrix::get_rows() const { return _rows; }

std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    if (i < 0 || i >= this->get_rows() || j < 0 || j >= this->get_cols()) {
        throw MatrixException("ACCESS: bad index.");
    }
    return _data[i][j];
}

void Matrix::print(FILE *f) const {
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            if (j != _cols - 1)
                fprintf(f, "%d ", _data[i][j]);
            else
                fprintf(f, "%d", _data[i][j]);
        }
        fprintf(f, "\n");
    }
}

bool Matrix::operator==(const Matrix &m) const {
    return equals(m);
}

bool Matrix::operator!=(const Matrix &m) const {
    return !equals(m);
}

Matrix &Matrix::operator+=(const Matrix &m) {
    if (this->get_cols() != m.get_cols() || this->get_rows() != m.get_rows()) {
        throw MatrixException("ADD: dimensions do not match.");
    }
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] += m._data[i][j];
        }
    }
    return *this;
}


Matrix &Matrix::operator-=(const Matrix &m) {
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] -= m._data[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &m) {
    if (this->get_cols() != m.get_rows()) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
    Matrix new_matrix(_rows, m._cols);
    for (std::size_t i = 0; i < new_matrix._rows; i++) {
        for (std::size_t j = 0; j < new_matrix._cols; j++) {
            for (std::size_t l = 0; l < _cols; l++) {
                new_matrix._data[i][j] += (_data[i][l] * m._data[l][j]);
            }
        }
    }
    *this = new_matrix;
    return *this;
}

void Matrix::new_space() {
    _data = new int *[_rows];
    for (std::size_t i = 0; i < _rows; ++i) {
        _data[i] = new int[_cols];
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] = 0;
        }
    }
}

Matrix::~Matrix() {
    destruct_data();
}


bool Matrix::equals(const Matrix &m) const {
    if (_cols != m._cols && _rows != m._rows)
        return false;
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            if (_data[i][j] != m._data[i][j])
                return false;
        }
    }
    return true;
}

Matrix &Matrix::operator=(Matrix m) {
    swap(m);
    return *this;
}

void Matrix::init(const Matrix &m) {
    _cols = m._cols;
    _rows = m._rows;
    new_space();
    *this += m;
}

void Matrix::destruct_data() {
    for (std::size_t i = 0; i < _rows; i++)
        delete[] _data[i];

    delete[] _data;
}

Matrix operator*(const Matrix &m1, const Matrix &m2) {
    Matrix new_matrix(m1);
    new_matrix *= m2;
    return new_matrix;
}

Matrix operator+(const Matrix &m1, const Matrix &m2) {
    Matrix new_matrix(m1);
    new_matrix += m2;
    return new_matrix;
}

Matrix operator-(const Matrix &m1, const Matrix &m2) {
    Matrix new_matrix(m1);
    new_matrix -= m2;
    return new_matrix;

}

void Matrix::swap(Matrix &m) {
    std::swap(_data, m._data);
    std::swap(_cols, m._cols);
    std::swap(_rows, m._rows);
}

MatrixException::MatrixException(const char *message) {
    this->message = new char[strlen(message)];
    strcpy(this->message, message);
}

const char *MatrixException::what() const noexcept {
    return message;
}
