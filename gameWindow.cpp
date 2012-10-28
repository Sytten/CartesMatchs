#include "gameWindow.h"
#include "gameImage.h"
#include "randomNumber.h"
#include <QMenuBar>

GameWindow::GameWindow(QMainWindow *parent) : QMainWindow(parent), m_centralArea(0)
{
    //create menus
    QMenu *gameMenu = menuBar()->addMenu(tr("&Partie"));
    QMenu *helpMenu = menuBar()->addMenu(tr("&?"));

        //Game Menu
        QAction *actionNewGame = gameMenu->addAction(tr("Nouvelle &partie"));
            actionNewGame->setShortcut(QKeySequence(Qt::Key_F2));
        gameMenu->addSeparator();
        QAction *actionQuit = gameMenu->addAction(tr("&Quitter"));
            actionQuit->setShortcut(QKeySequence(Qt::Key_Escape));

        //Help Menu
        QAction *actionAbout = helpMenu->addAction(tr("À propos de CartesMatchs"));
            actionAbout->setShortcut(QKeySequence(Qt::Key_F6));


    //connections
            connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));
    //connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));

    newGame();
}


void GameWindow::newGame()
{
    if(m_centralArea)
        delete m_centralArea;

    QList<int> numbers;

    for(int i = 1; i < 19; i++) //2 times each number up to 18
    {
        numbers << i << i;
    }

    for(int i = 0; i < 36; i++)
    {
        int y = numbers.at(RandomNumber::generateNumber(numbers.count()));
        imagesPointers.append(new GameImage(i));
        numbers.removeAt(y);
    }

    images = new QGridLayout;
    int imageNumber(0);

    for(int x = 0; x < 6; x++)
    {
        for(int y = 0; y < 6; y++)
        { 
            images->addWidget(imagesPointers.at(imageNumber), y, x);
            imageNumber++;
        }
    }

    m_centralArea = new QWidget;

    m_centralArea->setObjectName("zone1");
    m_centralArea->setStyleSheet("QWidget#zone1 { border-image: url(:/Images/background.jpg); }");

    m_centralArea->setLayout(images);
    setCentralWidget(m_centralArea);
}
