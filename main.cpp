#define NOMINMAX
#include <iostream>
#include <windows.h>
#include <vector>
#include <limits>
#include "Game.cpp"

using namespace std;

void clearScreen()
{
    #ifdef _WIN32
        system("cls"); // Windows clear screen
    #else
        cout << "\033[2J\033[1;1H"; // Linux clear screen
    #endif
}

int main()
{
    Game tetris;
    while (true)
    {
        switch (tetris.menu())
        {
        case 1:
            clearScreen();
            tetris.run();
            clearScreen();
            continue;
        case 2:
            clearScreen();
            tetris.changeDifficulty();
            clearScreen();
            continue;
        case 3:
            cout << "Thanks for playing!";
            return 0;
        default:
            cout << "Incorrect option!";
            Sleep(2000);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearScreen();
            continue;
        }
    }
}
