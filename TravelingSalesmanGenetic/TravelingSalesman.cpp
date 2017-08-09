#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

#include "TravelingSalesman.h"

using namespace std;

TravelingSalesman::TravelingSalesman(string filename)
{
	ifstream file(filename);

	if (file)
	{
		string line;
		getline(file, line);

		this->size = stoi(line);
		this->distance_matrix = new int*[this->size];
		for (int i = 0; i < size; i++)		
			distance_matrix[i] = new int[this->size];
		

		int idx = 0;		
		while (getline(file, line))
		{
			int idy = 0;
			stringstream stream(line);
			while (true)
			{
				if (!stream)
					break;
				stream >> distance_matrix[idx][idy];
				idy++;
			}
			idx++;
		}
		
		file.close();
	}
	else
	{
		exit(-1);
	}
}

void TravelingSalesman::run(int nb_ind, int nb_keep, int nb_time, int crossing_probability, int mutation_probability, int cloning_probability)
{
	this->nb_ind = nb_ind;
	this->nb_keep = nb_keep;
	this->nb_time = nb_time;
	this->crossing_probability = crossing_probability;
	this->mutation_probability = mutation_probability;
	this->cloning_probability = cloning_probability;

	init_pop();
	print_pop();
	sort_pop();
	print_pop();
	delete_pop();
}

void TravelingSalesman::init_pop()
{
	this->population = new int*[this->nb_ind];
	for (int i = 0; i < nb_ind; i++)
		this->population[i] = new int[this->size + 1];
	
	for (int i = 0; i < nb_ind; i++)
		for (int j = 0; j < size + 1; j++)
			population[i][j] = -1;
	
	for (int i = 0; i < nb_ind; i++) 
	{
		population[i][0] = 0;
		for (int j = 1; j < size; j++) {
			population[i][j] = j;
		}
		population[i][size] = 0;

		random_shuffle(&population[i][1], &population[i][size]);
	}
}

void TravelingSalesman::sort_pop()
{
	int* distances = new int[nb_ind];
	int** sorted_pop = new int*[nb_ind];
	for (int i = 0; i < nb_ind; i++)
		sorted_pop[i] = new int[size + 1];
	
	for (int i = 0; i < nb_ind; i++)
	{
		distances[i] = fitness(population[i]);
	}

	for (int i = 0; i < nb_ind; i++)
	{
		int best_id = -1;
		int best_value = INT_MAX;
		
		for (int j = 0; j < nb_ind; j++)
		{
			if (distances[j] < best_value)
			{
				best_id = j;
				best_value = distances[j];
			}
		}

		distances[best_id] = INT_MAX;
		for (int j = 0; j < size + 1; j++)
		{
			sorted_pop[i][j] = population[best_id][j];
		}
	}

	delete_pop();
	population = sorted_pop;
}

void TravelingSalesman::evol_pop() 
{
	int** new_pop = new int*[this->nb_ind];
	for (int i = 0; i < nb_ind; i++)
		new_pop[i] = new int[this->size + 1];

	srand(time(NULL));
	for (int idx_new_pop = 0; idx_new_pop < nb_keep; idx_new_pop++)
	{		
		if (idx_new_pop < nb_keep)
		{
			for (int i = 0; i < size + 1; i++)
				new_pop[idx_new_pop][i] = population[idx_new_pop][i];
		}
		else
		{
			int rnd = rand() % 100;
			if (rnd < crossing_probability)
			{

			}
			else if (rnd < crossing_probability + mutation_probability)
			{
				int pos_1 = rand() % (size - 1) + 1;
				int pos_2 = rand() % (size - 1) + 1;
				while (pos_1 == pos_2)
					pos_2 = rand() % (size - 1) + 1;

				for (int i = 0; i < size + 1; i++)
					new_pop[idx_new_pop][i] = population[idx_new_pop][i];
				new_pop[idx_new_pop][pos_1] = population[idx_new_pop][pos_2];
				new_pop[idx_new_pop][pos_2] = population[idx_new_pop][pos_1];
			}
			else
			{
				for (int i = 0; i < size + 1; i++)
					new_pop[idx_new_pop][i] = population[idx_new_pop][i];
			}
		}

	}

}

int TravelingSalesman::fitness(int* ind) 
{
	int total = 0;

	for (int i = 0; i < size; i++) 
	{
		total += distance_matrix[ind[i]][ind[i + 1]];
	}

	return total;
}

void TravelingSalesman::print_pop()
{
	cout << "Population: " << endl;
	for (int i = 0; i < nb_ind; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{
			cout << population[i][j] << " ";
		}
		cout << "distance: " << fitness(population[i]) << endl;
	}
}

void TravelingSalesman::delete_pop()
{
	for (int i = 0; i < nb_ind; i++)
		delete[] population[i];

	delete[] population;
}

TravelingSalesman::~TravelingSalesman()
{
	for (int i = 0; i < size; i++)	
		delete[] distance_matrix[i];
	
	delete[] distance_matrix;
}
