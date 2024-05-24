#pragma once


class Genetic_algorithm
{
	private:
	
	void shuffle_nodes();
	void swap_nodes(size_t i1, size_t i2);
	void swap_individuals(size_t i1, size_t i2);
	
public:	
		Line** population;
		size_t no_of_individuals;
		
		Node** nodes;
		size_t len_nodes;
		
		struct Data_new_pop** data;
		pthread_t* thread_list;
		size_t nb_thread;
		
		
		

	Genetic_algorithm(Node** _nodes, size_t _len_nodes, size_t _no_of_individuals, size_t _nb_thread);
	
	//return the index of the best individuals (shortest path)
	size_t generation_assessment();
	
	//if we want to do a real genetic algorithm
	void breeding(size_t indexFather, size_t indexSon, size_t commun_point);
	
	
	void create_new_population(size_t number_of_mutation);
	Line* find_shortest_path(size_t number_of_generation, size_t number_of_mutation);
	
	void print();
	
	~Genetic_algorithm();
};


void pthread_create_new_population(struct Data_new_pop* data);

struct Data_new_pop
{
	size_t number_of_mutation;
	size_t start;
	size_t end;
	Genetic_algorithm* ga_instance;
};
