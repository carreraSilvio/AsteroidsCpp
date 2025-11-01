#include "Ship.h"
#include "GameConstants.h"
#include "Services.h"

Ship::Ship(float x, float y)
{
	rotation = sf::degrees(0.0f);
	thrust = 200.0f;
	linerDamping = 0.75f;

	shape.setPointCount(3);
	shape.setPoint(0, { 20.f, 0.f });
	shape.setPoint(1, {-10.f, 10.f });
	shape.setPoint(2, {-10.f, -10.f });
	shape.setOrigin(sf::Vector2(0.0f, 0.0f));
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(sf::Vector2(x, y));
}

void Ship::resetPosition()
{
	rotation = sf::degrees(0.0f);

	//reset position
	setPosition(GameConstants::WINDOW_WIDTH / 2, GameConstants::WINDOW_HEIGHT / 2);
}

void Ship::update(float dt)
{
	if (Services::Input().isButtonPressed(BrightActionButton::MOVE_LEFT))
	{
		rotation -= rotationSpeed * dt;
	}
	else if (Services::Input().isButtonPressed(BrightActionButton::MOVE_RIGHT))
	{
		rotation += rotationSpeed * dt;
	}

	// thrust (booster)
	if (Services::Input().isButtonPressed(BrightActionButton::THRUST))
	{
		float rad = rotation.asRadians();
		sf::Vector2f forward(std::cos(rad), std::sin(rad));
		velocity += forward * thrust * dt;
	}

	// apply velocity and drag
	position += velocity * dt;
	velocity -= velocity * linerDamping * dt;
	setPosition(position);
	shape.setRotation(rotation);


	//shoot
	if (Services::Input().isButtonPressed(BrightActionButton::SHOOT))
	{
		onShoot.fire();
	}
}

void Ship::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Ship::setPosition(float x, float y)
{
	position = { x,y };
	setPosition(position);
}
void Ship::setPosition(sf::Vector2f position)
{
	this->position = position;
	shape.setPosition(position);
}

const sf::Vector2f Ship::getFrontPoint()
{
	return shape.getTransform().transformPoint(shape.getPoint(0));
}

const sf::Vector2f Ship::getForwardVector()
{
	float rad = rotation.asRadians();
	return sf::Vector2f(std::cos(rad), std::sin(rad));
}
