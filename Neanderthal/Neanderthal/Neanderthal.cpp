#include "Neanderthal.h"
#include <stdlib.h>
#include <iostream>



Neanderthal::Neanderthal()
{
	// Generate random numbers for first generation
	abilities.hunting = RollAbilityScore();
	abilities.waterTracking = RollAbilityScore();
	abilities.resting = RollAbilityScore();
	abilities.havingFun = RollAbilityScore();

	// Type out ability scores
	/*std::cout << "Ability scores:" << std::endl; 
	std::cout << "HUNTING: " << abilities.hunting << std::endl;
	std::cout << "DRINKING: " << abilities.waterTracking << std::endl;
	std::cout << "RESTING: " << abilities.resting << std::endl; 
	std::cout << "JOKING: " << abilities.havingFun << std::endl;*/

	// Setup max values
	/*maxNeeds.food = RollAbilityScore();
	maxNeeds.water = RollAbilityScore();
	maxNeeds.energy = RollAbilityScore();
	maxNeeds.entertainment = RollAbilityScore();*/

	maxNeeds.food = 4;
	maxNeeds.water = 4;
	maxNeeds.energy = 4;
	maxNeeds.entertainment = 4;

	// Setup current needs
	needs.food = maxNeeds.food;
	needs.water = maxNeeds.water;
	needs.energy = maxNeeds.energy;
	needs.entertainment = maxNeeds.entertainment;

	// Type out NEEDS
	/*std::cout << "MAXIMUM NEEDS:" << std::endl;
	std::cout << "FOOD: " << maxNeeds.food << std::endl;
	std::cout << "WATER: " << maxNeeds.water << std::endl;
	std::cout << "ENERGY: " << maxNeeds.energy << std::endl;
	std::cout << "FUN: " << maxNeeds.entertainment << std::endl;*/
	
	daysAlive = 1;
	isAlive = true;
}

Neanderthal::Neanderthal(Needs maxNeeds, Abilities abilities)
{
	this->needs = maxNeeds;
	this->maxNeeds = maxNeeds;
	this->abilities = abilities;


	daysAlive = 1;
	isAlive = true;
}


Neanderthal::~Neanderthal()
{
}

int Neanderthal::RollAbilityScore()
{
	int rolledAbilityScore = 0;

	for (int i = 0; i < 3; ++i)
	{
		rolledAbilityScore += rand() % 6 + 1;
	}

	return rolledAbilityScore;
}


int Neanderthal::GetDaysAlive() const
{
	return daysAlive;
}

void Neanderthal::SetDaysToSurpass(int fitnessLimit)
{
	this->daysToSurpass = fitnessLimit;
}

bool Neanderthal::SpendLife()
{
	int abilityCheck;

	do
	{
		// HUNTING
		abilityCheck = RollAbilityCheck(abilities.hunting);

		if (abilityCheck >= saveDC.huntingDifficulty)
		{
			needs.food = maxNeeds.food;
		}


		// GETTING WATER
		abilityCheck = RollAbilityCheck(abilities.waterTracking);

		if (abilityCheck >= saveDC.waterScarcity)
		{
			needs.water = maxNeeds.water;
		}

		// RESTING WELL
		abilityCheck = RollAbilityCheck(abilities.resting);

		if (abilityCheck >= saveDC.sleepingDifficulty)
		{
			needs.energy = maxNeeds.energy;
		}

		// ENTERTAINMENT
		abilityCheck = RollAbilityCheck(abilities.havingFun);

		if (abilityCheck >= saveDC.boredomDifficulty)
		{
			needs.entertainment = maxNeeds.entertainment;
		}

		// If any of the needs are 0 --> character dies
		if (needs.food <= 0 || needs.energy <= 0 || needs.entertainment <= 0 || needs.water <= 0)
		{	
			if (needs.food <= 0)
			{
				//std::cout << "DIED OF HUNGER." << std::endl;
			}
			if (needs.water <= 0)
			{
				//std::cout << "DIED OF THIRST." << std::endl;
			}
			if (needs.energy <= 0)
			{
				//std::cout << "DIED OF EXHAUSTION." << std::endl;
			}
			if (needs.entertainment <= 0)
			{
				//std::cout << "DIED OF BOREDOM." << std::endl;
			}
			

			
			isAlive = false;
			return false;
		}
		else
		{
			daysAlive++;
			needs.food--;
			needs.water--;
			needs.energy--;
			needs.entertainment--;
		}

	} while (isAlive && daysAlive <= daysToSurpass);

	return true;

	
}

int Neanderthal::RollD20()
{
	return (rand() % 19 + 1);
}

int Neanderthal::RollAbilityCheck(int abilityScore)
{
	// D&D ability checks
	if (abilityScore == 1)
	{
		return (RollD20() - 5);
	}
	else if (abilityScore == 2 || abilityScore == 3)
	{
		return (RollD20() - 4);
	}
	else if (abilityScore == 4 || abilityScore == 5)
	{
		return (RollD20() - 3);
	}
	else if (abilityScore == 6 || abilityScore == 7)
	{
		return (RollD20() - 2);
	}
	else if (abilityScore == 8 || abilityScore == 9)
	{
		return (RollD20() - 1);
	}
	else if (abilityScore == 10 || abilityScore == 11)
	{
		return RollD20();
	}
	else if (abilityScore == 12 || abilityScore == 13)
	{
		return (RollD20() + 1);
	}
	else if (abilityScore == 14 || abilityScore == 15)
	{
		return (RollD20() + 2);
	}
	else if (abilityScore == 16 || abilityScore == 17)
	{
		return (RollD20() + 3);
	}
	else if (abilityScore == 18 || abilityScore == 19)
	{
		return (RollD20() + 4);
	}
	// abilityScore = 20
	else if (abilityScore == 20 || abilityScore == 21)
	{
		return (RollD20() + 5);
	}
	else if (abilityScore == 22 || abilityScore == 23)
	{
		return (RollD20() + 6);
	}
	else if (abilityScore == 24 || abilityScore == 25)
	{
		return (RollD20() + 7);
	}
	else if (abilityScore == 26 || abilityScore == 27)
	{
		return (RollD20() + 8);
	}
	else if (abilityScore == 28 || abilityScore == 29)
	{
		return (RollD20() + 9);
	}
	else
	{
		return (RollD20() + 10);
	}
}

bool Neanderthal::GetIsAlive() const
{
	return isAlive;
}

void Neanderthal::SetBiome(Biome saveDC)
{
	this->saveDC = saveDC;
}
