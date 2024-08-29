//background.cpp
#include "background.h"
#include <iostream>
#include<vector>
using namespace std;
using namespace sf;

Background::Background(const std::string& textureFilePath, Vector2u windowSize)
{
    if (!texture.loadFromFile(textureFilePath))
    {
        cout << "Error loading background texture from file: " << textureFilePath << endl;
    }
    sprite.setTexture(texture);

    // Get the size of the texture
    FloatRect textureRect = sprite.getGlobalBounds();

    // Calculate scale factors
    float scaleX = windowSize.x / textureRect.width;
    float scaleY = windowSize.y / textureRect.height;

    // Set the scale of the sprite
    sprite.setScale(scaleX, scaleY);
}
void Background::render(RenderTarget& window)
{
    window.draw(sprite);
}
Background::~Background(){}

