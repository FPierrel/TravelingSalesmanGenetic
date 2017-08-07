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
	int nb_pop;
	int nb_keep;
	int nb_time;
	
	void init_pop();
	void delete_pop();
public:
	TravelingSalesman(string filename);
	void run(int nb_pop, int nb_keep, int nb_time);
	void print_pop();
	~TravelingSalesman();
};

