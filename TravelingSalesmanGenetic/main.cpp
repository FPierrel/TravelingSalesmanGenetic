#include <iostream>
#include <string>
#include <cstdlib>
#include "TravelingSalesman.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "usage: " << argv[0] << " filename" << endl;
		return -1;
	}

	TravelingSalesman travelingSalesman(argv[1]);

	exit(0);
}