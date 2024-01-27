#define NOMINMAX
#include "Game.h"
#include "Figure.cpp"
#include <limits>
#include <string>
#include <windows.h>

using namespace std;

// Constants for difficulty
const int EASY = 300;
const int MEDIUM = 200;
const int HARD = 100;

static int difficulty = MEDIUM;
static string difficultyStatus = "Medium";

void Game::changeDifficulty()
{

    int choice = 0;

    cout << R"(#==================================================================#

         ####### ####### ####### ######    ###    #####
            #    #          #    #     #    #    #     #
            #    #          #    #     #    #    #
            #    #####      #    ######     #     #####
            #    #          #    #   #      #          #
            #    #          #    #    #     #    #     #
            #    #######    #    #     #   ###    #####

#==================================================================#

        Select difficulty:                Made by:

        1: Easy                           
        2: Medium                         Batalov Maximilian      
        3: Hard                                        
            
#==================================================================#

Choose >> )";

    cin >> choice;
    switch (choice)
    {
    case 1:
        difficulty = EASY;
        difficultyStatus = "Easy  ";
        break;
    case 2:
        difficulty = MEDIUM;
        difficultyStatus = "Medium";
        break;
    case 3:
        difficulty = HARD;
        difficultyStatus = "Hard  ";
        break;
    default:
        cout << "Incorrect option!";
        Sleep(2000);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
}
int Game::menu()
{
    int choice = 0;

    cout << R"(#==================================================================#

         ####### ####### ####### ######    ###    #####
            #    #          #    #     #    #    #     #
            #    #          #    #     #    #    #
            #    #####      #    ######     #     #####
            #    #          #    #   #      #          #
            #    #          #    #    #     #    #     #
            #    #######    #    #     #   ###    #####

#==================================================================#

        <Menu>                            Made by:

        1: Start Game                     
        2: Difficulty )"
         << ": " << difficultyStatus << R"(            Batalov Maximilian      
        3: Quit                                       
            
#==================================================================#

Choose >> )";

    cin >> choice;
    return choice;
}
void Game::initVec(vector<vector<int>> &vec, int width, int height)
{
    vector<int> temp;
    temp.push_back(BORDERID);
    for (int i = BORDERID; i < width - BORDERID; i++)
        temp.push_back(EMPTYID);
    temp.push_back(BORDERID);

    for (int i = 0; i < height - 2; i++)
        vec.push_back(temp);

    temp.clear();
    for (int i = 0; i < width; i++)
        temp.push_back(FLOORID);
    vec.push_back(temp);
}
void Game::displayField(const vector<vector<int>> &vec)
{
    gotoxy(0, 0);
    for (size_t i = 0; i < vec.size(); i++)
    {
        for (size_t j = 0; j < vec[i].size(); j++)
        {
            if (vec[i][j] == BORDERID || vec[i][j] == BLOCKID)
                cout << BORDERCHAR;
            else if (vec[i][j] == EMPTYID)
                cout << EMPTYCHAR;
            else if (vec[i][j] == FLOORID)
                cout << FLOORCHAR;
        }
        cout << endl;
    }
    gotoxy(0, 20);
    cout << "Score: " << score;
}
void Game::clearFullRows(int WIDTH)
{
    vector<int> filledRows;

    // Find the filled rows
    for (int i = vec.size() - FLOORID; i >= CEILINGID; i--)
    {
        bool isFilledRow = true;
        for (size_t j = BORDERID; j < vec[i].size() - BORDERID; j++)
        {
            if (vec[i][j] != BLOCKID)
            {
                isFilledRow = false;
                break;
            }
        }

        // Add index of filled row in filledRows vector
        if (isFilledRow)
        {
            filledRows.push_back(i);
        }
    }

    // Clear the filled rows
    for (auto it = filledRows.rbegin(); it != filledRows.rend(); ++it)
    {
        int rowIndex = *it;
        vec.erase(vec.begin() + rowIndex);
        vector<int> emptyRow(WIDTH, EMPTYID);
        emptyRow[0] = BORDERID;
        emptyRow[WIDTH - BORDERID] = BORDERID;
        vec.insert(vec.begin(), emptyRow);
        score++;
    }
}
int Game::pause()
{
    gotoxy(2, 6);
    cout << "Game is PAUSED";
    gotoxy(4, 10);
    cout << "R: restart";
    gotoxy(4, 12);
    cout << "ESC: exit";
    while (true)
    {
        int keyPressed = _getch();
        switch (keyPressed)
        {
        case KEYSPACE:
            return CONTINUE;
            break;
        case KEYRESTART:
            return RESTART;
            break;
        case KEYESC:
            return EXIT;
            break;
        default:
            break;
        }
    }
}
bool Game::isGameOver(const vector<vector<int>> &vec)
{
    for (size_t col = 0; col < vec[1].size(); col++)
    {
        if (vec[1][col] == BLOCKID)
            return true;
    }
    return false;
}
int Game::run()
{
    initVec(clearVec, WIDTH, HEIGHT);
start:
    initVec(vec, WIDTH, HEIGHT);
    displayField(vec);

    int keyPressedID;
    Figure object;
    bool isSquare = false;
    object.spawn(isSquare);

    while (true)
    {
        // Game logic
        while (!_kbhit())
        {
            object.hide();
            object.moveDown();
            if (object.isCollision(vec))
            {
                object.moveUp();
                object.fixed(vec);
                clearFullRows(WIDTH);
                displayField(vec);
                object.spawn(isSquare);
                if (isGameOver(vec))
                {
                    displayField(clearVec);
                    gotoxy(5, 9);
                    cout << "GAMEOVER";
                    Sleep(3000);
                    score = 0;
                    goto exit;
                }
            }
            object.show();
            Sleep(difficulty);
        }

        // Controls
        keyPressedID = _getch();
        switch (keyPressedID)
        {
        case KEYSPACE: // Space Key
            displayField(clearVec);
            switch (pause())
            {
            case CONTINUE:
                displayField(vec);
                break;
            case RESTART:
                score = 0;
                vec.clear();
                goto start;
                break;
            case EXIT:
                score = 0;
                goto exit;
                break;
            }
            break;

        case KEYUP: // Up arrow Key
            if (isSquare)
                break;
            else
            {
                object.hide();
                object.inRotate();
                if (object.isCollision(vec))
                    object.outRotate();
                break;
            }

        case KEYLEFT: // Left arrow Key
            object.hide();
            object.moveLeft();
            if (object.isCollision(vec))
                object.moveRight();
            break;

        case KEYRIGHT: // Right arrow
            object.hide();
            object.moveRight();
            if (object.isCollision(vec))
                object.moveLeft();
            break;

        case KEYDOWN: // Down arrow
            object.hide();
            object.moveDown();
            if (object.isCollision(vec))
                object.moveUp();
            break;
        }
    }
exit:
    vec.clear();
    clearVec.clear();
    return 0;
}
