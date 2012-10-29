#include "gameImage.h"
#include "game.h"
#include <QDesktopWidget>
#include <QMouseEvent>

GameImage::GameImage(int imageNumber, QLabel *parent): QLabel(parent), m_imageNumber(imageNumber), m_faceDown(true), m_found(false)
{
    installEventFilter(this);

    //calculate the size of the screen
    QDesktopWidget desktop;
    QRect desktopSurface = desktop.screenGeometry();
    m_height = desktopSurface.height()/6 - 25;
    m_width = m_height;

    //down card
    QPixmap image(":/Images/back.jpg");
    image = image.scaled(m_width, m_height);
    setPixmap(image);
}


bool GameImage::eventFilter(QObject *obj, QMouseEvent *event)
{
    if(obj == this && event->button() == Qt::LeftButton && m_found == false)
    {
        emit pressedLabel(this);
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void GameImage::turnCard()
{
    if(!m_faceDown){ //if we see the face
        QPixmap image(":/Images/back.jpg");
        image = image.scaled(m_width, m_height);
        setPixmap(image);
    }

    else
    {
        QString filepath(":/Images/cards/card%1.jpg");
        QPixmap image(filepath.arg(m_imageNumber));
        image = image.scaled(m_width, m_height);
        setPixmap(image);
    }

    m_faceDown = !m_faceDown;
}

void GameImage::turnCardSlot()
{
    turnCard();
}
