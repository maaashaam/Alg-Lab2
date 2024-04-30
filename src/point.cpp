#include "../include/point.h"

point::point() : x(0), y(0) {}

point::point(int x_, int y_) : x(x_), y(y_){}

void point::print_point() {
    std::cout << "(" << x << "," << y << ")";
}