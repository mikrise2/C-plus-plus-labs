#include "Rectangle.hpp"
#include "iostream"
#include <stdlib.h>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y) {
    this->width = width;
    this->height = height;
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}

void Rectangle::print() const {
    std::cout << "Rectangle ";
    Figure::print();
    std::cout << " width = " << width << " height = " << height
         << std::endl;
}

bool Rectangle::is_inside(int x, int y) const {
    return float(abs(this->x-x)) <= float(width/2) && float (abs(this->y-y)) <= float(height/2);
}

Rectangle::~Rectangle() {
    width = 0;
    height = 0;
}

