#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "Line.h"
 
using namespace std;


//Node Class
Node::Node(int _x, int _y)
{
	x = _x;
	y = _y;
}

Node::Node(Node* n)
{
	x = n->x;
	y = n->y;
}
	
void Node::print()
{
	cout << "(" << x << "," << y <<"), ";
}




//Line Class 
Line::Line()
{
    len = 0;
    total_distance = 0;
    node_list = (Node**)malloc(0);
    distance_between_node = (double*)malloc(0);
}

Line::Line(Node** _node_list, size_t _len)
{
    len = _len;
    node_list = (Node**)malloc(len * sizeof(Node*));
    distance_between_node = (double*)malloc((len-1) * sizeof(double));
    total_distance = 0;
    
    double d;
    
    for(size_t i=0; i<len; i++)
    {
    	node_list[i] = new Node(_node_list[i]);
    }
    
    for(size_t i=0; i<len-1; i++)
    {
    	d =  distance_to_next(i);
    	distance_between_node[i] = d;
    	total_distance += d;
    }
}

Line::Line(Line* line)
{
    len = line->len;
    total_distance = line->total_distance;
    node_list = (Node**)malloc(len * sizeof(Node*));
    distance_between_node = (double*)malloc((len-1) * sizeof(double));
    
    for(size_t i=0; i<len; i++)
    {
        Node* p = line->node_list[i];
        node_list[i] = new Node(p->x, p->y);
    }
    
    for(size_t i=0; i<len-1; i++)
    	distance_between_node[i] = line->distance_between_node[i];

}


void Line::random(size_t number_of_point, size_t max)
{
	/*
	Automatically creating random node.
	*/
	for(size_t i=0; i<number_of_point; i++)
   		add((size_t)(rand()) % max, (size_t)(rand()) % max);
}

void Line::mutate(size_t number_of_mutation)
{
	for(size_t i=0; i<number_of_mutation; i++)
	{
		size_t i1 = rand()%len;
		size_t i2 = rand()%len;
		
		swap(i1, i2);
		
		//distance update
		if(i1 != 0)
			distance_between_node[i1-1] = distance_to_next(i1-1);
		if(i1 != len-1)
			distance_between_node[i1] = distance_to_next(i1);
		
		if(i2 != 0)
			distance_between_node[i2-1] = distance_to_next(i2-1);
		if(i2 != len-1)
			distance_between_node[i2] = distance_to_next(i2);
		
		
	}
	
	total_distance = 0;
	for(size_t i=0; i<len-1; i++)
    	total_distance += distance_between_node[i];
}



void Line::add(int x, int y)
{
    len++;
    node_list = (Node**)realloc(node_list, len * sizeof(Node*));

    node_list[len - 1] = new Node(x,y);
    
    if(len > 1)
    {
    	double d = distance_to_next(len - 2);
    	distance_between_node = (double*)realloc(distance_between_node, (len - 1)* sizeof(double));
    	distance_between_node[len-2] = d;
	    total_distance += d;
	}
}
void Line::add(Node* node)
{
    len++;
    node_list = (Node**)realloc(node_list, len * sizeof(Node*));

    node_list[len - 1] = node;
    
    if(len > 1)
    {
    	double d = distance_to_next(len - 2);
    	distance_between_node = (double*)realloc(distance_between_node, (len - 1)* sizeof(double));
    	distance_between_node[len-2] = d;
	    total_distance += d;
	}
}
void Line::delete_last()
{
	if(len <= 0)
		return;
	len--;
	delete node_list[len-1];
	node_list = (Node**)realloc(node_list, len * sizeof(Node*));
}
void Line::delete_last_without_delete_node()
{
	if(len <= 0)
		return;
	len--;
	node_list = (Node**)realloc(node_list, len * sizeof(Node*));
}

void Line::print()
{
    for(size_t i=0; i<len; i++)
        node_list[i]->print();
    cout << "\n";
}

void Line::swap(size_t index1, size_t index2)
{
    Node* temp = node_list[index1];
    node_list[index1] = node_list[index2];
    node_list[index2] = temp;
}

double Line::distance(size_t index1, size_t index2)
{
    Node* p1 = node_list[index1];
    Node* p2 = node_list[index2];
    return sqrt((p2->x - p1->x)*(p2->x - p1->x) + (p2->y - p1->y)*(p2->y - p1->y));
}
double Line::distance_to_next(size_t index)
{
    return distance(index, index + 1);
}

Line::~Line()
{
    for(size_t i=0; i<len; i++)
        delete node_list[i];
    free(node_list);
    free(distance_between_node);
}





double distance_between_node(Node* p1, Node* p2)
{
	return sqrt((p2->x - p1->x)*(p2->x - p1->x) + (p2->y - p1->y)*(p2->y - p1->y));
}
