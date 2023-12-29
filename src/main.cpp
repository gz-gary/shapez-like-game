#include "Game/Game.h"
#include <QApplication>

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Game new_game;
    new_game.restart("./save/save0.txt");

    return app.exec();
}
