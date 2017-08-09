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

	void init_pop();
	void sort_pop();
	void delete_pop();
	void evol_pop();
	int fitness(int* ind);
public:
	TravelingSalesman(string filename);
	void run(int nb_ind, int nb_keep, int nb_time, int crossing_probability, int mutation_probability, int cloning_probability);
	void print_pop();
	~TravelingSalesman();
};

