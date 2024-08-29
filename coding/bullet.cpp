#include "bullet.h"

Bullet::Bullet(Texture& texture)
{
    this->shape.setTexture(texture);
    this->shape.setScale(0.25f, 0.25f);
    this->velocity = Vector2f(0.f, 0.f); // Initialize velocity
}

Bullet::~Bullet() {}

void Bullet::update(float dt) {
    this->shape.move(this->velocity * dt); // Move using velocity
}

void Bullet::render(RenderTarget& window)
{
    window.draw(this->shape);
}

FloatRect Bullet::getBounds() const
{
    return this->shape.getGlobalBounds();
}

Sprite& Bullet::getShape() {
    return this->shape;
}

void Bullet::setVelocity(float x, float y) {
    this->velocity = Vector2f(x, y);
}

Vector2f Bullet::getVelocity() const {
    return this->velocity;
}
void Bullet::setPosition(float x, float y) {
    this->shape.setPosition(x, y);
}
