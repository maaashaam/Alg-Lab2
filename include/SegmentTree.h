#ifndef LAB2_SEGMENTTREE_H
#define LAB2_SEGMENTTREE_H

#include <vector>
#include "rectangle.h"
#include <set>
#include <algorithm>

class segmentTree {

public:

    std::vector <int> arrayX;
    std::vector <int> arrayY;

    void createArrays(std::vector<rectangle>& rectangles) {
        std::set <int> x_set;
        std::set <int> y_set;

        for (auto & rectangle : rectangles) {
            x_set.insert(rectangle.first.x);
            x_set.insert(rectangle.second.x);
            y_set.insert(rectangle.first.y);
            y_set.insert(rectangle.second.y);
        }

        arrayX = std::vector <int>(x_set.begin(), x_set.end());
        arrayY = std::vector <int>(y_set.begin(), y_set.end());
    }

    struct Node {
        int value;
        int left_border;
        int right_border;
        Node* left_child;
        Node* right_child;

        Node(int val, int l, int r, Node* lc, Node* rc) : value(val), left_border(l), right_border(r), left_child(lc), right_child(rc) {}
    };

    struct Event {
        int x;
        int y_left;
        int y_right;
        int check;

        Event(int x, int y1, int y2, int c) : x(x), y_left(y1), y_right(y2), check(c) {}
    };

    Node* createTree(std::vector<int>& array, int left, int right) {

        if (right < left + 1) {
            return new Node(array[left], left, right, nullptr, nullptr);
        }

        int middle = (left + right) / 2;
        Node* left_child = createTree(array, left, middle);
        Node* right_child = createTree(array, middle + 1, right);
        return new Node(left_child->value + right_child->value, left_child->left_border, right_child->right_border, left_child, right_child);

    }

    Node* addNode(Node* node, int left, int right, int value){

        if (right < node->left_border || left > node->right_border)
            return node;

        if (left <= node->left_border && right >= node->right_border)
            return new Node(node->value + value, node->left_border, node->right_border, node->left_child, node->right_child);

        auto new_node = new Node(node->value, node->left_border, node->right_border, node->left_child, node->right_child);

        new_node->left_child = addNode(new_node->left_child, left, right, value);
        new_node->right_child = addNode(new_node->right_child, left, right, value);

        return new_node;
    }

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

    std::vector<Node*> buildPersistTree(std::vector<rectangle>& rectangles) {

        if (rectangles.empty())
            return {};

        createArrays(rectangles);

        std::vector <Event> tree_events;

        for (auto & rectangle : rectangles) {
            int x1 = binSearch(arrayX, rectangle.first.x);
            int y1 = binSearch(arrayY, rectangle.first.y);
            int x2 = binSearch(arrayX, rectangle.second.x);
            int y2 = binSearch(arrayY, rectangle.second.y);

            tree_events.push_back(Event(x1, y1, y2 - 1, 1));
            tree_events.push_back(Event(x2, y1, y2 - 1, -1));
        }

        std::sort(tree_events.begin(), tree_events.end(), [](Event& a, Event& b) { return a.x < b.x; });

        std::vector <int> roots(arrayY.size());
        std::vector <Node*> tree_roots;
        auto root = createTree(roots, 0, arrayY.size()-1);
        int tmp = tree_events[0].x;
        for (auto & tree_event : tree_events) {
            if (tree_event.x != tmp) {
                tree_roots.push_back(root);
                tmp = tree_event.x;
            }
            root = addNode(root, tree_event.y_left, tree_event.y_right, tree_event.check);
        }
        return tree_roots;
    }

    int answer(Node* root, int index) {
        if (!root) return 0;
        int middle = (root->left_border + root->right_border) / 2;
        int value;
        if (index <= middle) value = answer(root->left_child, index);
        else
            value = answer(root->right_child, index);
        return value + root->value;
    }

    std::vector<int> treeAnswer(std::vector<Node*>& roots, std::vector<point>& points) {
        std::vector<int> count(points.size());

        int c = 0;
        for (auto & point : points) {
            int x = binSearch(arrayX, point.x);
            int y = binSearch(arrayY, point.y);
            if (x == -1 || y == -1) {
                c++;
                continue;
            }
            count[c++] = answer(roots[x], y);
        }
        return count;
    }

};

#endif
