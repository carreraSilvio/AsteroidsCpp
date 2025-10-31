#pragma once

#include <string>

class HighscoreService
{
public:
	/// <summary>
	/// Resests highscore to 0
	/// </summary>
	void resetHighscore();
	
	/// <summary>
	/// Update the highscore if the provided scorer is greater than the highscore
	/// </summary>
	void tryUpdateHighscore(unsigned int score);

	/// <summary>
	/// Get latest highscore
	/// </summary>
	/// <returns></returns>
	unsigned int getHighscore();

	/// <summary>
	/// Save highscore to file
	/// </summary>
	void save();

	/// <summary>
	/// Load highscore from file
	/// </summary>
	/// <returns></returns>
	void load();

private:
	unsigned int highscore;

	inline static const std::string FILEPATH = "highscore.txt";
};

