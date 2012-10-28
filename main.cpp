#include <QApplication>
#include <time.h>
#include "game.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication app(argc, argv);
    Game game;
    return app.exec();
}

