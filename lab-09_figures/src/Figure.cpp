#include "Figure.hpp"
#include "iostream"

Figure::Figure(int id, int x, int y) : id(id), x(x), y(y) {
}

void Figure::move(int new_x, int new_y) {
    this->x = new_x;
    this->y = new_y;
}

int Figure::get_id() const {
    return id;
}

void Figure::print() const {
    std::cout << id << ": x = " << x << " y = " << y;
}

Figure::~Figure() {
    id = 0;
    x = 0;
    y = 0;
}
