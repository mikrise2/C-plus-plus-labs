#pragma once

#include "Figure.hpp"

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);

    ~Rectangle() override;

    void zoom(int factor) override;

    void print() const override;

    bool is_inside(int x, int y) const override;

private:
    int width;

    int height;
};
