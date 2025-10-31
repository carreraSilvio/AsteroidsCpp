#pragma once
#include <vector>
#include "BrightView.h"
#include <typeindex>

class BrightViewManager
{
private:
	std::unordered_map<std::type_index, std::unique_ptr<BrightView>> views;
	std::vector<BrightView*> openedViews;
	inline static const std::string DEFAULT_FONT_PATH = "resources/arial.ttf";

public:
	inline static unsigned int DEFAULT_FONT_SIZE = 24;
	inline static sf::Font DEFAULT_FONT;

	BrightViewManager();

	template<typename T>
	T* addView();

	template<typename T>
	T* openView();

	template<typename T>
	T* getView();

	void update(float);
	void draw(sf::RenderWindow&);
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
	T* view = views[typeid(T)].get();
	view->open();
	openedViews.push_back(view);
	return view;
}

template<typename T>
T* BrightViewManager::getView()
{
	T* view = views[typeid(T)].get();
	return view;
}