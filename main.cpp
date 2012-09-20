#include <QApplication>
#include "FenPrincipale.h"
#include "time.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication app(argc, argv);

    FenPrincipale fen;

    fen.show();

    return app.exec();
}
