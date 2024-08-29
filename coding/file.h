#ifndef FILE_H
#define FILE_H

#include <string>

class FileHandler {
public:
    static int readHighScore(const std::string& filename);
    static void writeHighScore(const std::string& filename, int score);
};

#endif // FILE_H
