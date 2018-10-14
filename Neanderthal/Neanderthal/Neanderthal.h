#pragma once

#include "Biome.h"

struct Abilities
{
	int hunting;
	int waterTracking;
	int resting;
	int havingFun;
};

struct Needs
{
	int food;
	int water;
	int energy;
	int entertainment;
};

class Neanderthal
{
private:

	int daysAlive;
	bool isAlive;
	int daysToSurpass;

public:
	Neanderthal();
	Neanderthal(Needs maxNeeds, Abilities abilities);
	~Neanderthal();

	int RollAbilityScore();

	Needs needs;
	Needs maxNeeds;
	Abilities abilities;
	Biome saveDC;

	int GetDaysAlive() const;
	void SetDaysToSurpass(int fitnessLimit);
	bool SpendLife();
	int RollD20();
	int RollAbilityCheck(int abilityScore);
	bool GetIsAlive() const;
	void SetBiome(Biome saveDC);
	

};

