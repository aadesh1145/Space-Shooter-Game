#include "menu.hpp"
#include "sound.h"
#include "globals.h"
#include <iostream>
#include <sstream>
Menu::Menu(float width, float height) 
    : showAbout(false), wordTimer(0.0f), wordDelay(0.2f), currentWordIndex(0), currentStoryWordIndex(0), 
      currentState(MenuState::MAIN_MENU), musicPlaying(true),  isEnteringName(false)
{
    // Load resources
    if (!font.loadFromFile("C:\\smfl-project\\fonts\\KnightWarrior-w16n8.otf") ||
        !font1.loadFromFile("C:\\smfl-project\\fonts\\WowDino-G33vP.ttf") ||
        !clickBuffer.loadFromFile("C:\\smfl-project\\SFX\\mixkit-sci-fi-click-900.wav") ||
        !menuMusic.openFromFile("C:\\smfl-project\\SFX\\mus.ogg"))
    {
        std::cerr << "Failed to load resources!" << std::endl;
    }
    
    // Set up sound
    clickSound.setBuffer(clickBuffer);
    menuMusic.play();
    menuMusic.setLoop(true);

    // Initialize text settings
    heading.setFont(font1);
    heading.setFillColor(sf::Color::White);
    heading.setString("SPACE SHOOTER");
    heading.setCharacterSize(100);
    heading.setPosition(sf::Vector2f(620, height / 10));

    // Main menu items
    std::string menuOptions[5] = {"Play", "Options", "Instructions", "About", "Exit"};
    for (int i = 0; i < 5; ++i)
    {
        mainmenu[i].setFont(font);
        mainmenu[i].setFillColor(sf::Color::Red);
        mainmenu[i].setString(menuOptions[i]);
        mainmenu[i].setCharacterSize(50);
        mainmenu[i].setPosition(sf::Vector2f((width / 2) - 100, height / (4) + i * 100));
    }

    // Options menu items
    std::string options[] = {"Mute Music", "Mute Sound", "Back"};
    for (int i = 0; i < 3; ++i)
    {
        optionsMenu[i].setFont(font);
        optionsMenu[i].setFillColor(sf::Color::Red);
        optionsMenu[i].setString(options[i]);
        optionsMenu[i].setCharacterSize(50);
        optionsMenu[i].setPosition(sf::Vector2f((width / 2) - 150, height / (4) + i * 100));
    }

    // Player name input
    playerNameInput.setFont(font);
    playerNameInput.setFillColor(sf::Color::White);
    playerNameInput.setCharacterSize(45);
    playerNameInput.setPosition(sf::Vector2f((width / 2) - 400, height / 2 - 100));
    playerNameInput.setString("Enter Your Name: ");

    // About text
    aboutText.setFont(font);
    aboutText.setFillColor(sf::Color::White);
    aboutText.setCharacterSize(30);
    aboutText.setPosition(100, height / 2.0f - 100);

    // Story text
    storyText.setFont(font);
    storyText.setFillColor(sf::Color::White);
    storyText.setCharacterSize(30);
    storyText.setPosition(100, height / 2.0f - 100);

    // Prepare About text
    std::string fullAboutText = "This is a space shooter game developed by AKNN.\n"
                                "In this game, you'll battle through waves of enemies in space.\n"
                                "Good luck.";
    std::istringstream stream(fullAboutText);
    std::string word;
    while (stream >> word)
    {
        aboutWords.push_back(word);
    }

    // Prepare Story text
    std::string storyContent ="Press A or Left arrow(<-)to go to left side.\n"
                              "Press D or Right arrow(->) to go right.\n"
                              "Press S to shoot bullets.\n"
                              "For every normal enemy you kill you get one point."
                              "If you score more than 20 point Boss Enemy will appear.\n "
                              "If you kill boss enemy you will win.\n"
                              "If 5 enemies touch the below screen boundary or boss enemy touch below screen boundary you will lose.";
    std::string wrappedStoryText = wrapText(storyContent, width - 400, font, storyText.getCharacterSize());
    storyText.setString(wrappedStoryText);
    std::istringstream storyStream(storyContent);
    while (storyStream >> word)
    {
        storyWords.push_back(word);
    }

    selected = -1;
}

Menu::~Menu()
{
}

void Menu::setselected(int n)
{
    selected = n;
}


void Menu::MoveUp()
{
    if (selected - 1 >= 0)
    {
        mainmenu[selected].setFillColor(sf::Color::Red);
        selected--;
        if (selected < 0)
        {
            selected = 4;
        }
        mainmenu[selected].setFillColor(sf::Color::Blue);
    }
}

void Menu::MoveDown()
{
    if (selected + 1 < 5)
    {
        mainmenu[selected].setFillColor(sf::Color::Red);
        selected++;
        if (selected >= 5)
        {
            selected = 0;
        }
        mainmenu[selected].setFillColor(sf::Color::Blue);
    }
}

void Menu::handleMouseClick(sf::Vector2i mousePosition, sf::RenderWindow &window, sf::Music &bgmusic, sf::Sound &clickSound)
{
    if (currentState == MenuState::MAIN_MENU)
    {
        for (int i = 0; i < 5; i++)
        {
            if (mainmenu[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
            {
                selected = i;
                clickSound.play();
                if (mainmenu[i].getString() == "Play")
                {
                    inputString.clear();
                    playerNameInput.setString("Enter Your Name: ");
                    currentState = MenuState::PLAY;
                    isEnteringName = true;
                }
                else if (mainmenu[i].getString() == "Exit")
                {
                    window.close();
                    menuMusic.stop();
                }
                else if (mainmenu[i].getString() == "About")
                {
                    currentState = MenuState::ABOUT_PAGE;
                    showAbout = true;
                    displayedText = "";
                    currentWordIndex = 0;
                    wordTimer = 0.0f;
                }
                else if (mainmenu[i].getString() == "Instructions")
                {
                    currentState = MenuState::STORY_PAGE;
                }
                else if (mainmenu[i].getString() == "Options")
                {
                    currentState = MenuState::OPTIONS_PAGE;
                    updateOptionsText();
                }
                break;
            }
        }
    }
    else if (currentState == MenuState::ABOUT_PAGE || currentState == MenuState::STORY_PAGE)
    {
        // Clicking anywhere returns to the main menu
        if (window.mapPixelToCoords(mousePosition).x >= 0 &&
            window.mapPixelToCoords(mousePosition).x <= window.getSize().x &&
            window.mapPixelToCoords(mousePosition).y >= 0 &&
            window.mapPixelToCoords(mousePosition).y <= window.getSize().y)
        {
            showAbout = false;
            currentState = MenuState::MAIN_MENU;
        }
    }
    else if (currentState == MenuState::OPTIONS_PAGE)
    {
        for (int i = 0; i < 3; i++)
        {
            if (optionsMenu[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
            {
                selected = i;
                clickSound.play();
                if (optionsMenu[i].getString() == "Mute Music")
                {
                    musicPlaying = !musicPlaying;
                    if (musicPlaying)
                    {
                        menuMusic.play();
                    }
                    else
                    {
                        menuMusic.pause();
                    }
                }
                else if (optionsMenu[i].getString() == "Unmute Music")
                {
                    musicPlaying = !musicPlaying;
                    if (musicPlaying)
                    {
                        menuMusic.play();
                    }
                    else
                    {
                        menuMusic.pause();
                    }
                }
                if (optionsMenu[i].getString() == "Mute Sound")
                  {
                 soundPlaying = false;
                  soundloader.StopAllSounds(); // Call StopAllSounds to stop all sounds
                  }
                else if (optionsMenu[i].getString() == "Unmute Sound")
                  {
                    soundPlaying = true;
                  }
                else if (optionsMenu[i].getString() == "Back")
                {
                    currentState = MenuState::MAIN_MENU;
                }
                updateOptionsText();
                break;
            }
        }
    }
}


void Menu::draw(sf::RenderWindow& window)
{

    window.draw(backgroundSprite);
    window.draw(heading);
    switch (currentState)
    {
    case MenuState::MAIN_MENU:
        for (const auto& item : mainmenu)
        {
            window.draw(item);
        }
        break;
    case MenuState::ABOUT_PAGE:
        window.draw(aboutText);
        // No need to draw aboutMenu since it no longer exists
        break;
    case MenuState::STORY_PAGE:
        window.draw(storyText);
        // No need to draw storyMenu since it no longer exists
        break;
    case MenuState::OPTIONS_PAGE:
        for (const auto& item : optionsMenu)
        {
            window.draw(item);
        }
        break;
    case MenuState::PLAY:
        window.draw(playerNameInput);
        break;
    }
}


void Menu::update(float deltaTime, sf::RenderWindow& window)
{
    wordTimer += deltaTime;

    if (currentState == MenuState::ABOUT_PAGE)
    {
        if (wordTimer >= wordDelay && currentWordIndex < aboutWords.size())
        {
            displayedText += aboutWords[currentWordIndex] + " ";
            aboutText.setString(wrapText(displayedText, window.getSize().x - 200, font, aboutText.getCharacterSize()));
            wordTimer = 0.0f;
            ++currentWordIndex;
        }
    }
    else if (currentState == MenuState::STORY_PAGE)
    {
        if (wordTimer >= wordDelay && currentStoryWordIndex < storyWords.size())
        {
            displaystoryText += storyWords[currentStoryWordIndex] + " ";
            storyText.setString(wrapText(displaystoryText, window.getSize().x - 200, font, storyText.getCharacterSize()));
            wordTimer = 0.0f;
            ++currentStoryWordIndex;
        }
    }
}



void Menu::handleTextInput(sf::Uint32 unicode) {
    if (isEnteringName) {
        // Convert the Unicode character to a string and append to the inputString
        if (unicode >= 32 && unicode <= 126) { // Printable ASCII characters
            inputString += static_cast<char>(unicode);
        } else if (unicode == 8 && !inputString.empty()) { // Backspace
            inputString.pop_back();
        } else if (unicode == 13) { // Enter
            // Handle Enter key if needed (e.g., finish input)
            isEnteringName = false;
            // Additional code to handle name submission
        }
        playerNameInput.setString("Enter Your Name: " + inputString);
    }
}


bool Menu::loadBackground(const std::string& filename)
{
    if (!backgroundTexture.loadFromFile(filename))
    {
        std::cerr << "Failed to load background texture from " << filename << std::endl;
        return false;
    }
    backgroundSprite.setTexture(backgroundTexture);
    return true;
}

sf::String Menu::wrapText(const std::string& text, float width, const sf::Font& font, unsigned int characterSize)
{
    sf::String wrappedText;
    std::string line;
    sf::Text tempText;
    tempText.setFont(font);
    tempText.setCharacterSize(characterSize);
    std::istringstream stream(text);
    std::string word;

    while (stream >> word)
    {
        std::string testLine = line + word + " ";
        tempText.setString(testLine);

        // Check if the current line width exceeds the maximum width
        if (tempText.getLocalBounds().width > width)
        {
            // If it does, wrap the line and start a new one
            if (!line.empty())
            {
                wrappedText += line + "\n";
            }
            line = word + " "; // Start a new line with the current word
        }
        else
        {
            line = testLine; // Continue adding words to the current line
        }
    }

    // Add any remaining text
    if (!line.empty())
    {
        wrappedText += line;
    }

    return wrappedText;
}


void Menu::updateOptionsText()
{
    optionsMenu[0].setString(musicPlaying ? "Mute Music" : "Unmute Music");
    optionsMenu[1].setString(soundPlaying ? "Mute Sound" : "Unmute Sound");
}
void Menu::handleMouseHover(sf::Vector2i mousePosition)
{
    if (currentState == MenuState::MAIN_MENU)
    {
        for (int i = 0; i < 5; i++)
        {
            if (mainmenu[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
            {
                mainmenu[i].setFillColor(sf::Color::Blue);
            }
            else
            {
                mainmenu[i].setFillColor(sf::Color::Red);
            }
        }
    }
    else if (currentState == MenuState::OPTIONS_PAGE)
    {
        for (int i = 0; i < 3; i++)
        {
            if (optionsMenu[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
            {
                optionsMenu[i].setFillColor(sf::Color::Blue);
            }
            else
            {
                optionsMenu[i].setFillColor(sf::Color::Red);
            }
        }
    }
}

