#pragma once

enum BiomeType
{
	JUNGLE,
	DESERT,
	CITY
};

struct Biome
{
	void SetBiomType(BiomeType type)
	{
		if (type == DESERT)
		{
			huntingDifficulty = 15;
			waterScarcity = 20;
			sleepingDifficulty = 10;
			boredomDifficulty = 10;
		}
		else if (type == CITY)
		{
			huntingDifficulty = 5;
			waterScarcity = 10;
			sleepingDifficulty = 20;
			boredomDifficulty = 8;
		}
		else if (type == JUNGLE)
		{
			huntingDifficulty = 8;
			waterScarcity = 8;
			sleepingDifficulty = 10;
			boredomDifficulty = 20;
		}
		else
		{
			huntingDifficulty = 15;
			waterScarcity = 15;
			sleepingDifficulty = 15;
			boredomDifficulty = 15;
		}
		
	}

	int huntingDifficulty;
	int waterScarcity;
	int sleepingDifficulty;
	int boredomDifficulty;
	
};