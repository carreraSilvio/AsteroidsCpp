#pragma once

#include <string>

class HighscoreService
{
public:
	/// <summary>
	/// Resets highscore to 0
	/// </summary>
	void resetHighscore();
	
	/// <summary>
	/// Updates the highscore if the provided score is greater
	/// </summary>
	void updateHighscore(unsigned int score);

	/// <summary>
	/// Gets latest highscore
	/// </summary>
	unsigned int getHighscore();

	/// <summary>
	/// Saves highscore to file
	/// </summary>
	void save();

	/// <summary>
	/// Loads highscore from file
	/// </summary>
	void load();

private:
	unsigned int highscore;

	inline static const std::string FILEPATH = "highscore.txt";
};

