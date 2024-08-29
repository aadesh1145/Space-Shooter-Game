//background.h
#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
using namespace sf;

class Background
{
private:
    Sprite sprite;
    Texture texture;

public:
    Background(const std::string& textureFilePath,Vector2u windowSize);
    ~Background();
    void render(RenderTarget& window);
};
