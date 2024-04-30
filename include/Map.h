#ifndef LAB2_MAP_H
#define LAB2_MAP_H

#include <iostream>
#include <vector>
#include <set>
#include "rectangle.h"
#include "point.h"

class Map {

public:

    std::vector <int> x_array;
    std::vector <int> y_array;

    int binSearch(std::vector <int>& array, int target) {
        int left = 0;
        int right = array.size() - 1;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (array[middle] > target) {
                right = middle - 1;
            } else if (array[middle] < target) {
                left = middle + 1;
            } else {
                return middle;
            }
        }
        return right;
    }

    std::vector <std::vector <int>> createMap(std::vector<rectangle>& rectangles) {

        std::set <int> x_set;
        std::set <int> y_set;

        for (int i = 0; i < rectangles.size(); i++) {
            x_set.insert(rectangles[i].first.x);
            x_set.insert(rectangles[i].second.x);
            y_set.insert(rectangles[i].first.y);
            y_set.insert(rectangles[i].second.y);
        }

        x_array = std::vector <int>(x_set.begin(), x_set.end());
        y_array = std::vector <int>(y_set.begin(), y_set.end());

        std::vector <std::vector <int>> compressMap = std::vector <std::vector <int>> (x_array.size(), std::vector<int>(y_array.size(), 0));

        for (int i = 0; i < rectangles.size(); i++) {

            int x1 = binSearch(x_array, rectangles[i].first.x);
            int y1 = binSearch(y_array, rectangles[i].first.y);
            int x2 = binSearch(x_array, rectangles[i].second.x);
            int y2 = binSearch(y_array, rectangles[i].second.y);

            for (int x = x1; x < x2; x++) {
                for (int y = y1; y < y2; y++) {
                    compressMap[x][y]++;
                }
            }

        }

        return compressMap;

    }

    std::vector <int> getMapValue(std::vector<point>& points, std::vector <std::vector <int>>& map) {

        std::vector <int> count;

        for (int i = 0; i < points.size(); i++) {
            int x = binSearch(x_array, points[i].x);
            int y = binSearch(y_array, points[i].y);
            count.push_back(map[x][y]);
        }

        return count;
    }

};

#endif
