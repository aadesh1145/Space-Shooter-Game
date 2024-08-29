// enemy.h
#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include <vector>
#include "explosion.h"

class Enemy
{
protected:
    sf::Sprite enemy;
    int hp;
      int hpMax;
    sf::Color originalColor;
    sf::Clock hitClock;
    bool isHit;

public:

    static sf::Texture enemyTex;
    static std::vector<Enemy> enemies;

    Enemy(sf::Texture& texture, sf::Vector2u windowSize);
    ~Enemy();

    void update(float dt);
    void render(sf::RenderTarget& window);
    sf::Vector2f getPosition();
    sf::FloatRect getBounds();
    int getHp() const;
    void takeDamage(int damage);

    static void spawnEnemy(sf::Vector2u windowSize);
    static void updateEnemies(float dt, sf::Vector2u windowSize, std::vector<Explosion>& explosions, const sf::Texture& explosionTexture);
    static void renderEnemies(sf::RenderTarget& window);
};
