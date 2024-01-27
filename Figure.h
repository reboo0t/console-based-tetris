#pragma once
#include <vector>
#include <windows.h>


struct Point
{
    int x;
    int y;
};

inline void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = static_cast<SHORT>(x);
    coordinates.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

class Figure
{
    std::vector<Point> vec;

public:
    inline void push(int x, int y);
    inline void show();
    inline void hide();
    inline void moveDown();
    inline void moveUp();
    inline void moveLeft();
    inline void moveRight();
    inline bool isCollision(const std::vector<std::vector<int>>& vec2d);
    inline void fixed(std::vector<std::vector<int>>& vec2d);
    inline void spawn(bool& isSquare);
    inline void inRotate();
    inline void outRotate();
};
