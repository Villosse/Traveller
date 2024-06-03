#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "Line.h"
#include "Genetic_algorithm.h"
#include <cfloat> 
#include <thread>
using namespace std;
//Shuffle the nodes randomly
void Genetic_algorithm::shuffle_nodes()
{		
	for(size_t i = 0; i < rand() % (len_nodes-3) + 3; i++)
	{
		swap_nodes(rand() % (len_nodes), rand() % (len_nodes));
	}
}
//Swap two nodes in the nodes array
//Arguments: i1 and i2 are the indices of the nodes to swap
void Genetic_algorithm::swap_nodes(size_t i1, size_t i2)
{
	Node* temp = nodes[i1];
	nodes[i1] = nodes[i2];
	nodes[i2] = temp;
}
//Swap two individuals in the population array
//Arguments: i1 and i2 are the indices of the individuals to swap
void Genetic_algorithm::swap_individuals(size_t i1, size_t i2)
{
	Line* temp = population[i1];
	population[i1] = population[i2];
	population[i2] = temp;
}
//Constructor for the Genetic_algorithm class
//Arguments: _nodes is an array of Node pointers, _len_nodes is the number of nodes, _no_of_individuals is the number of individuals in the population, _nb_thread is the number of threads to use
Genetic_algorithm::Genetic_algorithm(Node** _nodes, size_t _len_nodes, size_t _no_of_individuals, size_t _nb_thread)
{
	no_of_individuals = _no_of_individuals;
	population = (Line**)malloc(no_of_individuals * sizeof(Line*));
	
	len_nodes = _len_nodes-1;
	nodes = (Node**)malloc(len_nodes * sizeof(Node*));
	
	for(size_t i=0; i<len_nodes; i++)
		nodes[i] = new Node(_nodes[i]);
	
	for(size_t i=0; i<no_of_individuals; i++)
	{
		shuffle_nodes();
		population[i] = new Line(nodes, len_nodes);
	}
	
	
	//setup multithreading
	nb_thread = _nb_thread;
	size_t nb_ind = no_of_individuals / nb_thread;
	
	data = (struct Data_new_pop**)malloc(nb_thread * sizeof(struct Data_new_pop*));
	thread_list = (pthread_t*)malloc(nb_thread * sizeof(pthread_t));
	
	for(size_t i=0; i < nb_thread; i++)
	{
		data[i] = (struct Data_new_pop*)malloc(sizeof(struct Data_new_pop));
		data[i]->start = nb_ind * i + 1;
		size_t ni = nb_ind * (i+1);
		data[i]->end = min(ni, no_of_individuals - ni);
		data[i]->ga_instance = this;
	}
}

//Assess the current generation and return the index of the best individual (the one with the shortest path)
//Returns: the index of the best individual
size_t Genetic_algorithm::generation_assessment()
{
	size_t best = 0;
	for(size_t i=1; i<no_of_individuals; i++)
	{
		if(population[i]->total_distance < population[best]->total_distance && population[i]->total_distance > 0)
			best = i;
	}
	return best;
}
//Check if a node in the son's path exists in the given range of the father's path
//Arguments: indexSon is the index of the son in the population, genStart and genEnd are the range in the father's path, to_search is the index in the son's path to search for
//Returns: the index in the father's path if found, otherwise -1
int Genetic_algorithm::in_genFather(size_t indexSon, size_t genStart, size_t genEnd, size_t to_search)
{
	for(size_t j=genStart; j<genEnd; j++)
		if(*(population[0]->node_list[j]) ==  *(population[indexSon]->node_list[to_search]))
			return j;
	return -1;
}
//Breed a new path for the son using the best individual
//Arguments: indexSon is the index of the son in the population
void Genetic_algorithm::breeding_with(size_t indexSon)
{
	size_t gen1;
	size_t gen2;
	size_t len = population[0]->len;
	
	size_t len_minus_one = len-1;
	
	do
	{
		gen1 = rand() % len_minus_one;
		gen2 = rand() % len_minus_one;
	}while(gen1 == gen2);
	size_t genStart = min(gen1, gen2);
	size_t genEnd = max(gen1, gen2);
		
	
	for(size_t i=0; i<len_minus_one; i++)
	{
		int index = in_genFather(indexSon, genStart, genEnd, i);
		if(index != -1)
			population[indexSon]->swap(index, i);
	}
}
//Thread function to create a new population
//Arguments: argv is a pointer to a Data_new_pop struct
//The function type must be "void* function_name(void*)"  
void* pthread_create_new_population(void * argv)
{
	struct Data_new_pop* data = (struct Data_new_pop*) argv;
	size_t len = data->ga_instance->population[0]->len;
	size_t len_minus_one = len - 1;
	
	for(size_t i=data->start; i<data->end; i++)
	{
		data->ga_instance->breeding_with(i);
		data->ga_instance->population[i]->mutate(data->number_of_mutation);
		
		//updating last node; the path need to be a loop
		data->ga_instance->population[i]->node_list[len_minus_one] = data->ga_instance->population[i]->node_list[0];
	
		data->ga_instance->population[i]->total_distance 						-= data->ga_instance->population[i]->distance_between_node[len_minus_one];
		data->ga_instance->population[i]->distance_between_node[len_minus_one] 	 = distance_between_node(data->ga_instance->population[i]->node_list[0], data->ga_instance->population[i]->node_list[len-2]);
		data->ga_instance->population[i]->total_distance 						+= data->ga_instance->population[i]->distance_between_node[len_minus_one];
	}

	return NULL;
}
//Create a new population with mutations
//Arguments: number_of_mutation is the number of mutations to apply
void Genetic_algorithm::create_new_population(size_t number_of_mutation)
{
	size_t best = generation_assessment();
	//we save the best line. Saving it is less costly than recreating it
	swap_individuals(0, best);
	
	for(size_t i=0; i < nb_thread; i++)
	{
		pthread_create(&(thread_list[i]), nullptr, pthread_create_new_population, data[i]);
	}
	
	for(size_t i=0; i < nb_thread; i++)
	{
		pthread_join(thread_list[i], nullptr);
	}
}
void doubleInLine(Line* l)
{
	for (size_t i = 0; i < l->len-1; i++)
	{
		for (size_t j = i+1; j < l->len-1; j++)
		{
			if(*(l->node_list[i]) == *(l->node_list[j]))
			{
				cout << i<<" "<<j<<endl;
				exit(1);
			}
		}
	}
}
//Find the shortest path over a number of generations
//Arguments: number_of_generation is the number of generations to run the algorithm
//Returns: a pointer to the Line object representing the shortest path found
//It isn't a new line, just a pointer to the best individual! It shoudn't be deleted!
Line* Genetic_algorithm::find_shortest_path(size_t number_of_generation)
{
	for(size_t i=1; i<number_of_generation; i++)
	{
		double percentage = (double)i / number_of_generation;
		size_t nb_mutation = (population[0]->len-1) * exp(-20 * percentage) + 1;
		
		if(nb_mutation != data[0]->number_of_mutation)
		{
			for(size_t i=0; i < nb_thread; i++)
				data[i]->number_of_mutation = nb_mutation;
		}
		cout << "generation n°" << i << "\t\tnumber_of_mutation:" << nb_mutation << "\t\tpercentage:" << percentage * 100 <<"%\r";
		create_new_population(nb_mutation);
		doubleInLine(population[0]);
	}
	
	printf("                                                                              \r");
	return population[0];
}
//Print the nodes
void Genetic_algorithm::print()
{
	for(size_t i=0; i<len_nodes; i++)
		nodes[i]->print();
}
//Destructor for the Genetic_algorithm class
Genetic_algorithm::~Genetic_algorithm()
{
	/*for(size_t i=0; i<len_nodes; i++)
		delete nodes[i];
	free(nodes);

	
	for(size_t i=0; i<no_of_individuals; i++)
		delete population[i];
	free(population);*/
	
	//I've no idea if it work well, but when I do it, this destructor doesn't crash, so I suppose it is ok (and idc if not, bc it doesn't have a hudge impact in the computer memory)
	delete[] nodes;
	delete[] population;
	
	/*cout << "thread\n";
	for(int i=nb_thread-1; i >= 0; i--)
	{
		cout << i << "\n";
		delete (thread_list[i]);
	}
	cout << "ok\n";*/
	free(thread_list);
	free(data);
}
