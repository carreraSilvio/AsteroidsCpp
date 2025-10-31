#pragma once
#include <vector>
#include "BrightState.h"
#include <typeindex>
#include "BrightUI/BrightViewManager.h"

class BrightFSM
{
private:
	std::unordered_map<std::type_index, std::unique_ptr<BrightState>> states;
	BrightState* currentState = nullptr;

	std::type_index initialStateTypeId{ typeid(void) };
	std::type_index nextStateTypeId{ typeid(void) };

	BrightViewManager viewManager;

public:
	BrightFSM();

	template<typename T>
	void addState();

	template<typename T>
	void setInitialState();
	
	void enterInitialState();
	void update(float);
	void draw(sf::RenderWindow&);
};

template<typename T>
void BrightFSM::addState()
{
	static_assert(std::is_base_of_v<BrightState, T>,
		"T must derive from BrightState");

	auto state = std::make_unique<T>();
	states[typeid(T)] = std::move(state);
}

template<typename T>
void BrightFSM::setInitialState()
{
	initialStateTypeId = typeid(T);
	auto state = std::make_unique<T>();
	states[typeid(T)] = std::move(state);
}