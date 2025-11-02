#include "Play_GameState.h"
#include "GameConstants.h"
#include "BrightLib/CollisionManager.h"
#include "Services.h"
#include "BrightLib/BrightRandom.h"

Play_GameState::Play_GameState() : BrightState(typeid(Play_GameState)),
    ship(50.0f, 50.0f),
    asteroidSpawner(50, 1.2f, 0.3f),
    bullets(20),
    playerScore(0),
    restartGameTimer(0.3f)
{
    //UI
    scoreView = Services::Views().addView<ScoreView>();

    //hook up events
    ship.onShoot.subscribe([this]() { handlePlayerShoot(); });
    asteroidSpawner.onSpawn.subscribe([this](Asteroid& asteroid) { handleAsteroidSpawn(asteroid); });

    asteroidSpawner.addSpawnPoint({ -5.0f, -5.0f });//topleft
    asteroidSpawner.addSpawnPoint({ -5.0f, GameConstants::WINDOW_HEIGHT + 5.0f });//botleft
    asteroidSpawner.addSpawnPoint({ GameConstants::WINDOW_WIDTH + 5.0f, -5.0f });//topright
    asteroidSpawner.addSpawnPoint({ GameConstants::WINDOW_WIDTH + 5.0f, GameConstants::WINDOW_HEIGHT + 5.0f });//botright
}

void Play_GameState::enter()
{
    float windowCenterX = GameConstants::WINDOW_WIDTH / 2.0f;
    float windowCenterY = GameConstants::WINDOW_HEIGHT / 2.0f;

    ship.setPosition(windowCenterX, windowCenterY);

    //asteroidSpawner.position = { -5.0f, -5.0f};
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

        //collision between asteroids and bullets
        for (Asteroid& asteroid : asteroidSpawner.pool.getAll())
        {
            if (!asteroid.active)
            {
                continue;
            }

            for (Bullet& bullet : bullets.getAll())
            {
                if (!bullet.active)
                {
                    continue;
                }

                if (!CollisionManager::checkOverlap(asteroid.shape, bullet.shape))
                {
                    continue;
                }
                bullet.active = false;
                asteroid.active = false;

                if (!asteroid.canBreak())
                {
                    continue;
                }

                Asteroid::Size newAsteroidSize = asteroid.size == Asteroid::Size::Large ?
                    Asteroid::Size::Medium :
                    Asteroid::Size::Small;
                int spawnAmount = 3;
                while (spawnAmount > 0)
                {
                    Asteroid& newAsteroid = asteroidSpawner.spawnAt(asteroid.position);
                    newAsteroid.direction = BrightRandom::getRandomNormalizedDirection();
                    newAsteroid.setSize(newAsteroidSize);
                    newAsteroid.lifetimeTimer.reset();

                    spawnAmount--;
                }
            }
        }

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
    bullet.lifetimeTimer.reset();
    bullet.active = true;
}

void Play_GameState::handleAsteroidSpawn(Asteroid& asteroid)
{
    //set direction
    sf::Vector2f dir = sf::Vector2f{GameConstants::WINDOW_WIDTH / 2.0f, GameConstants::WINDOW_HEIGHT / 2.0f} - asteroid.position;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    sf::Vector2f normalizedDirection = (len != 0) ? dir / len : sf::Vector2f{ 0.f, 0.f };
    asteroid.direction = normalizedDirection;

    //set size and speed
    asteroid.setRandomSize();

    //reset timer
    asteroid.lifetimeTimer.reset();
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