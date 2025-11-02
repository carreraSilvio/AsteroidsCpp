#include "HighscoreService.h"
#include <fstream>

void HighscoreService::resetHighscore()
{
	highscore = 0;
}

void HighscoreService::updateHighscore(unsigned int score)
{
	if (score > highscore)
	{
		highscore = score;
	}
}

unsigned int HighscoreService::getHighscore()
{
	return highscore;
}

void HighscoreService::save()
{
	std::ofstream file(FILEPATH);
	file << highscore;
}

void HighscoreService::load()
{
	std::ifstream file(FILEPATH);
	int value = 0;
	if (file >> value)
	{
		highscore = value;
	}
}

