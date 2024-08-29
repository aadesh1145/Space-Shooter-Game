//explosin.cpp
#include "explosion.h"
#include<iostream>
Explosion::Explosion(const sf::Texture& texture, sf::Vector2f position, float duration, float fadeDuration)
    : position(position), duration(duration), fadeDuration(fadeDuration), elapsedTime(0.0f)
{
    this->sprite.setTexture(texture);
    this->sprite.setPosition(position);
    this->sprite.setScale(0.35f, 0.35f);  // Adjust this scale if needed
    this->sprite.setColor(sf::Color(255,255,255,255));
    std::cout << "Explosion initialized at position (" << position.x << ", " << position.y << ")" << std::endl;
}


Explosion::~Explosion() {}

void Explosion::update(float dt) {
    this->elapsedTime += dt;

    // Calculate fade factor
    float fadeFactor = std::max(0.f, (fadeDuration - (elapsedTime - duration)) / fadeDuration);
    sf::Color color = this->sprite.getColor();
    color.a = static_cast<sf::Uint8>(255 * fadeFactor);  // Fade out
    this->sprite.setColor(color);
}

void Explosion::render(sf::RenderTarget& target) {
    // Add debugging output

    if (!isFinished()) {
        target.draw(sprite); // Assuming sprite is a member variable
    }
}
bool Explosion::isFinished() const {
    return this->elapsedTime >= this->duration + this->fadeDuration;
}