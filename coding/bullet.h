#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Bullet
{
public:
    Bullet(Texture& tex);
    ~Bullet();
    void update(float dt);
    void render(RenderTarget& window);
    FloatRect getBounds() const;

    // Public accessors
    Sprite& getShape(); // Method to access the private `shape` sprite
    void setVelocity(float x, float y); // Method to set velocity
    Vector2f getVelocity() const; // Method to get velocity
     Sprite shape;
     void setPosition(float x, float y);

private:
   
    Vector2f velocity; // Added to store bullet velocity
};
