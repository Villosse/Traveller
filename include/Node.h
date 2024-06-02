#pragma once

#ifndef NODE_H

#define NODE_H

class Node
{
  public:
    int x;
    int y;
  Node(int X, int Y);
  Node(Node* n);
  void print();
};

#endif
