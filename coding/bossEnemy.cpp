#include "bossEnemy.h"
#include "game.h"
#include "explosion.h"
#include "bullet.h"

std::vector<BossEnemy> BossEnemy::bossEnemies;
std::vector<Explosion> BossEnemy::explosions;

BossEnemy::BossEnemy(sf::Texture& texture, sf::Vector2u windowSize) 
    : Enemy(texture, windowSize), hp(20), isHit(false) {
    this->hpMax = 20;  // More HP than regular enemies
    this->hp = this->hpMax;

    this->enemy.setScale(0.5f, 0.5f);
    this->originalColor = this->enemy.getColor();
}


BossEnemy::~BossEnemy() {}

void BossEnemy::spawnBossEnemy(sf::Vector2u windowSize, sf::Texture& texture) {
    bossEnemies.push_back(BossEnemy(texture, windowSize));
}

void BossEnemy::updateBossEnemies(float dt) {
    for (auto bossIt = bossEnemies.begin(); bossIt != bossEnemies.end();) {
        bossIt->update(dt);

        // Reset the color after hit effect duration
        if (bossIt->isHit && bossIt->hitClock.getElapsedTime().asSeconds() > 0.1f) { // Flash duration of 0.1 seconds
            bossIt->enemy.setColor(bossIt->originalColor);
            bossIt->isHit = false;
        }

        // Check for collision with player's bullets
        auto& bullets = Game::getInstance()->getBullets();
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
            if (bossIt->enemy.getGlobalBounds().intersects(bulletIt->getShape().getGlobalBounds())) {
                bossIt->decreaseHP(1);  // Reduce boss HP by 1
                bulletIt = bullets.erase(bulletIt);  // Remove the bullet on collision
            } else {
                ++bulletIt;  // Move to the next bullet if no collision
            }
        }

        // Check if boss is destroyed
        if (bossIt->getHP() <= 0) {
            sf::Vector2f explosionPosition = bossIt->getPosition();
            explosions.push_back(Explosion(Game::getExplosionTexture(), explosionPosition, 0.50f, 0.75f)); // Access explosionTexture through Game
            bossIt = bossEnemies.erase(bossIt); // Remove and get the next iterator
        } else {
            ++bossIt; // Move to the next boss if not erased
        }
    }
}

void BossEnemy::renderBossEnemies(sf::RenderTarget& window) {
    for (auto& boss : bossEnemies) {
        boss.render(window);
    }
}

void BossEnemy::decreaseHP(int amount) {
    hp -= amount;
    if (hp < 0) {
        hp = 0;
    }

    // Apply hit effect
    this->isHit = true;
    this->enemy.setColor(sf::Color::Red);  // Flash red when hit
    this->hitClock.restart();  // Start the clock for the flash duration

    // Apply knockback
    this->enemy.move(0.f, -5.f);  // Move the boss slightly upwards when hit
}


int BossEnemy::getHP() const {
    return hp;
}

bool BossEnemy::operator==(const BossEnemy& other) const {
    return this->hp == other.hp && this->enemy.getPosition() == other.enemy.getPosition();
}
