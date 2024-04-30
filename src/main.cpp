#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>

#include "../include/point.h"
#include "../include/rectangle.h"
#include "../include/BruteForce.h"
#include "../include/Map.h"
#include "../include/SegmentTree.h"

std::vector <point> newPoints(int n, int m) {
    std::vector <point> points;
    for (int i = 0; i < n; i++) {
        point newPoint;
        newPoint.x = rand() % (m * 20 + 1);
        newPoint.y = rand() % (m * 20 + 1);
        points.push_back(newPoint);
    }
    return points;
}

std::vector <rectangle> newRectangles(int n) {
    std::vector <rectangle> rectangles(n);
    for (int i = 0; i < n; i++) {
        rectangles[i].first = point(10 * i, 10 * i);
        rectangles[i].second = point(10 * (2 * n - i), 10 * (2 * n - i));
    }
    return rectangles;
}

using namespace std;

int main() {

    srand(time(nullptr));

    std::ofstream file("output.txt", std::ios::app);

    file << "m,n," <<"BruteForce," << "Map," << "PersistentTree" << "\n";

    for (int m = 250; m < 1000; m += 250) {
        auto n = m * m;

        file << m << "," << n << ",";

        vector<rectangle> recs = newRectangles(m);
        vector<point> pos = newPoints(n, recs.size() * 2 - 1);

        {
            auto start = chrono::steady_clock::now();
            std::vector<int> BrForce = BruteForce(pos, recs);
            cout << "\n";
            auto finish = chrono::steady_clock::now();
            chrono::duration<double> elapsed_seconds = finish - start;
            file << elapsed_seconds.count() << ",";
        }

        {
            auto start = chrono::steady_clock::now();
            Map compMap;
            std::vector<std::vector<int>> m = compMap.createMap(recs);
            std::vector<int> map = compMap.getMapValue(pos, m);
            auto finish = chrono::steady_clock::now();
            chrono::duration<double> elapsed_seconds = finish - start;
            file << elapsed_seconds.count() << ",";
        }

        {
            auto start = chrono::steady_clock::now();
            segmentTree tree;
            std::vector<segmentTree::Node *> rs = tree.buildPersistTree(recs);
            std::vector<int> segTree = tree.treeAnswer(rs, pos);
            auto finish = chrono::steady_clock::now();
            chrono::duration<double> elapsed_seconds = finish - start;
            file << elapsed_seconds.count() << "\n";
        }
    }


    return 0;
}
