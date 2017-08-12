#include <iostream>
#include <string>
#include <cstdlib>
#include "TravelingSalesman.h"

using namespace std;

int main(int argc, char *argv[])
{
	TravelingSalesman *travelingSalesman;
	if (argc == 2)
	{
		travelingSalesman = new TravelingSalesman(argv[1]);		
	}
	else
	{
		travelingSalesman = new TravelingSalesman(500);
	}

	travelingSalesman->run(1000, 5, 10000, 80, 15, 5);

	delete travelingSalesman;

	system("PAUSE");
	exit(0);
}
