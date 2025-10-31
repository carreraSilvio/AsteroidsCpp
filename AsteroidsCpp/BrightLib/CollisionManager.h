#pragma once
#include <utility>

///DevNote: No need to instantiate this ever so that is why it's just within a namespace
namespace CollisionManager
{
    float clamp(float value, float min, float max)
    {
        return std::max(min, std::min(value, max));
    }

    bool checkCollisionCircleRect(const sf::Vector2f& circleCenter, float radius, const sf::FloatRect& rect)
    {
        // Find the closest point on the rectangle to the circle's center
        float closestX = clamp(circleCenter.x, rect.position.x, rect.position.x + rect.size.x);
        float closestY = clamp(circleCenter.y, rect.position.y, rect.position.y + rect.size.y);

        // Compute the distance between circle center and this point
        float dx = circleCenter.x - closestX;
        float dy = circleCenter.y - closestY;

        // If the distance is less than the radius, there's a collision
        return (dx * dx + dy * dy) <= (radius * radius);
    }

    bool checkCollisionRectRect(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB)
    {
        sf::FloatRect a = rectA.getGlobalBounds();
        sf::FloatRect b = rectB.getGlobalBounds();

        return (a.position.x < b.position.x + b.size.x &&
            a.position.x + a.size.x > b.position.x &&
            a.position.y < b.position.y + b.size.y &&
            a.position.y + a.size.y > b.position.y);
    }
};

