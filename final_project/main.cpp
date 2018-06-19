#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *TankGame = new GameWindow();

    TankGame->game_play();

    delete TankGame;
    return 0;
}
