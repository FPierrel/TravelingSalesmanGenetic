#pragma once

#include <string>

using namespace std;

class TravelingSalesman
{
private:
	int** distance_matrix;
	int size;
public:
	TravelingSalesman(string filename);
	~TravelingSalesman();
};

