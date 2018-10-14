#pragma once


#include <vector>
#include "Biome.h"

class Neanderthal;
struct Abilities;
struct Needs;

class Evolution
{
private:
	int numberOfHumans;
	int maxNumberOfGenerations;
	float mutationRate;
	float crossOverRate;
	int fitnessLimit;
	bool evolutionOver;

	int numberOfGenerationsNeeded;
	Biome currentBiome;

	std::vector<Neanderthal*> currentGeneration;
	std::vector<Neanderthal*> nextGeneration;

	std::vector <Neanderthal*> parents;
public:
	Evolution();
	~Evolution();

	void RunEvolution();
	void CreateFirstGeneration();

	void MakeNewGeneration();
	void SelectParents();
	
	void CreateNewKid(Neanderthal * parent1, Neanderthal * parent2);
	void CheckForMutations(Abilities &kidAbilities, Needs &maxNeeds);
	int Mutate();
};

