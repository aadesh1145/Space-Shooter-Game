#include "player.h"
#include "game.h"
#include "bullet.h"
#include "bossEnemy.h"
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;

void Player::initSprite()
{
    this->sprite.setTexture(this->texture);
}

Player::Player(Texture& texture, float posX, float posY)
    : shootCooldown(0.3f), // Set cooldown to 0.15 seconds
      lastShotTime(0.0f), damping(0.95f),hp(10) // Initialize last shot time to 0
{
    this->hpMax = 5;
    this->hp = hpMax;
    this->texture = texture;
    this->initSprite();
    this->sprite.setPosition(posX, posY);
    this->sprite.setScale(0.3, 0.3);
    this->velocity = sf::Vector2f(0.f, 0.f);
    this->speed = 200.f; // Set default speed value
}

Player::~Player() {}

void Player::update(float dt)
{
    // Apply damping
    velocity *= damping;

    sprite.move(velocity * dt);

    if (Keyboard::isKeyPressed(Keyboard::Key::Right))
    {
        this->sprite.move(1 * speed * dt, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::Left))
    {
        this->sprite.move(-1 * speed * dt, 0);
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::D))
    {
        this->sprite.move(1 * speed * dt, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::A))
    {
        this->sprite.move(-1 * speed * dt, 0);
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::S))
    {
        this->shoot();
    }

    // Update cooldown timer
    lastShotTime += dt;

    // Check for boundary collisions
    if (this->sprite.getPosition().x <= 0) {
        this->sprite.setPosition(0.f, this->sprite.getPosition().y);
    }
    else if (this->sprite.getPosition().x + this->sprite.getGlobalBounds().width >= Game::window->getSize().x) {
        this->sprite.setPosition(Game::window->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getPosition().y);
    }

    // New Boundary Checks
    if (this->sprite.getPosition().y <= 0) {
        this->sprite.setPosition(this->sprite.getPosition().x, 0.f);
    }
    else if (this->sprite.getPosition().y + this->sprite.getGlobalBounds().height >= Game::window->getSize().y) {
        this->sprite.setPosition(this->sprite.getPosition().x, Game::window->getSize().y - this->sprite.getGlobalBounds().height);
    }

    // Update bullets
    for (size_t i = 0; i < this->bullets.size(); i++) {
        this->bullets[i].update(dt);

        // Remove bullet if it moves out of bounds
        if (this->bullets[i].getShape().getPosition().y < 0) {
            this->bullets.erase(this->bullets.begin() + i);
            --i; // Adjust index since we removed an element
        }
    }
}

void Player::move(sf::Vector2f direction, float dt)
{
    // Normalize the direction and scale it by speed and delta time
    if (direction.x != 0 || direction.y != 0) {
        direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y); // Normalize direction
        velocity += direction * speed * dt;
    }
}

void Player::render(sf::RenderTarget& window)
{
    window.draw(this->sprite);

    for (auto& bullet : this->bullets)
    {
        window.draw(bullet.getShape());
    }

    for (auto& explosion : this->explosions)
    {
        explosion.render(window);
    }
}

void Player::shoot()
{
    Game::getInstance()->soundLoader.PlaySound(Shoot);

    // Check if cooldown period has passed
    if (lastShotTime >= shootCooldown)
    {
        Bullet newBullet(Game::getInstance()->getBulletTexture());

        newBullet.getShape().setPosition(
            this->sprite.getPosition().x + (this->sprite.getGlobalBounds().width / 2) - (newBullet.getShape().getGlobalBounds().width / 2),
            this->sprite.getPosition().y - newBullet.getShape().getGlobalBounds().height
        );

        newBullet.setVelocity(0.f, -500.f); // Adjust 500.f to control bullet speed
        this->bullets.push_back(newBullet);

        // Reset cooldown timer
        lastShotTime = 0.0f;
    }
}

vector<Bullet>& Player::getBullets()
{
    return this->bullets;
}

vector<Explosion>& Player::getExplosions() {
    return this->explosions;
}

void Player::takeDamage(int damage)
{
    this->hp -= damage;
    if (this->hp < 0)
    {
        this->hp = 0;
    }
    if (this->hp == 0 )
    {
        cout << "Player is dead!" << endl;
        Game::getInstance()->soundLoader.PlaySound(PlayerDead);
        Game::getInstance()->setGameOver(true);

        // Create explosion effect
        sf::Vector2f explosionPosition = this->sprite.getPosition();
        this->explosions.push_back(Explosion(Game::getExplosionTexture(), explosionPosition, 0.5f, 0.5f)); // Adjust duration and fade duration
    }
}

void Player::reset()
{
    this->hp = 5;
    this->sprite.setPosition(960, 900);
    velocity = sf::Vector2f(0.f, 0.f); // Reset velocity
    this->bullets.clear();
    this->explosions.clear();
}

bool Player::isDead() const {
    return this->hp <= 0;
}

sf::Vector2f Player::getPosition() const {
    return this->sprite.getPosition();
}
void Player::decreaseHP(int amount)
{
    hp-=amount;
    if(hp<0) hp=0;
}

int Player::getHP() const{
    return hp;
}
sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds(); // Returns the bounds of the player sprite
}