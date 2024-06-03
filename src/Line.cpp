#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "Line.h"
#include "Node.h"
 
//Line Class
//Default constructor: Initializes an empty Line with zero length and distance
Line::Line()
{
    len = 0;
    total_distance = 0;
    node_list = (Node**)malloc(0);
    distance_between_node = (double*)malloc(0);
}
//Constructor: Initializes a Line with a given list of Nodes
//Arguments: Node** _node_list (pointer to array of Node pointers), size_t _len (number of Nodes)
Line::Line(Node** _node_list, size_t _len)
{
    len = _len + 1;
    node_list = (Node**)malloc(len * sizeof(Node*));
    distance_between_node = (double*)malloc((len-1) * sizeof(double));
    total_distance = 0;
    //Copy nodes to the node_list

    for(size_t i=0; i<len-1; i++)
    {
    	node_list[i] = new Node(_node_list[i]);
    }
    
    node_list[len-1] = node_list[0];
    
    //Calculate distances between nodes and total distance
    double d;
    for(size_t i=0; i<len-1; i++)
    {
    	d = distance_to_next(i);
    	distance_between_node[i] = d;
    	total_distance += d;
    }
}
//Copy constructor: Initializes a Line by copying another Line
//Arguments: Line* line (pointer to another Line object)
Line::Line(Line* line)
{
    len = line->len;
    total_distance = line->total_distance;
    node_list = (Node**)malloc(len * sizeof(Node*));
    distance_between_node = (double*)malloc((len-1) * sizeof(double));
    
    for(size_t i=0; i<len-1; i++)
    {
        Node* p = line->node_list[i];
        node_list[i] = new Node(p->x, p->y);
    }
    
    node_list[len-1] = node_list[0];
    
    for(size_t i=0; i<len-1; i++)
    	distance_between_node[i] = line->distance_between_node[i];
}
//Creates random nodes and adds them to the Line
//Arguments: size_t number_of_point (number of nodes), size_t max (maximum coordinate value)
void Line::random(size_t number_of_point, size_t max)
{
	/*
	Automatically creating random node.
	*/
	for(size_t i=0; i<number_of_point; i++)
   		add((size_t)(rand()) % max, (size_t)(rand()) % max);
   	
   	len++;
   	node_list = (Node**)realloc(node_list, (len)* sizeof(Node*));
   	node_list[len-1] = node_list[0];
   	double d = distance_to_next(len - 2);
    distance_between_node = (double*)realloc(distance_between_node, (len - 1)* sizeof(double));
    distance_between_node[len-2] = d;
	total_distance += d;
}
//Adds a new node to the Line with given coordinates
//Arguments: int x (x-coordinate), int y (y-coordinate)
void Line::add(int x, int y)
{
    len++;
    node_list = (Node**)realloc(node_list, len * sizeof(Node*));
    node_list[len - 1] = new Node(x, y);
    
    if(len > 1)
    {
    	double d = distance_to_next(len - 2);
    	distance_between_node = (double*)realloc(distance_between_node, (len - 1)* sizeof(double));
    	distance_between_node[len-2] = d;

	    total_distance += d;
	}
}
//Adds an existing Node to the Line
//Arguments: Node* node (pointer to a Node object)
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
//Deletes the last node in the Line and updates the length
void Line::delete_last()
{
	if(len <= 1)
		return;
	delete node_list[len-2];
	node_list[len-2] = node_list[len-1];
	len--;
	node_list = (Node**)realloc(node_list, len * sizeof(Node*));
}
//Deletes the last node in the Line without deleting the Node object itself
void Line::delete_last_without_delete_node()
{
	if(len <= 1)
		return;
	node_list[len-2] = node_list[len-1];
	len--;
	node_list = (Node**)realloc(node_list, len * sizeof(Node*));
}
//Prints the coordinates of all nodes in the Line
void Line::print()
{
    for(size_t i=0; i<len; i++)
        node_list[i]->print();
    std::cout << "\n";
}
//Mutates the Line by swapping nodes a given number of times
//Arguments: size_t number_of_mutation (number of swaps to perform)
void Line::mutate(size_t number_of_mutation)
{
	size_t len_minus_one = len-1;
	for(size_t i=0; i<number_of_mutation; i++)
	{
		size_t i1 = rand()%len_minus_one;
		size_t i2 = rand()%len_minus_one;
		swap(i1, i2);
	}
}
//Swaps two nodes in the Line and updates the distances
//Arguments: size_t index1 (index of first node), size_t index2 (index of second node)
void Line::swap(size_t index1, size_t index2)
{
    Node* temp = node_list[index1];
    node_list[index1] = node_list[index2];
    node_list[index2] = temp;

    
    //Update distances
	if(index1 != 0)
	{
		total_distance -= distance_between_node[index1-1];
		distance_between_node[index1-1] = distance_to_next(index1-1);
		total_distance += distance_between_node[index1-1];
	}
	if(index1 != len-1)
	{
		total_distance -= distance_between_node[index1];
		distance_between_node[index1] = distance_to_next(index1);
		total_distance += distance_between_node[index1];
	}
	if(index2 != 0)
	{
		total_distance -= distance_between_node[index2-1];
		distance_between_node[index2-1] = distance_to_next(index2-1);
		total_distance += distance_between_node[index2-1];
	}
	if(index2 != len-1)
	{
		total_distance -= distance_between_node[index2];
		distance_between_node[index2] = distance_to_next(index2);
		total_distance += distance_between_node[index2];
	}
}
//Calculates the distance between two nodes in the Line
//Arguments: size_t index1 (index of first node), size_t index2 (index of second node)
//Returns: double (distance between the nodes)
double Line::distance(size_t index1, size_t index2)
{
    Node* p1 = node_list[index1];
    Node* p2 = node_list[index2];
    return sqrt((p2->x - p1->x)*(p2->x - p1->x) + (p2->y - p1->y)*(p2->y - p1->y));
}
//Calculates the distance to the next node in the Line
//Arguments: size_t index (index of the node)
//Returns: double (distance to the next node)
double Line::distance_to_next(size_t index)
{
    return distance(index, index + 1);
}
//Equality operator: Checks if two Lines are equal based on their nodes and length
bool Line::operator==(const Line& a)
{
	if(a.len != len)
		return false;
	for(size_t i=0; i<len; i++)
		if(*node_list[i] != *a.node_list[i])
			return false;
	return true;
}
//Destructor: Cleans up memory allocated for the Line
Line::~Line()
{
	//std::cout << " \n";
	//print();
    /*for(size_t i=0; i<len-2; i++)
    {
    	std::cout << i;
    	node_list[i]->print();
    	std::cout << " \n";
        delete node_list[i];
    }

    std::cout << "nod okay\n";
    free(node_list);*/
    
    std::cout << "del Line\n";
    delete[] node_list;
    free(distance_between_node);
}
//Helper function: Calculates the distance between two nodes
//Arguments: Node* p1 (pointer to first node), Node* p2 (pointer to second node)
//Returns: double (distance between the nodes)
double distance_between_node(Node* p1, Node* p2)
{
	return sqrt((p2->x - p1->x)*(p2->x - p1->x) + (p2->y - p1->y)*(p2->y - p1->y));
}
