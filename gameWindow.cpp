#include "gameWindow.h"
#include "gameImage.h"
#include <QMenuBar>

GameWindow::GameWindow(QMainWindow *parent) : QMainWindow(parent), m_centralArea(0)
{
    //create menus
    QMenu *gameMenu = menuBar()->addMenu(tr("&Partie"));

        //Game Menu
        actionNewGame = gameMenu->addAction(tr("Nouvelle &partie"));
            actionNewGame->setShortcut(QKeySequence(Qt::Key_F2));
        gameMenu->addSeparator();
        QAction *actionQuit = gameMenu->addAction(tr("&Quitter"));
            actionQuit->setShortcut(QKeySequence(Qt::Key_Escape));

    //connections
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));

}


void GameWindow::displayNewGame(QList<GameImage*> pointersOnImages)
{
    if(m_centralArea)
        delete m_centralArea;

    images = new QGridLayout;
    int imageNumber(0);

    for(int x = 0; x < 6; x++)
    {
        for(int y = 0; y < 6; y++)
        { 
            images->addWidget(pointersOnImages.at(imageNumber), y, x);
            imageNumber++;
        }
    }

    m_centralArea = new QWidget;

    m_centralArea->setObjectName("zone1");
    m_centralArea->setStyleSheet("QWidget#zone1 { border-image: url(:/Images/background.jpg); }");

    m_centralArea->setLayout(images);
    setCentralWidget(m_centralArea);
}
