#include "Node.h"
#include <iostream>
//Node Class
Node::Node(int X, int Y)
{
	x = X;
	y = Y;
}

Node::Node(Node* n)
{
	x = n->x;
	y = n->y;
}
	
void Node::print()
{
  std::cout << "(" << x << "," << y <<"), ";
}
