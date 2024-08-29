#pragma once
#include "SFML/Graphics.hpp"
#include "enemy.h"
#include "explosion.h"
#include <vector>

class BossEnemy : public Enemy {
public:
    BossEnemy(sf::Texture& texture, sf::Vector2u windowSize);
    ~BossEnemy();
    
    static std::vector<Explosion> explosions;
    static void spawnBossEnemy(sf::Vector2u windowSize, sf::Texture& texture);
    static void renderBossEnemies(sf::RenderTarget& window);
    static void updateBossEnemies(float dt);

    void decreaseHP(int amount);
    int getHP() const;

    static std::vector<BossEnemy> bossEnemies;

    bool operator==(const BossEnemy& other) const;

protected:
    sf::Color originalColor;
    sf::Clock hitClock;
    bool isHit;
private:
    int hp;
};
