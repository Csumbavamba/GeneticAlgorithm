#include "Evolution.h"
#include "Neanderthal.h"

#include <algorithm>
#include <iostream>


Evolution::Evolution()
{
	numberOfHumans = 1000;
	maxNumberOfGenerations = 15000;
	mutationRate = 0.01f;
	crossOverRate = 0.7f;
	fitnessLimit = 361;
	evolutionOver = false;
	currentBiome.SetBiomType(DESERT);

}


Evolution::~Evolution()
{
	// Delete the created neanderthals
	for (Neanderthal * human : currentGeneration)
	{
		delete human;
		human = NULL;
	}
}





void Evolution::RunEvolution()
{
	CreateFirstGeneration();

	numberOfGenerationsNeeded = 0;

	

	// REPATE Until fitness criteria met
	do
	{
		numberOfGenerationsNeeded++;

		Neanderthal * bestHuman = currentGeneration.back();

		// Calculate Fitness for every member of the current generation
		for (Neanderthal * human : currentGeneration)
		{
			human->SpendLife();
			
			// Select the best human
			if (human->GetDaysAlive() > bestHuman->GetDaysAlive())
			{
				bestHuman = human;
			}

			// Once one human fits the fitness limit, stop function
			if (human->GetDaysAlive() > fitnessLimit)
			{
				evolutionOver = true;
			}
		}

		// Print results to Screen
		if (evolutionOver)
		{
			std::cout << "Days Alive: " << bestHuman->GetDaysAlive() << std::endl;
			std::cout << "Number of Generations needed: " << numberOfGenerationsNeeded << std::endl;
			std::cout << std::endl;

			std::cout << "Best Human stats: " << std::endl;
			std::cout << "HUNTING: " << bestHuman->abilities.hunting << std::endl;
			std::cout << "DRINKING: " << bestHuman->abilities.waterTracking << std::endl;
			std::cout << "RESTING: " << bestHuman->abilities.resting << std::endl;
			std::cout << "JOKING: " << bestHuman->abilities.havingFun << std::endl;
			std::cout << std::endl;

			std::cout << "DAYS CAN SURVIVE WIHTOUT:" << std::endl;
			std::cout << "FOOD: " << bestHuman->maxNeeds.food << std::endl;
			std::cout << "WATER: " << bestHuman->maxNeeds.water << std::endl;
			std::cout << "ENERGY: " << bestHuman->maxNeeds.energy << std::endl;
			std::cout << "FUN: " << bestHuman->maxNeeds.entertainment << std::endl;


			break;
		}

		// Select the best parents based on the fitness
		SelectParents();

		// Select Best Parent for Printing to Screen
		Neanderthal * bestParent = parents.back();

		for (Neanderthal * parent : parents)
		{
			if (parent->GetDaysAlive() > bestParent->GetDaysAlive())
			{
				bestParent = parent;
			}
		}

		std::cout << "Most Days Alive Parent: " << bestParent->GetDaysAlive() << std::endl;

		// Create new Generation with the best parents
		MakeNewGeneration();

	} while (!evolutionOver || (maxNumberOfGenerations == numberOfGenerationsNeeded));
}

void Evolution::CreateFirstGeneration()
{
	for (int i = 0; i < numberOfHumans; ++i)
	{
		Neanderthal * human = new Neanderthal();
		human->SetDaysToSurpass(fitnessLimit);
		human->SetBiome(currentBiome);
		currentGeneration.push_back(human);
	}
}


void Evolution::MakeNewGeneration()
{
	// REPEAT until new generation is created
	do
	{
		// Get 2 random parents from the tournament selection
		Neanderthal * parent1 = parents.at(rand() % (parents.size() - 1));
		Neanderthal * parent2 = parents.at(rand() % (parents.size() - 1));

		// Create Kid from parents
		CreateNewKid(parent1, parent2);

	} while (nextGeneration.size() < numberOfHumans);


	
	// Remove current Generation
	for (Neanderthal * oldHuman : currentGeneration)
	{
		delete oldHuman;
		oldHuman = NULL;
	}
	
	// Make next Generation the current one
	currentGeneration = nextGeneration;
	
	// Make space for next generation
	nextGeneration.clear();
	parents.clear();

}

void Evolution::SelectParents()
{
	int tournamentBrackets = 4 * numberOfHumans / 100;
	int humansInBrackets = numberOfHumans / tournamentBrackets;
	
	Neanderthal * previousBest = NULL;

	// Tournament method for brackets based on number of Humans
	for (int i = 0; i < tournamentBrackets; ++i)
	{
		Neanderthal * previousBest = currentGeneration.at(i * humansInBrackets);

		for (int j = 0; j < humansInBrackets; ++j)
		{
			// Select the neanderthal with the best fitness value out of the tournament bracket
			if (currentGeneration[(i * humansInBrackets) + j]->GetDaysAlive() > previousBest->GetDaysAlive())
			{
				previousBest = currentGeneration[(i * humansInBrackets) + j];
			}
		}

		// Select the best as Parent
		parents.push_back(previousBest);
	}

	// Add one random parent for diversity 
	int randomParentNumber = rand() & numberOfHumans - 1;
	parents.push_back(currentGeneration.at(randomParentNumber));
}

void Evolution::CreateNewKid(Neanderthal * parent1, Neanderthal * parent2)
{
	Abilities kidAbilities;
	Needs maxNeeds;
	int crossPercentage = 100 * crossOverRate;

	// Get Kid Abilities
	// Hunting Ability
	if (crossPercentage < rand() & 100)
	{
		kidAbilities.hunting = parent1->abilities.hunting;
	}
	else
	{
		kidAbilities.hunting = parent2->abilities.hunting;
	}
	// Water Ability
	if (crossPercentage < rand() & 100)
	{
		kidAbilities.waterTracking = parent1->abilities.waterTracking;
	}
	else
	{
		kidAbilities.waterTracking = parent2->abilities.waterTracking;
	}
	// Resting
	if (crossPercentage < rand() & 100)
	{
		kidAbilities.resting = parent1->abilities.resting;
	}
	else
	{
		kidAbilities.resting = parent2->abilities.resting;
	}
	// Entertainment
	if (crossPercentage < rand() & 100)
	{
		kidAbilities.havingFun = parent1->abilities.havingFun;
	}
	else
	{
		kidAbilities.havingFun = parent2->abilities.havingFun;
	}
	

	// Get Kid Max Needs
	// Food
	if (crossPercentage < rand() & 100)
	{
		maxNeeds.food = parent1->maxNeeds.food;
	}
	else
	{
		maxNeeds.food = parent2->maxNeeds.food;
	}
	// Water
	if (crossPercentage < rand() & 100)
	{
		maxNeeds.water = parent1->maxNeeds.water;
	}
	else
	{
		maxNeeds.water = parent2->maxNeeds.water;
	}
	// Resting
	if (crossPercentage < rand() & 100)
	{
		maxNeeds.energy = parent1->maxNeeds.energy;
	}
	else
	{
		maxNeeds.energy = parent2->maxNeeds.energy;
	}
	// Entertainment
	if (crossPercentage < rand() & 100)
	{
		maxNeeds.entertainment = parent1->maxNeeds.entertainment;
	}
	else
	{
		maxNeeds.entertainment = parent2->maxNeeds.entertainment;
	}


	CheckForMutations(kidAbilities, maxNeeds);

	Neanderthal * kid = new Neanderthal(maxNeeds, kidAbilities);
	kid->SetDaysToSurpass(fitnessLimit);
	kid->SetBiome(currentBiome);
	nextGeneration.push_back(kid);

}

void Evolution::CheckForMutations(Abilities &kidAbilities, Needs &maxNeeds)
{
	// Decide which ability to mutate
	int randomNumber = (rand() % 4);

	switch (randomNumber)
	{
	case 0: // Mutate for Better Food Income
	{
		kidAbilities.hunting += Mutate();

		if (kidAbilities.hunting >= 20 && rand() % 100 > 85)
		{
			maxNeeds.food += Mutate();
		}

		break;
	}
	case 1: // Mutate for Better Water Income
	{
		kidAbilities.waterTracking += Mutate();

		if (kidAbilities.waterTracking >= 20 && rand() % 100 > 85)
		{
			maxNeeds.water += Mutate();
		}

		break;
	}
	case 2: // Mutate for Better Energy Income
	{
		kidAbilities.resting += Mutate();

		if (kidAbilities.resting >= 20 && rand() % 100 > 85)
		{
			maxNeeds.energy += Mutate();
		}

		break;
	}
	case 3: // Mutate for Better Entertainment Income
	{
		kidAbilities.havingFun += Mutate();

		if (kidAbilities.havingFun >= 20 && rand() % 100 > 85)
		{
			maxNeeds.entertainment += Mutate();
		}

		break;
	}
	default:
		break;
	}
	
}

int Evolution::Mutate()
{
	int randomNumber = rand() % 100 + 1;
	int mutationPercentage = mutationRate * 100;


	// If it's mutation time
	if (mutationPercentage >= randomNumber)
	{

		if ((rand() % 2))
		{
			return 1;
		}
		else
		{
			return -1;
		}
		
	}
	// No mutation
	return 0;
}
