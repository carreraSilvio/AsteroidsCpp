#pragma once
#include <vector>
#include <functional>
#include <utility>

//BrightEvent<int> or BrightEvent<int, float, std::string> both work.
template<typename... Args>
class BrightEvent
{
public:
    int subscribe(const std::function<void(Args...)>& func)
    {
        listeners.push_back(std::make_pair(++lastId, func ));
        return lastId;
    }

    void unsubscribe(int id)
    {
        listeners.erase(
            std::remove_if(listeners.begin(), listeners.end(),
                [id](const auto& p) { return p.first == id; }),
            listeners.end());
    }

    void fire(Args... args)
    {
        for (auto& pair : listeners)
        {
            pair.second(args...);
        }
    }
private:
    int lastId = 0;
    std::vector<std::pair<int, std::function<void(Args...)>>> listeners;
};
