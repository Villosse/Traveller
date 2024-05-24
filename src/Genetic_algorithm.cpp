#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "Line.h"
#include "Genetic_algorithm.h"
#include <cfloat> 
#include <thread>

using namespace std;





void Genetic_algorithm::shuffle_nodes()
{		
	for(size_t i = 0; i < rand() % (len_nodes-3) + 3; i++)
	{
		swap_nodes(rand() % len_nodes, rand() % len_nodes);
	}
}

void Genetic_algorithm::swap_nodes(size_t i1, size_t i2)
{
	Node* temp = nodes[i1];
	nodes[i1] = nodes[i2];
	nodes[i2] = temp;
}

void Genetic_algorithm::swap_individuals(size_t i1, size_t i2)
{
	Line* temp = population[i1];
	population[i1] = population[i2];
	population[i2] = temp;
}




Genetic_algorithm::Genetic_algorithm(Node** _nodes, size_t _len_nodes, size_t _no_of_individuals, size_t _nb_thread)
{
	no_of_individuals = _no_of_individuals;
	population = (Line**)malloc(no_of_individuals * sizeof(Line*));
	
	len_nodes = _len_nodes;
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
		data[i]->end = min(nb_ind * (i+1), no_of_individuals - (nb_ind * (i+1)));
		data[i]->ga_instance = this;
	}
	
	/*
	for(size_t i=0; i < nb_thread; i++)
	{
		data[i] = (struct Data_new_pop*)malloc(sizeof(struct Data_new_pop));
		data->start = nb_ind * i + 1;
		data->end = min(nb_ind * (i+1), no_of_individuals - (nb_ind * (i+1)));
		data->ga_instance = this;
		
		pthread_create(&thread, nullptr, pthread_create_new_population, data);
		
		pthread_join(thread, nullptr);
	}
	*/
}


//return the index of the best individuals (shortest path)
size_t Genetic_algorithm::generation_assessment()
{
	size_t best = 0;
	for(size_t i=1; i<no_of_individuals; i++)
	{
		if(population[i]->total_distance < population[best]->total_distance)
			best = i;
	}
	return best;
}

//if we want to do a real genetic algorithm
//void Genetic_algorithm::breeding(size_t indexFather, size_t indexSon, size_t commun_point);



void* pthread_create_new_population(void * argv)
{
	struct Data_new_pop* data = (struct Data_new_pop*) argv;
	
	//cout << "thread " << data->start << " to " << data->end <<"\n";
	for(size_t i=data->start; i<data->end; i++)
	{
		delete data->ga_instance->population[i];
		data->ga_instance->population[i] = new Line(data->ga_instance->population[0]);
		data->ga_instance->population[i]->mutate(data->number_of_mutation);
	}
	//cout << "thread " << data->start << " done\n";
	return NULL;
}

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

Line* Genetic_algorithm::find_shortest_path(size_t number_of_generation, size_t number_of_mutation)
{
	for(size_t i=1; i<number_of_generation; i++)
	{
		cout << "generation n°" << i << "\r";
		create_new_population(number_of_mutation);
	}
	return population[0];
}


void Genetic_algorithm::print()
{
	for(size_t i=0; i<len_nodes; i++)
		nodes[i]->print();
}

Genetic_algorithm::~Genetic_algorithm()
{
	for(size_t i=0; i<len_nodes; i++)
		delete nodes[i];
	free(nodes);
	
	for(size_t i=0; i<no_of_individuals; i++)
		delete population[i];
	free(population);
	
	free(thread_list);
	free(data);
}


