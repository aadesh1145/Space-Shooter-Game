//game.h
#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "background.h"
#include "explosion.h"
#include "sound.h"
#include "menu.hpp"
#include "globals.h"
#include "file.h"
#include <fstream>
#include <iostream>


using namespace sf;
using namespace std;

class Game
{
private:
    
 
    bool isPaused;
    Texture playerTexture;
    Background* background;
    Player* player;
    Bullet* bullet;
    static sf::Texture bulletTexture;
    vector<Explosion> explosions;
    Texture explosionTexture;
    float enemySpawnCooldown;
    float lastEnemySpawnTime;
    bool bossSpawned;
    int score;
    sf::Font font;
    sf::Text scoreText;
    Texture bossEnemyTex;
    bool victory;
    sf::Text victoryText;

    Clock clock{};
    float deltaTime{800.00};
    static Game* instance;
    void initWindow();
    void initBackground();
    void initTexture();
    void initPlayer();
    void initBullet();
    void initEnemy();
    void initBossEnemy();
    void spwanEnemy();
    void updateEnemies(float dt);
    void renderEnemies();
    void updateExplosions(float dt);
    static sf::Texture explosionTex; 
    bool backgroundIsLoaded;
    bool gameOver;
    std::vector<Bullet> bullets;
    bool paused = false; 

    int highScore;
    bool newHighScore; // Track if a new high score was achieved
    FileHandler fileHandler; // Instance of FileHandler for reading/writing high score
    sf::Text highScoreText; // Text to display high score
    sf::Text newHighScoreText;// Text to display "New High Score" 
     sf::Clock newHighScoreClock;

public:
    Game() ;
       Menu* pauseMenu;
    SoundLoader soundLoader;
    static Game* getInstance();
    static void cleanup();
    static Texture bulletTex;
    static Texture enemyTex;
    static RenderWindow* window;
    virtual ~Game();
    void update(float dt);
    void run();
    void render();
    void updateEvents();
    void initScore();
    void incrementScore();
    void resetGame();
    void handleGameOver();
    void setGameOver(bool status);
    static sf::Texture& getExplosionTexture();
    static sf::Texture& getBulletTexture() { return bulletTex; }
    static void setBulletTexture(const sf::Texture& texture);  // To set the texture
    std::vector<Bullet>& getBullets(); // Getter for bullets
    void updateBullets(float dt);
    void handleVictory();
    bool isGameOver() const;
    bool isVictory() const;
    
};

