//explosion.h
#pragma once
#include <SFML/Graphics.hpp>

class Explosion {
private:
    sf::Sprite sprite;
     sf::Vector2f position; // Add this line
    float duration;     // Duration of the explosion in seconds
    float fadeDuration;
    float elapsedTime;  // Time since the explosion started

public:
    Explosion(const sf::Texture& texture, sf::Vector2f position, float duration,float fadeDuration);
    ~Explosion();
    
    void update(float dt);
    void render(sf::RenderTarget& target);
    bool isFinished() const;  // Add this method
};
