#pragma once
#include "SFML/Graphics.hpp"
#include "bullet.h"
#include "explosion.h"
#include <vector>

using namespace sf;
using namespace std;

class Player
{
public:
    Player(Texture& texture, float posX, float posY);
    ~Player();

    void update(float dt);
    void move(sf::Vector2f direction, float dt);
    void render(sf::RenderTarget& window);
    void shoot();
    vector<Bullet>& getBullets();
    vector<Explosion>& getExplosions();
    void takeDamage(int damage);
    void reset();
    bool isDead() const;
    sf::Vector2f getPosition() const;
     sf::FloatRect getBounds() const; // Method to get the bounds of the player
    void decreaseHP(int amount);
    int getHP() const;

private:
    void initSprite();

    Texture texture;
    Sprite sprite;
    float speed;
    float shootCooldown;
    float lastShotTime;
    float damping;
    Vector2f velocity;
    int hp;
    int hpMax;
    bool soundPlaying;
    vector<Bullet> bullets;
    vector<Explosion> explosions;
};
