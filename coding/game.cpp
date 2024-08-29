//game.cpp
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "bossEnemy.h"
#include "globals.h"
#include "file.h"
#include <fstream>
#include <iostream>
#include<vector>

using namespace std;
sf::RenderWindow* Game::window = nullptr;
Game* Game::instance = nullptr;
sf::Texture Game::bulletTex; 
sf::Texture Game::enemyTex;
sf::Texture Game::explosionTex;

void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SPACE SHOOTER", sf::Style::Close | sf::Style::Titlebar);
}
void Game::initBackground()
{
    this->background = new Background("C:\\smfl-project\\sprite\\spacebg.jpeg", window->getSize());
    backgroundIsLoaded = true;
}

void Game::initTexture() {
    if (!playerTexture.loadFromFile("C:\\smfl-project\\sprite\\Player2.png")) {
        cout << "Unable to load image" << endl;
    }
        if (!explosionTex.loadFromFile("C:\\smfl-project\\sprite\\explode.png")) {
        cout << "Failed to load explosion texture!" << endl;
    }
}

void Game::initBullet()
{
    if (!bulletTex.loadFromFile("C:\\smfl-project\\sprite\\Projectile1.png")) {
        cout << "Unable to load bullet" << endl;
    }
}

void Game::initEnemy()
{
    if (!Enemy::enemyTex.loadFromFile("C:\\smfl-project\\sprite\\Enemy1.png")) {
        cout << "Error: Could not load enemy texture!" << endl;
    }
}
void Game::initBossEnemy()
{
    if(!bossEnemyTex.loadFromFile("C:\\smfl-project\\sprite\\Player1.png"))
    {
        cout << "Error: Could not load BossEnemy texture!" << endl; 
    }
}

void Game::initPlayer() {
    this->player = new Player(this->playerTexture, 960, 900);
}

void Game::spwanEnemy() {
    cout << "Spawning enemy..." << endl;
    Enemy::spawnEnemy(window->getSize());
    cout << "Enemies count: " << Enemy::enemies.size() << endl;
}

void Game::updateEnemies(float dt) {
    for (size_t i = 0; i < Enemy::enemies.size(); ++i) {
        Enemy::enemies[i].update(dt);

        bool removeEnemy = false;

        // Check if the enemy reaches or crosses the left boundary (x = 0)
        if (Enemy::enemies[i].getPosition().x <= 0) {
            this->player->takeDamage(1); // Reduce player's HP by 1
            removeEnemy = true;
        }
        // Check if the enemy reaches or crosses the bottom boundary (y >= screen height)
        else if (Enemy::enemies[i].getPosition().y >= Game::window->getSize().y) {
            this->player->takeDamage(1); // Reduce player's HP by 1
            removeEnemy = true;
        }

        if (removeEnemy) {
            // Remove the enemy from the list
            Enemy::enemies.erase(Enemy::enemies.begin() + i);
            --i; // Adjust index since we removed an element
        }
    }
}

void Game::updateExplosions(float dt) {
    for (size_t i = 0; i < explosions.size(); ++i) {
        explosions[i].update(dt);
        if (explosions[i].isFinished()) {
            explosions.erase(explosions.begin() + i);
            --i;  // Adjust index since we removed an element
        }
    }
}

void Game::renderEnemies()
{
    Enemy::renderEnemies(*window);
}

Game::Game() :soundLoader(), enemySpawnCooldown(2.0f), lastEnemySpawnTime(0.0f), backgroundIsLoaded(false), gameOver(false),victory(false) ,score(0),bossSpawned(false),newHighScore(false){
    initWindow();
    this->initTexture();
    this->initBackground();
    this->initBullet();
    this->initPlayer();
    this->initEnemy();
    this->initBossEnemy();

    highScore = fileHandler.readHighScore("highscore.txt");

    if(!font.loadFromFile("C:\\smfl-project\\fonts\\venus rising rg.ttf"))
    {
        cout << "Failed to load font!" <<endl;
    }

    initScore();

    if (!explosionTexture.loadFromFile("C:\\smfl-project\\sprite\\explode.png")) {
        cout << "Failed to load explosion texture!" << endl;
    }

    // Initialize high score text
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(50);
    highScoreText.setFillColor(sf::Color(255, 215, 0)); // Gold color for high score
    highScoreText.setPosition(10.f, 60.f);
    highScoreText.setString("High Score: " + std::to_string(highScore));

    // Initialize "New High Score" text
    newHighScoreText.setFont(font);
    newHighScoreText.setCharacterSize(50);
    newHighScoreText.setFillColor(sf::Color::Yellow);
    newHighScoreText.setPosition(window->getSize().x / 2 - 400.f, window->getSize().y / 2 - 100.f); // Centered
    newHighScoreText.setString("New High Score!");

    
}

Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->background;
}

void Game::updateEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}


void Game::update(float dt) {
    player->update(dt);

    if (gameOver) {
        handleGameOver();
        return;
    }
        if (victory) {
        handleVictory();  // Handle the victory scenario
        return;
    }

    this->deltaTime = dt; // Use dt directly here
    if (this->player != nullptr) {
        this->player->update(deltaTime);
        if (this->player->isDead()) {
            sf::Vector2f explosionPosition = this->player->getPosition();
            explosions.push_back(Explosion(explosionTexture, explosionPosition, 0.25f, 0.5f));
            this->setGameOver(true);
        }
    }

    lastEnemySpawnTime += deltaTime;
    if (lastEnemySpawnTime >= enemySpawnCooldown) {
        this->spwanEnemy();
        lastEnemySpawnTime = 0.0f;
    }

    this->updateEnemies(deltaTime);
    updateBullets(deltaTime);

    // Spawn boss if score is greater than 20 and the boss hasn't been spawned yet
    if (score > 20 && !bossSpawned) {
        BossEnemy::spawnBossEnemy(window->getSize(), bossEnemyTex);
        bossSpawned = true; // Set flag to true so that boss is not spawned again
    }

    // Update boss enemies
    BossEnemy::updateBossEnemies(deltaTime);
    for (auto& boss : BossEnemy::bossEnemies) {
    if (boss.getPosition().y + boss.getBounds().height >= window->getSize().y) {
            this->setGameOver(true);  // End the game if the boss reaches the bottom
            break;
        }
    }

    // Check for collisions between bullets and enemies
    for (size_t i = 0; i < this->player->getBullets().size(); ++i) {
        for (size_t j = 0; j < Enemy::enemies.size(); ++j) {
            if (this->player->getBullets()[i].getBounds().intersects(Enemy::enemies[j].getBounds())) {
                Enemy::enemies[j].takeDamage(1);
                this->player->getBullets().erase(this->player->getBullets().begin() + i);
                --i;
                if (Enemy::enemies[j].getHp() <= 0) {
                    soundLoader.PlaySound(EnemyDead);
                    sf::Vector2f explosionPosition = Enemy::enemies[j].getPosition();
                    explosions.push_back(Explosion(explosionTexture, explosionPosition, 0.25f, 0.5f));
                    Game::getInstance()->incrementScore();
                    Enemy::enemies.erase(Enemy::enemies.begin() + j);
                    --j;
                    
                }
                break;
            }
        }
    }

    // Check for collisions between player's bullets and boss enemies
    for (size_t i = 0; i < this->player->getBullets().size(); ++i) {
        for (size_t j = 0; j < BossEnemy::bossEnemies.size(); ++j) {
            if (this->player->getBullets()[i].getBounds().intersects(BossEnemy::bossEnemies[j].getBounds())) {
                BossEnemy::bossEnemies[j].decreaseHP(1);  // Reduce boss HP by 1
                this->player->getBullets().erase(this->player->getBullets().begin() + i);
                --i;
                if (BossEnemy::bossEnemies[j].getHP() <= 0) {  // Only remove if HP is 0
                    sf::Vector2f explosionPosition = BossEnemy::bossEnemies[j].getPosition();
                    explosions.push_back(Explosion(explosionTexture, explosionPosition, 0.25f, 0.5f));
                    BossEnemy::bossEnemies.erase(BossEnemy::bossEnemies.begin() + j);
                    --j;

                    victory = true;
                }
                break;

            }
        }
    }

    this->updateExplosions(deltaTime);
    this->updateEvents();

        // Hide new high score text after 1 second
    if (newHighScore && newHighScoreClock.getElapsedTime().asSeconds() > 1.0f) {
        newHighScore = false;
    }
}

void Game::run()
{
    sf::Clock clock;
    std::cout << "Game run method called" << std::endl;
    while (window->isOpen())
    {
        float dt = clock.restart().asSeconds();

        // Process input, update game state, render
        update(dt);
        render();
    }
}
void Game::render() {
    window->clear(); // Clear the window first

    if (backgroundIsLoaded) {
        this->background->render(*this->window);
    }
    this->player->render(*this->window);
    this->renderEnemies();

    for (auto& explosion : explosions) {
        explosion.render(*window);
    }

    // Render bullets
    for (auto& bullet : bullets) {
        bullet.render(*window);
    }

    // Update the score text
    scoreText.setString("Score: " + std::to_string(score)); // This updates the displayed score
    // Render the score
    window->draw(scoreText);

    window->draw(highScoreText);

    // Draw the new high score text if applicable
    if (newHighScore) {
        
        window->draw(newHighScoreText); // Draw the new high score text
        // Hide new high score text after 1 second
        if (newHighScoreClock.getElapsedTime().asSeconds() > 1.0f) {
            newHighScore = false; // Reset the flag
        }
    }

    if (isGameOver()) {
        // Game Over text
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("Game Over");
        gameOverText.setCharacterSize(100);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(
            window->getSize().x / 2 - gameOverText.getGlobalBounds().width / 2,
            window->getSize().y / 2 - gameOverText.getGlobalBounds().height / 2
        );

        window->draw(gameOverText);

        // Space to Continue text
        sf::Text spaceToContinue;
        spaceToContinue.setFont(font);
        spaceToContinue.setString("Press Space for New Game");
        spaceToContinue.setCharacterSize(50); // Smaller size for instructions
        spaceToContinue.setFillColor(sf::Color::Green);
        
        // Position it below the Game Over text with some padding
        float padding = 20.0f;
        spaceToContinue.setPosition(
            window->getSize().x / 2 - spaceToContinue.getGlobalBounds().width / 2,
            gameOverText.getPosition().y + gameOverText.getGlobalBounds().height + padding
        );

        window->draw(spaceToContinue);
    }

    if (isVictory()) {
        // Victory text
        victoryText.setFont(font);
        victoryText.setString("Victory!");
        victoryText.setCharacterSize(100);
        victoryText.setFillColor(sf::Color::Green);
        victoryText.setPosition(
            window->getSize().x / 2 - victoryText.getGlobalBounds().width / 2,
            window->getSize().y / 2 - victoryText.getGlobalBounds().height / 2
        );

        window->draw(victoryText);

        // Space to Continue text
        sf::Text spaceToContinue;
        spaceToContinue.setFont(font);
        spaceToContinue.setString("Press Space for New Game");
        spaceToContinue.setCharacterSize(50); // Smaller size for instructions
        spaceToContinue.setFillColor(sf::Color::White);

        // Position it below the Victory text with some padding
        float padding = 20.0f;
        spaceToContinue.setPosition(
            window->getSize().x / 2 - spaceToContinue.getGlobalBounds().width / 2,
            victoryText.getPosition().y + victoryText.getGlobalBounds().height + padding
        );

        window->draw(spaceToContinue);
    }
    
    // Render boss enemies
    BossEnemy::renderBossEnemies(*window);

    window->display();
}

Game* Game::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Game();
    }
    return instance;
}

void Game::cleanup()
{
    delete instance;
    instance = nullptr;
}

void Game::setGameOver(bool status)
{
    this->gameOver = status;
}
void Game::handleGameOver() {
    Event event;
    while (window->pollEvent(event)) {
        if (event.type == Event::Closed) {
            window->close();
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
            resetGame(); // Reset the game when space is pressed
        }
    }
}
void Game::resetGame()
{
    gameOver = false;
    victory = false;
    newHighScore=false;  // Reset victory flag
    player->reset(); // Ensure Player has a reset method that reinitializes player state
    Enemy::enemies.clear(); // Clear all enemies
    explosions.clear(); // Clear all explosions

    lastEnemySpawnTime = 0.0f;
    score = 0; // Reset the enemy spawn timer
    bossSpawned = false;
}


void Game::initScore()
{
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color (Color::Yellow));
    scoreText.setPosition(10.f,10.f);
}

void Game::incrementScore() {
    score++;
    std::cout << "Score incremented: " << score << std::endl;

    if (score > highScore) {
        highScore = score;
        newHighScore = true; // Set flag to true
        newHighScoreClock.restart(); // Restart the clock
        fileHandler.writeHighScore("C:\\smfl-project\\highscore.txt", highScore); // Save the new high score to the file
    }
}

std::vector<Bullet>& Game::getBullets() {
    return bullets;
}

void Game::updateBullets(float dt) {
    for (size_t i = 0; i < bullets.size(); ++i) {
        bullets[i].update(dt);

        // Remove bullets off-screen
        if (bullets[i].getBounds().top + bullets[i].getBounds().height < 0) {
            bullets.erase(bullets.begin() + i);
            --i;
        }
    }
}
sf::Texture& Game::getExplosionTexture() {
    return explosionTex; // Return the static texture
}

void Game::handleVictory() {
    Event event;
    while (window->pollEvent(event)) {
        if (event.type == Event::Closed) {
            window->close();
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
            resetGame(); // Reset the game when space is pressed
        }
    }
}
bool Game::isGameOver() const {
    return this->gameOver; // Return the actual game over status
}


bool Game::isVictory() const {
    return victory;
}
