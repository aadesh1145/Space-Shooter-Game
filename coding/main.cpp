#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menu.hpp"
#include "game.h"
#include "sound.h"
#include "globals.h"

bool soundPlaying = true;

int main()
{
   sf::RenderWindow window(sf::VideoMode(1920, 1080), "SPACE SHOOTER", sf::Style::Close | sf::Style::Titlebar);

   Menu menu(window.getSize().x, window.getSize().y);

    if (!menu.loadBackground("C:\\smfl-project\\sprite\\img.jpg")) {
        std::cout << "Failed to load background image!" << std::endl;
        return -1;
    }

    atexit(Game::cleanup);

    sf::Sound clickSound;
    sf::Music bgMusic;



    bgMusic.setLoop(true);
    bgMusic.play();

    bool gameStarted = false;
    Game* game = nullptr;
    Clock clock;
while (window.isOpen())
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
        }
        else if (event.type == Event::TextEntered)
        {
            menu.handleTextInput(event.text.unicode); // Pass the Unicode character
            std::cout << "TextEntered event: " << event.text.unicode << std::endl;
        }
        else if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Up)
            {
                menu.MoveUp();
            }
            else if (event.key.code == Keyboard::Down)
            {
                menu.MoveDown();
            }
            else if (event.key.code == Keyboard::Enter)
            {
                if (menu.isEnteringName)
                {
                    std::cout << "Enter key pressed while entering name" << std::endl;
                    menu.isEnteringName = false;
                    gameStarted = true;
                    game = Game::getInstance();
                    if (game)
                    {
                        std::cout << "Game instance obtained, starting game..." << std::endl;
                        game->run();
                    }
                    else
                    {
                        std::cout << "Failed to get game instance!" << std::endl;
                    }
                }
            }
        }
        else if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left)
            {
                menu.handleMouseClick(Vector2i(event.mouseButton.x, event.mouseButton.y), window, bgMusic, clickSound);
            }
        }
        else if (event.type == Event::MouseMoved)
        {
            menu.handleMouseHover(Vector2i(event.mouseMove.x, event.mouseMove.y));
        }

    }

    float deltaTime = clock.restart().asSeconds();

    if (!gameStarted)
    {
        menu.update(deltaTime,window);
        window.clear();
        menu.draw(window); // Draw the background and menu elements
        window.display();
    }
    else
    {
        if (game)
        {
            game->update(deltaTime);
            window.clear();
            game->render(); // Call render without arguments
            window.display();

            if (game->isGameOver())
            {
                std::cout << "Game Over detected" << std::endl;
                gameStarted = false;
                Game::cleanup();
                game = nullptr;
            }
        }
    }
}
}