#pragma once

#ifndef NODE_H

#include <iostream>

#define NODE_H

class Node
{
    public:
        int x;
        int y;
    Node(int _x, int _y);
    Node(Node* n);
    void print();
    bool operator==(const Node& other) const;
    bool operator!=(const Node& a);
};

#endif
