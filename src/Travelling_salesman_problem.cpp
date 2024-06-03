#include "Travelling_salesman_problem.h"

//recustive function used in the "shortest_path" function
void Travelling_salesman_problem::__shortest_path_brute_force(Line** best, int start, int end)
{
	
    if (start == end)
    {
    	double d = 0;
    	for(size_t i=0; i<len-1; i++)
	{
		d += distance_between_node(nodes[i], nodes[i+1]);
	}
	
	
	if(d < (*best)->total_distance)
	{
       		delete (*best);
       		*best = new Line(nodes, len);
       	}
       	return;
       	
    }
    
    for (size_t i = start; i <= end; i++)
    {
       	swap(start, i);
       	__shortest_path_brute_force(best, start + 1, end);
       	swap(start, i);
    }
}
void Travelling_salesman_problem::swap(size_t index1, size_t index2)
{
	Node* temp = nodes[index1];
	nodes[index1] = nodes[index2];
	nodes[index2] = temp;
}
Travelling_salesman_problem::Travelling_salesman_problem(Node** _nodes, size_t _len)
{
	len = _len;
	nodes = (Node**)malloc(len * sizeof(Node*));
	
	for(size_t i=0; i<len; i++)
	{
		Node* n = _nodes[i];
		nodes[i] = new Node(n->x, n->y);
	}
}
/*find the shortest path in the list of node
An optimisation can be done: this code generate all possible combinaison,
incuding repetitive statement (1234 = 4321)

Idc for now, it is just for test and comparing the mathematicaly best path.
Useless in the final project
*/
Line* Travelling_salesman_problem::shortest_path()
{
	Line** best = (Line**)malloc(sizeof(Line*));
	*best = new Line();
	(*best)->total_distance = DBL_MAX;
	
	__shortest_path_brute_force(best, 0, len - 1 );
	
	
	return (*best);
}
void Travelling_salesman_problem::print()
{
  std::cout << "len: " << len << "\n";
	for(size_t i=0; i<len; i++)
		nodes[i]->print();
}
Travelling_salesman_problem::~Travelling_salesman_problem()
{
	for(size_t i=0; i<len; i++)
		delete nodes[i];
	free(nodes);
}
