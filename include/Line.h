#pragma once

class Node
{
    public:
        int x;
        int y;
    Node(int _x, int _y);
    Node(Node* n);
    void print();
};


class Line
{
    public:
        size_t len;
        Node** node_list;
        double* distance_between_node;
        double total_distance;
    Line();
    Line(Node** _node_list, size_t _len);
    Line(Line* line);
    void random(size_t number_of_point, size_t max);
    void mutate(size_t number_of_mutation);
    
    void add(int x, int y);
    void add(Node* node);
    
    void delete_last();
    void delete_last_without_delete_node();
    
    void print();
    void swap(size_t index1, size_t index2);
    
    double distance(size_t index1, size_t index2);
    double distance_to_next(size_t index);
    ~Line();
};
 
double distance_between_node(Node* p1, Node* p2);
