#pragma once
#include <vector>
#include "BrightView.h"
#include <typeindex>

class BrightViewManager
{
public:
	inline static unsigned int DEFAULT_FONT_SIZE_SMALL = 18;  // for HUD labels, button text, minor info
	inline static unsigned int DEFAULT_FONT_SIZE_MEDIUM = 24; // for standard UI text, menus, scores
	inline static unsigned int DEFAULT_FONT_SIZE_LARGE = 32;  // for titles, headers, or emphasis
	inline static sf::Font DEFAULT_FONT;

	BrightViewManager();

	template<typename T>
	T* addView();

	template<typename T>
	T* openView();

	template<typename T>
	void closeView();

	template<typename T>
	T* getView();

	void update(float);
	void draw(sf::RenderWindow&);

private:
	std::unordered_map<std::type_index, std::unique_ptr<BrightView>> views;
	std::unordered_map<std::type_index, BrightView*> openedViews;
	inline static const std::string DEFAULT_FONT_PATH = "resources/arial.ttf";

};

template<typename T>
T* BrightViewManager::addView()
{
	static_assert(std::is_base_of_v<BrightView, T>,
		"T must derive from BrightView");

	auto view = std::make_unique<T>();
	T* ptr = view.get();
	views[typeid(T)] = std::move(view);
	return ptr;
}


template<typename T>
T* BrightViewManager::openView()
{
	T* view = static_cast<T*>(views[typeid(T)].get());
	view->open();
	openedViews[typeid(T)] = view;
	return view;
}

template<typename T>
void BrightViewManager::closeView()
{
	auto it = openedViews.find(typeid(T));
	if (it != openedViews.end())
	{
		it->second->close();
		openedViews.erase(it);
	}
}

template<typename T>
T* BrightViewManager::getView()
{
	T* view = views[typeid(T)].get();
	return view;
}