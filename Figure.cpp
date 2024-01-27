#include "Game.h"
#include "Figure.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>

using namespace std;

// Constants for building a field
const int CEILINGID = 0;
const int EMPTYID = 0;
const int BORDERID = 1;
const int FLOORID = 2;
const int BLOCKID = 3;
const int WIDTH = 16 + 2;
const int HEIGHT = 20 + 1;

// Constans for controls
const int KEYSPACE = 32;
const int KEYUP = 72;
const int KEYDOWN = 80;
const int KEYLEFT = 75;
const int KEYRIGHT = 77;
const int KEYESC = 27;
const int KEYRESTART = 114;

// Constans for graphics
const char BORDERCHAR = 219;
const char EMPTYCHAR = 249;
const char FLOORCHAR = 223;

// Constants for pause()
const int CONTINUE = 1;
const int RESTART = 2;
const int EXIT = 0;

void Figure::push(int x, int y)
{
    Point temp;
    temp.x = x;
    temp.y = y;
    vec.push_back(temp);
}
void Figure::show()
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        gotoxy(vec[i].x, vec[i].y);
        cout << BORDERCHAR;
    }
}
void Figure::hide()
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        gotoxy(vec[i].x, vec[i].y);
        cout << EMPTYCHAR;
    }
}
void Figure::moveDown()
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i].y++;
    }
}
void Figure::moveUp()
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i].y--;
    }
}
void Figure::moveLeft()
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i].x--;
    }
}
void Figure::moveRight()
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i].x++;
    }
}
bool Figure::isCollision(const vector<vector<int>> &vec2d)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec2d[vec[i].y][vec[i].x] == BORDERID || vec2d[vec[i].y][vec[i].x] == FLOORID || vec2d[vec[i].y][vec[i].x] == BLOCKID)
        {
            return true;
        }
    }
    return false;
}
void Figure::fixed(vector<vector<int>> &vec2d)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec2d[vec[i].y][vec[i].x] = BLOCKID;
    }
}
void Figure::spawn(bool &isSquare)
{

    srand(time(NULL));
    int randNum = 1 + (rand() % 7);

    switch (randNum)
    {
    case 1: // A Square object
        vec.clear();
        this->push(8, 1);
        this->push(9, 1);
        this->push(8, 2);
        this->push(9, 2);
        isSquare = true;
        break;

    case 2: // A Line object
        vec.clear();
        this->push(7, 1);
        this->push(8, 1);
        this->push(9, 1);
        this->push(10, 1);
        isSquare = false;
        break;

    case 3: // A S-Shaped object
        vec.clear();
        this->push(9, 1);
        this->push(8, 1);
        this->push(8, 2);
        this->push(7, 2);
        isSquare = false;
        break;

    case 4: // An Inverted S-Shaped object
        vec.clear();
        this->push(7, 1);
        this->push(8, 1);
        this->push(8, 2);
        this->push(9, 2);
        isSquare = false;
        break;

    case 5: // A R-Shaped object
        vec.clear();
        this->push(7, 1);
        this->push(8, 1);
        this->push(9, 1);
        this->push(9, 2);
        isSquare = false;
        break;

    case 6: // An Inverted R-Shaped object
        vec.clear();
        this->push(7, 2);
        this->push(8, 2);
        this->push(9, 2);
        this->push(9, 1);
        isSquare = false;
        break;

    case 7: // A Piramide-Shaped object
        vec.clear();
        this->push(8, 1);
        this->push(8, 2);
        this->push(9, 2);
        this->push(8, 3);
        isSquare = false;
        break;
    }
}
void Figure::inRotate()
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        int x = -(vec[i].y - vec[1].y) + vec[1].x;
        int y = (vec[i].x - vec[1].x) + vec[1].y;
        vec[i].x = x;
        vec[i].y = y;
    }
}
void Figure::outRotate()
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        int x = (vec[i].y - vec[1].y) + vec[1].x;
        int y = -(vec[i].x - vec[1].x) + vec[1].y;
        vec[i].x = x;
        vec[i].y = y;
    }
}