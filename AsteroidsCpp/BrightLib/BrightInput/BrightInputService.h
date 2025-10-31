#pragma once
#include <vector>
#include <typeindex>
#include <SFML/Graphics.hpp>

enum class BrightActionButton
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	SHOOT,
	ATTACK,
	JUMP,
	MOVE_UP_LADDER,
	MOVE_DOWN_LADDER,

	//UI CONTEXT
	CONFIRM,
	BACK
};

class BrightInputService
{
public:

	BrightInputService();

	void bindKey(BrightActionButton, sf::Keyboard::Key);
	bool isButtonPressed(BrightActionButton);

private:
	std::unordered_map<BrightActionButton, std::vector<sf::Keyboard::Key>> actionToKeys;
};