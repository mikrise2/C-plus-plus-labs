#include "Scheme.hpp"
#include <iostream>

Scheme::Scheme(int capacity) {
    size = 0;
    this->figures_ = new Figure *[capacity];
}

Scheme::~Scheme() {
    for (int i = 0; i < size; i++)
        delete figures_[i];
    delete[] figures_;
}

void Scheme::push_back_figure(Figure *fg) {
    figures_[size] = fg;
    size++;
}

void Scheme::remove_figure(int id) {
    int temp_index = 0;
    while (figures_[temp_index]->get_id() != id)
        temp_index++;
    delete figures_[temp_index];
    size--;
    for (int i = temp_index; i < size; i++)
        figures_[i] = figures_[i + 1];
}

void Scheme::print_all_figures() {
    for (int i = 0; i < size; i++)
        figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
    for (int i = 0; i < size; i++) {
        if (figures_[i]->get_id() == id)
            figures_[i]->zoom(factor);
    }
}

Figure *Scheme::is_inside_figure(int x, int y) {
    for (int i = 0; i < size; i++) {
        if (figures_[i]->is_inside(x, y))
            return figures_[i];
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    for (int i = 0; i < size; i++)
        if (figures_[i]->get_id() == id)
            figures_[i]->move(new_x, new_y);
}
