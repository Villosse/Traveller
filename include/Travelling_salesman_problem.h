#pragma once


class Travelling_salesman_problem
{
	private:
		Node** nodes;
		size_t len;
		
	//recustive function used in the "shortest_path" function
	void __shortest_path_brute_force(Line** best, int start, int end);
	
	void swap(size_t index1, size_t index2);
	
	public:
	Travelling_salesman_problem(Node** _nodes, size_t _len);
	
	/*find the shortest path in the list of node
	An optimisation can be done: this code generate all pobbible combinaison,
	incuding repetitive statement (1234 = 4321)
	*/
	Line* shortest_path();

	void print();
	
	~Travelling_salesman_problem();
};
