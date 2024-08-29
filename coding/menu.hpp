#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <array>
#include "sound.h"
#include "globals.h"

enum class MenuState
{
    MAIN_MENU,
    ABOUT_PAGE,
    STORY_PAGE,
    OPTIONS_PAGE,
    PLAY
};

class Menu
{
public:
    Menu(float width, float height);
    ~Menu();

    void update(float deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    void handleMouseClick(sf::Vector2i mousePosition, sf::RenderWindow &window, sf::Music &bgmusic, sf::Sound &clickSound);
    void handleMouseHover(sf::Vector2i mousePosition);
    void handleTextInput(sf::Uint32 unicode);
    bool loadBackground(const std::string& filename);

    void setselected(int n);
    bool isEnteringName;

    std::array<sf::Text, 1> aboutMenu;  // Adjust size if you add more buttons
    std::array<sf::Text, 1> storyMenu;  // Adjust size if you add more buttons


private:
    int selected;
    SoundLoader soundloader;
    sf::Font font;
    sf::Font font1;
    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;
    sf::Music menuMusic;
    sf::Text mainmenu[5];
    sf::Text heading;
    sf::Text optionsMenu[3];
    sf::Text playerNameInput;
    sf::RectangleShape textBox;
    sf::Text aboutText;
    sf::Text storyText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    bool showAbout;
    bool musicPlaying;
    float wordTimer;
    float wordDelay;
    size_t currentWordIndex;
    size_t currentStoryWordIndex;
    std::string displayedText;
    std::string displaystoryText;
    std::string inputString;
    std::vector<std::string> aboutWords;
    std::vector<std::string> storyWords;
    MenuState currentState;

    sf::String wrapText(const std::string& text, float width, const sf::Font& font, unsigned int characterSize);
    void updateOptionsText();
};
