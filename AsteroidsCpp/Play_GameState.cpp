#include "Play_GameState.h"
#include "GameConstants.h"
#include "BrightLib/CollisionManager.h"
#include "Services.h"
#include "BrightLib/BrightRandom.h"

Play_GameState::Play_GameState() : BrightState(typeid(Play_GameState)),
    ship(50.0f, 50.0f),
    asteroidSpawner(20, 2.3f),
    bullets(20),
    playerScore(0),
    restartGameTimer(0.3f)
{

    //UI
    scoreView = Services::Views().addView<ScoreView>();

    //hook up events
    ship.onShoot.subscribe([this]() { handlePlayerShoot(); });
    asteroidSpawner.onSpawn.subscribe([this](Asteroid& asteroid) { handleAsteroidSpawn(asteroid); });
}

void Play_GameState::enter()
{
    float windowCenterX = GameConstants::WINDOW_WIDTH / 2.0f;
    float windowCenterY = GameConstants::WINDOW_HEIGHT / 2.0f;

    ship.setPosition(windowCenterX, windowCenterY);

    asteroidSpawner.position = { -5.0f, -5.0f};
    //asteroidSpawner.position = { windowCenterX / 2.0f, windowCenterY / 2.0f };
    //asteroid.setPosition(windowCenterX/2.0f, windowCenterY/2.0f);

    restartGameTimer.reset();

    scoreView->setScore(0);
    scoreView->setHighscore(Services::Highscore().getHighscore());
}

std::type_index Play_GameState::update(float dt)
{
    if (subState == GameState::Playing)
    {
        ship.update(dt);
        asteroidSpawner.update(dt);

        //todo: temporary, remove it
        for (Asteroid& asteroid : asteroidSpawner.pool.getAll())
        {
            if (!asteroid.active)
            {
                continue;
            }
            asteroid.update(dt);
        }

        //todo: temporary, remove it
        for (Bullet& bullet : bullets.getAll())
        {
            if (!bullet.active)
            {
                continue;
            }
            bullet.update(dt);
        }

        //collision between asteroids and ship
        for (Asteroid& asteroid : asteroidSpawner.pool.getAll())
        {
            if (!asteroid.active)
            {
                continue;
            }

            if (CollisionManager::checkOverlap(asteroid.shape, ship.shape))
            {
                subState = GameState::PlayerDead;
            }
        }
        

        /*
        //check collision with body
        if (snake.pieces.size() > 5)
        {
            for (size_t i = 1; i < snake.pieces.size(); ++i)
            {
                SnakePiece piece = snake.pieces[i];
                float dx = snake.getHead().position.x - snake.pieces[i].position.x;
                float dy = snake.getHead().position.y - snake.pieces[i].position.y;
                float distSq = dx * dx + dy * dy;

                if (distSq < GameConstants::SNAKE_PIECE_SIZE * GameConstants::SNAKE_PIECE_SIZE * 0.25f)
                {
                    subState = GameState::PlayerDied;
                }
            }
        }
        */

    }
    else if (subState == GameState::PlayerDead)
    {
        //playsfx?
        restartGameTimer.reset();
        subState = GameState::RestartingGame;
    }
    else if (subState == GameState::RestartingGame)
    {
        if (restartGameTimer.update(dt))
        {
            //save
            Services::Highscore().updateHighscore(playerScore);
            playerScore = 0;
            scoreView->setScore(playerScore);
            scoreView->setHighscore(Services::Highscore().getHighscore());
            Services::Highscore().save();

            //reset
            asteroidSpawner.despawnAll();
            //asteroid.setPosition(getRandomFreePosition(ship));
            ship.resetPosition();

            subState = GameState::Playing;
        }
    }

	return getTypeId();
}

void Play_GameState::draw(sf::RenderWindow& window)
{
    ship.draw(window);

    //todo: temporary, remove it
    for (Asteroid& asteroid : asteroidSpawner.pool.getAll())
    {
        asteroid.draw(window);
    }

    //todo: temporary, remove it
    for (Bullet& bullet : bullets.getAll())
    {
        bullet.draw(window);
    }

    scoreView->draw(window);
}

void Play_GameState::handlePlayerShoot()
{
    Bullet& bullet = bullets.getAvailable();
    bullet.setPosition(ship.getFrontPoint());
    bullet.direction = ship.getForwardVector();
    bullet.active = true;
}

void Play_GameState::handleAsteroidSpawn(Asteroid& asteroid)
{
    //set position
    asteroid.position = { asteroidSpawner.position.x, asteroidSpawner.position.y };

    //set direction
    sf::Vector2f dir = sf::Vector2f{GameConstants::WINDOW_WIDTH / 2.0f, GameConstants::WINDOW_HEIGHT / 2.0f} - asteroid.position;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    sf::Vector2f normalizedDirection = (len != 0) ? dir / len : sf::Vector2f{ 0.f, 0.f };
    asteroid.direction = normalizedDirection;

    //set size
    float small = 20.0f;
    float medium = 30.0f;
    float large = 50.0f;
    float range = BrightRandom::range(0, 100);
    float size = range < 50 ? small : medium;
    size = range < 80 ? medium : large;
    asteroid.shape.setRadius(size);

    //set speed
    //asteroid.setRandomSpeed();
}   

sf::Vector2f Play_GameState::getRandomFreePosition(const Ship& ship)
{
    sf::Vector2f pos;
    bool collision;

    int gridWidth = GameConstants::WINDOW_WIDTH / GameConstants::PLAYER_SHIP_SIZE;
    int gridHeight = GameConstants::WINDOW_HEIGHT / GameConstants::PLAYER_SHIP_SIZE;

    const float tolernace = 0.05f;

    do 
    {
        collision = false;
        int cellX = rand() % gridWidth;
        int cellY = rand() % gridHeight;
        pos.x = cellX * GameConstants::PLAYER_SHIP_SIZE;
        pos.y = cellY * GameConstants::PLAYER_SHIP_SIZE;

        float distanceX = ship.position.x - pos.x;
        float distanceY = ship.position.y - pos.y;
        if (distanceX < 0) distanceX *= -1;
        if (distanceY < 0) distanceY *= -1;

        if (distanceX < tolernace && distanceY < tolernace)
        {
            collision = true;
            break;
        }
        
    } while (collision);

    return pos;
}