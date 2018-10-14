#include <iostream>
#include <time.h>

#include "Neanderthal.h"
#include "Evolution.h"
#include <vld.h>



int main()
{
	srand(time(NULL));

	Evolution evolution;

	evolution.RunEvolution();

	/*Neanderthal * first = new Neanderthal();
	first->SetDaysToSurpass(31);
	first->SpendLife();*/

	/*std::cout << "Days Alive: " << first->GetDaysAlive() << std::endl;

	delete first;*/

	int wait;
	std::cin >> wait;

	return 0;
}