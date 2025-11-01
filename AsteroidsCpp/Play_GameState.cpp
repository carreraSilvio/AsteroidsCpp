#include "Play_GameState.h"
#include "GameConstants.h"
#include "BrightLib/CollisionManager.h"
#include "Services.h"

Play_GameState::Play_GameState() : BrightState(typeid(Play_GameState)),
    ship(50.0f, 50.0f),
    fruit(50.0f, 0.0f),
    bullet(0.0f, 0.0f)
{
    bullet.active = false;

    //UI
    scoreView = Services::Views().addView<ScoreView>();

    //hook up events
    ship.onShoot.subscribe([this]() { handlePlayerShoot(); });
}

void Play_GameState::enter()
{
    float windowCenterX = GameConstants::WINDOW_WIDTH / 2.0f;
    float windowCenterY = GameConstants::WINDOW_HEIGHT / 2.0f;

    ship.setPosition(windowCenterX, windowCenterY);
    fruit.setPosition(windowCenterX, windowCenterY - 50.0f);

    playerAteFruitTimer = 0.0f;
    playerDiedTimer = 0.0f;

    scoreView->setScore(0);
    scoreView->setHighscore(Services::Highscore().getHighscore());
}

std::type_index Play_GameState::update(float dt)
{
    if (subState == GameState::Playing)
    {
        ship.update(dt);
        fruit.update(dt);
        bullet.update(dt);

        /*
        //check collision with fruit
        sf::Vector2f circleCenter = fruit.shape.getPosition() + sf::Vector2f(fruit.shape.getRadius(), fruit.shape.getRadius());
        if (fruit.active && CollisionManager::checkCollisionCircleRect(circleCenter, fruit.shape.getRadius(), snake.getHead().shape.getGlobalBounds()))
        {
            subState = GameState::PlayerAteFruit;
        }

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
    else if (subState == GameState::PlayerAteFruit)
    {
        playerScore++;
        scoreView->setScore(playerScore);

        playerAteFruitTimer = 0.0f;
        subState = GameState::DelayAfterEatingFruit;
    }
    else if (subState == GameState::DelayAfterEatingFruit)
    {
        playerAteFruitTimer += dt;
        if (playerAteFruitTimer > 0.1f)
        {
            fruit.setPosition(getRandomFreePosition(ship));

            subState = GameState::Playing;
        }
    }
    else if (subState == GameState::PlayerDied)
    {

        playerDiedTimer = 0.0f;
        //playsfx?
        subState = GameState::DelayAfterPlayerDied;
    }
    else if (subState == GameState::DelayAfterPlayerDied)
    {
        playerDiedTimer += dt;
        if (playerDiedTimer > 0.2f)
        {
            Services::Highscore().tryUpdateHighscore(playerScore);
            playerScore = 0;
            scoreView->setScore(playerScore);
            scoreView->setHighscore(Services::Highscore().getHighscore());
            Services::Highscore().save();

            fruit.setPosition(getRandomFreePosition(ship));
            ship.resetPosition();

            subState = GameState::Playing;
        }
    }

	return getTypeId();
}

void Play_GameState::draw(sf::RenderWindow& window)
{
    ship.draw(window);
    fruit.draw(window);
    bullet.draw(window);

    scoreView->draw(window);
}

void Play_GameState::handlePlayerShoot()
{

    bullet.setPosition(ship.getFrontPoint());
    bullet.direction = ship.getForwardVector();
    bullet.active = true;
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