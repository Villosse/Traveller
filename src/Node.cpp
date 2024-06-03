#include "Node.h"
// Node Class
Node::Node(int _x, int _y) {
  x = _x;
  y = _y;
}
// Copy constructor: Initializes a Node by copying another Node
// Arguments: Node* n (pointer to another Node object)
Node::Node(Node *n) {
  x = n->x;
  y = n->y;
}
// Prints the coordinates of the Node
void Node::print() { std::cout << "(" << x << "," << y << "), "; }
// Equality operator: Checks if two Nodes are equal based on their coordinates
bool Node::operator==(const Node &other) const {
  return (x == other.x) && (y == other.y);
}
// Inequality operator: Checks if two Nodes are not equal based on their
// coordinates
bool Node::operator!=(const Node &a) { return !(*this == a); }
