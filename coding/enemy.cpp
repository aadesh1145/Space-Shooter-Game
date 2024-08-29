// enemy.cpp
#include<iostream>
#include "enemy.h"
#include"game.h"
#include"explosion.h"
#include <cstdlib>  // for rand()

using namespace std;
using namespace sf;

// Initialize static members
Texture Enemy::enemyTex;
vector<Enemy> Enemy::enemies;

Enemy::Enemy(Texture& texture, Vector2u windowSize) :isHit(false)
{
    this->hpMax = rand() % 3 + 1;  // Random HP between 1 and 3
    this->hp = this->hpMax;

    this->enemy.setTexture(texture);

    // Check if the texture is set properly
    if (texture.getSize().x == 0 || texture.getSize().y == 0) {
        cout << "Error: Texture is not set properly!" << endl;
    }

    this->enemy.setScale(0.8f, 0.8f);
    this->originalColor = this->enemy.getColor();
    // Debugging texture size
    FloatRect bounds = this->enemy.getGlobalBounds();
    cout << "Enemy texture size: " << bounds.width << " x " << bounds.height << endl;

    float xPos = static_cast<float>(rand() % (windowSize.x - static_cast<int>(bounds.width)));
    float yPos = -bounds.height;
    this->enemy.setPosition(xPos, yPos);

    cout << "Enemy spawned at (" << xPos << ", " << yPos << ")" << endl;
}


Enemy::~Enemy() {}

void Enemy::update(float dt) {
    this->enemy.move(0.f, 80.f * dt);  // Adjust speed as necessary
    
    if (isHit && hitClock.getElapsedTime().asSeconds() > 0.1f) { // Flash duration of 0.1 seconds
        this->enemy.setColor(this->originalColor);
        this->isHit = false;
    }
}

void Enemy::render(RenderTarget& window)
{
    window.draw(this->enemy);
}

Vector2f Enemy::getPosition()
{
    return this->enemy.getPosition();
}

FloatRect Enemy::getBounds()
{
    return this->enemy.getGlobalBounds();
}

int Enemy::getHp() const
{
    return this->hp;
}

void Enemy::takeDamage(int damage) {
    this->hp -= damage;
    this->isHit = true;
    this->enemy.setColor(sf::Color::Red); // Flash red when hit
    this->hitClock.restart(); // Start the clock for the flash duration

    // Apply knockback
    this->enemy.move(0.f, -5.f); // Move the enemy slightly upwards when hit
}

// Static method to spawn a new enemy
void Enemy::spawnEnemy(Vector2u windowSize)
{
    enemies.push_back(Enemy(enemyTex, windowSize));
}

// Static method to update all enemies
void Enemy::updateEnemies(float dt, Vector2u windowSize, std::vector<Explosion>& explosions, const Texture& explosionTexture) {
    for (size_t i = 0; i < enemies.size(); ++i) {
        enemies[i].update(dt);

        if (enemies[i].getPosition().y > windowSize.y || enemies[i].getHp() <= 0) {
            // Create an explosion at the enemy's position
            sf::Vector2f explosionPosition = enemies[i].getPosition();
            explosions.push_back(Explosion(explosionTexture, explosionPosition, 0.25f,0.5f)); // Duration 0.5 seconds

            // Remove the enemy from the list
            enemies.erase(enemies.begin() + i);
            --i;

            // Increment the score
            Game::getInstance()->incrementScore();
        }
    }
}

// Static method to render all enemies
void Enemy::renderEnemies(RenderTarget& window) {
    for (auto& enemy : enemies) {
        enemy.render(window);
    }

}
