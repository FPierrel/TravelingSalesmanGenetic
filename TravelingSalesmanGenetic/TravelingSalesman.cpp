#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>

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

void TravelingSalesman::run(int nb_pop, int nb_keep, int nb_time)
{
	this->nb_pop = nb_pop;
	this->nb_keep = nb_keep;
	this->nb_time = nb_time;

	init_pop();
	print_pop();
	sort_pop();
	print_pop();
	delete_pop();
}

void TravelingSalesman::init_pop()
{
	this->population = new int*[this->nb_pop];
	for (int i = 0; i < nb_pop; i++)
		this->population[i] = new int[this->size + 1];
	
	for (int i = 0; i < nb_pop; i++)
		for (int j = 0; j < size + 1; j++)
			population[i][j] = -1;
	
	for (int i = 0; i < nb_pop; i++) 
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
	int* distances = new int[nb_pop];
	int** sorted_pop = new int*[nb_pop];
	for (int i = 0; i < nb_pop; i++)
		sorted_pop[i] = new int[size + 1];
	
	for (int i = 0; i < nb_pop; i++)
	{
		distances[i] = eval_ind(population[i]);
	}

	for (int i = 0; i < nb_pop; i++)
	{
		int best_id = -1;
		int best_value = INT_MAX;
		
		for (int j = 0; j < nb_pop; j++)
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

int TravelingSalesman::eval_ind(int* ind) {
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
	for (int i = 0; i < nb_pop; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{
			cout << population[i][j] << " ";
		}
		cout << "distance: " << eval_ind(population[i]) << endl;
	}
}

void TravelingSalesman::delete_pop()
{
	for (int i = 0; i < nb_pop; i++)
		delete[] population[i];

	delete[] population;
}

TravelingSalesman::~TravelingSalesman()
{
	for (int i = 0; i < size; i++)	
		delete[] distance_matrix[i];
	
	delete[] distance_matrix;
}
