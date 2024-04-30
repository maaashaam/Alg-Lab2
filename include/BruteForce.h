#ifndef LAB2_BRUTEFORCE_H
#define LAB2_BRUTEFORCE_H

#include <iostream>
#include <vector>
#include "point.h"
#include "rectangle.h"

std::vector <int> BruteForce(std::vector <point>& points, std::vector <rectangle>& rectangles) {

    std::vector <int> count(points.size());

    for (int i = 0; i < points.size(); i++) {

        point p = points[i];

        for (int j = 0; j < rectangles.size(); j++) {
            rectangle r = rectangles[j];

            if ((p.x >= r.first.x) && (p.x < r.second.x) && (p.y >= r.first.y) && (p.y < r.second.y)) {
                count[i] += 1;
            }

        }

    }

    return count;

}

#endif
