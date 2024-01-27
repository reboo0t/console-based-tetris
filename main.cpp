/*Отче наш, що є на небесах! Нехай святиться Ім’я
Твоє. Нехай прийде Царство Твоє, нехай буде воля
Твоя як на небі, так і на землі. Хліб наш насущний
дай нам сьогодні. І прости нам провини наші, як і
ми прощаємо винуватцям нашим. І не введи нас у
спокусу, але визволи нас від лукавого. Бо Твоє є
Царство, і сила, і слава навіки. Амінь.*/

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