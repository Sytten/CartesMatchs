#include "game.h"
#include <QLabel>
#include <QTimer>

Game::Game() : m_lastCard(0)
{
    m_window = new GameWindow;
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
        int cardsFaceUp = countCardsFaceDown(m_window->pointers());

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

                checkWin(m_window->pointers());
            }

            else
            {
                QTimer::singleShot(1200, image, SLOT(turnCard()));
                m_lastCard->turnCard();
            }
        }
    }

}

int Game::countCardsFaceDown(QList<GameImage*> pointers) const
{
    int cards(0);

    for(int i = 0; i < 36; i++)
    {
        if(pointers.at(i)->faceDown() == false)
            cards++;
    }

    return cards;
}


void Game::checkWin(QList<GameImage*> pointers) const
{
    int cards(0);

    for(int i = 0; i < 36; i++)
    {
        if(pointers.at(i)->found() == false)
            cards++;
    }

    if(cards == 0)
        m_window->newGame();
}
