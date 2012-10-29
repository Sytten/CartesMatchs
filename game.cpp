#include "game.h"
#include "gameWindow.h"
#include "gameImage.h"
#include <QLabel>
#include <QTimer>

Game::Game() : m_lastCard(0)
{
    m_window = new GameWindow;

    QAction *actionNewGame = m_window->returnActionNewGame();
    connect(actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));
    newGame();

    for(int i = 0; i < 36; i++)
    {
        GameImage *pointer = m_pointersOnCards.at(i);
        connect(pointer, SIGNAL(pressedLabel(GameImage *currentImage)), this, SLOT(imagePressed(GameImage *image)));
    }

    m_window->setVisible(true);
}

Game::~Game()
{
    delete m_window;
}

void Game::imagePressed(GameImage *image)
{
    if(m_window && image)
    {
        int cardsFaceUp = countCardsFaceDown();

        if(cardsFaceUp == 0)
        {
            m_lastCard = image;
            image->turnCard();
        }

        if(cardsFaceUp == 1)
        {
            image->turnCard();

            if(m_lastCard->cardNumber() == image->cardNumber() && m_lastCard != image)
            {
                m_lastCard->setFound(true);
                image->setFound(true);

                checkWin();
            }

            else
            {
                QTimer::singleShot(1200, image, SLOT(turnCard()));
                m_lastCard->turnCard();
            }
        }
    }

}

int Game::countCardsFaceDown() const
{
    int cards(0);

    for(int i = 0; i < 36; i++)
    {
        if(m_pointersOnCards.at(i)->faceDown() == false)
            cards++;
    }

    return cards;
}


void Game::checkWin()
{
    int cards(0);

    for(int i = 0; i < 36; i++)
    {
        if(m_pointersOnCards.at(i)->found() == false)
            cards++;
    }

    if(cards == 0)
        newGame();
}

void Game::newGame()
{
    m_pointersOnCards.clear();

    QList<int> numbers;

    for(int i = 1; i < 19; i++) //2 times each number up to 18
    {
        numbers << i << i;
    }

    for(int i = 0; i < 36; i++)
    {
        int y = numbers.at(generateNumber(numbers.count()));
        m_pointersOnCards.append(new GameImage(y));
        numbers.removeAt(y);
    }

    m_window->displayNewGame(m_pointersOnCards);
}


int generateNumber(int a)
{
    return rand()% a;
}
