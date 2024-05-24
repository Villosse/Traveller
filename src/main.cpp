#include <iostream>
#include <cfloat>

#include "Line.h"
#include "Travelling_salesman_problem.h"
#include "Genetic_algorithm.h"


using namespace std;


int main()
{
	srand(123);
	
	Line* l = new Line();
	//l->random(20,1000);
	
	
	
	/*for(size_t i=0; i<100; i++)
		l->add((i*i)/1000,i);*/
		
	l->add(50,57);
	l->add(86,82);
	l->add(97,21);
	l->add(83,25);
	l->add(14,37);
	l->add(61,7);
	l->add(2,22);
	l->add(99,21);
	l->add(16,44);
	l->add(8,5);
	l->add(92,1);
	//l->add(50,35);
	
	
	l->print();
	
	cout << "Travelling_salesman_problem:\n";
	Travelling_salesman_problem* tsp = new Travelling_salesman_problem(l->node_list, l->len);
	
	Line* best = tsp->shortest_path();
	best->print();
	delete tsp;
	delete best;
	
	cout << "Genetic_algorithm:\n";
	//size_t best;
	double max_d = DBL_MAX;

		Genetic_algorithm* ga = new Genetic_algorithm(l->node_list, l->len, 10000, 50);
		
		
		
		Line* best_ga = ga->find_shortest_path(2000, 4);
		best_ga->print();
		//cout << (double)i/10 << ": best distance: " << ga->population[0]->total_distance << "\n\n";
		
		/*if(ga->population[0]->total_distance < max_d)
		{
			max_d = ga->population[0]->total_distance;
			//best = i;
		}*/
		
		delete ga;
	
	
	//cout << "best :" << (double)best/10 << "\td: " << max_d << "\n";
	
	delete l;
	
	return 0;
}
