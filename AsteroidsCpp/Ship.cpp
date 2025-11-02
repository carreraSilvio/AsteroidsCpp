#include "Ship.h"
#include "GameConstants.h"
#include "Services.h"

Ship::Ship(float x, float y) 
	: thrust(200.0f),
	shootTimer(SHOOT_INTERVAL),
	linerDamping(0.75f),
	thrusterShape({ THRUSTER_LENGTH, THRUSTER_THICKNESS })
{
	rotation = sf::degrees(0.0f);

	shape.setPointCount(3);
	shape.setPoint(0, { 20.f, 0.f });
	shape.setPoint(1, {-10.f, 10.f });
	shape.setPoint(2, {-10.f, -10.f });
	shape.setOrigin(sf::Vector2(0.0f, 0.0f));
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(sf::Vector2(x, y));

	thrusterShape.setFillColor(sf::Color::Red);
	thrusterShape.setOrigin({ 0.0f, THRUSTER_THICKNESS / 2.0f });
}

void Ship::resetPosition()
{
	rotation = sf::degrees(0.0f);
	velocity = {0.0f, 0.0f};
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

	// thrust
	thrusting = false;
	if (Services::Input().isButtonPressed(BrightActionButton::THRUST))
	{
		float rad = rotation.asRadians();
		sf::Vector2f forward(std::cos(rad), std::sin(rad));
		velocity += forward * thrust * dt;
		thrusting = true;
	}

	// apply velocity and drag
	position += velocity * dt;
	velocity -= velocity * linerDamping * dt;
	setPosition(position);
	shape.setRotation(rotation);

	//shoot
	if (shootTimer.update(dt) && Services::Input().isButtonPressed(BrightActionButton::SHOOT))
	{
		onShoot.fire();
		shootTimer.reset();
	}
}

void Ship::draw(sf::RenderWindow& window)
{
	if (thrusting)
	{
		sf::Vector2f forward = getForwardVector();
		sf::Vector2f center = shape.getPosition();

		// orient opposite to the ship's forward vector
		thrusterShape.setRotation(rotation + sf::degrees(180.f));

		// start from ship center
		thrusterShape.setPosition(center);

		//vary size slightly so it seems like it's animated
		thrusterShape.setSize({ BrightRandom::range(THRUSTER_LENGTH, THRUSTER_LENGTH + 5.0f), THRUSTER_THICKNESS });

		window.draw(thrusterShape);
	}
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
