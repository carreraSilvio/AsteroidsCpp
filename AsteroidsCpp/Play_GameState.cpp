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
    Services::Views().openView<ScoreView>();
}

void Play_GameState::exit()
{
    Services::Views().openView<ScoreView>();
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
                increaseScore(asteroid.size);

                if (!asteroid.canBreak())
                {
                    continue;
                }

                Asteroid::Size newAsteroidSize = asteroid.size == Asteroid::Size::Large ?
                    Asteroid::Size::Medium :
                    Asteroid::Size::Small;
                int spawnAmount = BrightRandom::range(2,3);
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
            setScore(0);
            scoreView->setHighscore(Services::Highscore().getHighscore());
            Services::Highscore().save();

            //reset
            asteroidSpawner.despawnAll();
            bullets.deactivateAll();
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
}

void Play_GameState::increaseScore(Asteroid::Size asteroidSize)
{
    int asteroidScore = 0;
    switch (asteroidSize)
    {
        case Asteroid::Size::Large:  asteroidScore = 20;  break;
        case Asteroid::Size::Medium: asteroidScore = 50;  break;
        case Asteroid::Size::Small:  asteroidScore = 100; break;
        default:                     asteroidScore = 0;   break;
    }

    setScore(playerScore + asteroidScore);
}


void Play_GameState::setScore(int newScore)
{
    playerScore = newScore;
    scoreView->setScore(playerScore);
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