#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

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
		{
			distance_matrix[i] = new int[this->size];
		}

		while (getline(file, line))
		{

		}

		file.close();
	}
	else
	{
		exit(-1);
	}
}


TravelingSalesman::~TravelingSalesman()
{
	for (int i = 0; i < size; i++)
	{
		delete[] distance_matrix[i];
	}
	delete[] distance_matrix;
}
