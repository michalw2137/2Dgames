#include <string>
#include <sstream>
#include "screen.h"
#include <windows.h>

bool Screen::loadTextures()
{
    bool f1 = ball.loadFromFile("textures/circle_wins.png");
    bool f2 = box.loadFromFile("textures/square_wins.png");
    bool f3 = over.loadFromFile("textures/game_over.png");
    bool f4 = empty.loadFromFile("textures/empty.png");
    if (!(f1 && f2 && f3 && f4)) {
        return false;
    }
    
}

int Screen::getWait() {
    return time;
}

void Screen::boxWins()
{
    time = 1000;

    currentTexture = &box;
}

void Screen::ballWins()
{
    time = 1000;

    currentTexture = &ball;
}

void Screen::gameOver()
{
    time = 2000;

    currentTexture = &over;
}

void Screen::emptyScreen()
{
    time = 0;
    currentTexture = &empty;
}

void Screen::render()
{
    currentTexture->render();
}

