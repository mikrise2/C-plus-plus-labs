#include "Circle.hpp"
#include <cstring>
#include <iostream>

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y) {
    this->radius = radius;
    this->label = new char[strlen(label)+1];
    strcpy(this->label, label);
}

void Circle::zoom(int factor) {
    radius *= factor;
}

void Circle::print() const {
    std::cout << "Circle ";
    Figure::print();
    std::cout << " radius = " << radius << " label = " << label
              << std::endl;
}

bool Circle::is_inside(int x, int y) const {
    return (this->x - x) * (this->x - x) + (this->y - y) * (this->y - y) <= radius * radius;
}

Circle::~Circle() {
    delete[] label;
    radius = 0;
}
