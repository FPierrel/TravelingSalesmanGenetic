#pragma once

#include <string>

using namespace std;

class TravelingSalesman
{
private:
	int** distance_matrix;
	int** population;
	int size;

	//Parameters
	int nb_ind;
	int nb_keep;
	int nb_time;
	int crossing_probability;
	int mutation_probability;
	int cloning_probability;

	int* cross(int p1, int p2);
	void init_pop();
	void sort_pop();
	void delete_pop();
	void evol_pop();
	int fitness(int* ind);
	void print_best();
	void print_pop();
public:
	TravelingSalesman(string filename);
	TravelingSalesman(int size);
	void run(int nb_ind, int nb_keep, int nb_time, int crossing_probability, int mutation_probability, int cloning_probability);	
	~TravelingSalesman();
};

