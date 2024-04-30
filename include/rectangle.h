#ifndef LAB2_RECTANGLE_H
#define LAB2_RECTANGLE_H
#include <iostream>
#include "point.h"

class rectangle {
public:
    point first;
    point second;

    rectangle();
    rectangle(point f, point s);

    void print_rectangle();
};

#endif
