#include "../include/rectangle.h"

rectangle::rectangle() : first(point()), second(point()) {
}

rectangle::rectangle(point f, point s) : first(f), second(s) {
}

void rectangle::print_rectangle() {
    std::cout << "{";
    first.print_point();
    std::cout << ",";
    second.print_point();
    std::cout << "}";
}
