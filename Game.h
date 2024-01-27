#pragma once
#include "Figure.h"
#include <string>

class Game
{
    int score = 0;
    std::vector<std::vector<int>> vec;
    std::vector<std::vector<int>> clearVec;

public:
    inline void changeDifficulty();
    inline int menu();
    inline void initVec(std::vector<std::vector<int>>& vec, int width, int height);
    inline void displayField(const std::vector<std::vector<int>>& vec);
    inline void clearFullRows(int WIDTH);
    inline inline int pause();
    inline bool isGameOver(const std::vector<std::vector<int>>& vec);
    inline int run();
};
