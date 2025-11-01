
///DevNote: No need to instantiate this ever so that is why it's just within a namespace

namespace GameConstants
{
	//inline constexpr avoids multiple definition issues across .cpp files.

	static const unsigned int WINDOW_WIDTH = 960;
	static const unsigned int WINDOW_HEIGHT = 540;
	static constexpr unsigned int HALF_WINDOW_WIDTH() { return WINDOW_WIDTH / 2; }
	static constexpr unsigned int HALF_WINDOW_HEIGHT() { return WINDOW_HEIGHT / 2; }
	static sf::Vector2f WindowHalfSize() {
		return sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
	}

	inline static constexpr float PLAYER_SHIP_SIZE = 20.0f;

	inline static constexpr float BALL_SPEED = 300.0f;


};