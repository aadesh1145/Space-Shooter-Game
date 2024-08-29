#include "file.h"
#include <fstream>
#include <iostream>

int FileHandler::readHighScore(const std::string& filename) {
    std::ifstream file(filename);
    int highScore = 0;

    if (file.is_open()) {
        file >> highScore;
        file.close();
    } else {
        std::cout << "No high score file found. Starting fresh." << std::endl;
    }

    return highScore;
}

void FileHandler::writeHighScore(const std::string& filename, int score) {
    std::ofstream file(filename);

    if (file.is_open()) {
        file << score;
        file.close();
    } else {
        std::cout << "Unable to save high score." << std::endl;
    }
}
