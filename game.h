#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QLabel>
#include "gameImage.h"
#include "gameWindow.h"

class Game : public QObject
{
  Q_OBJECT

  public:
    Game();
    ~Game();
    int countCardsFaceDown(QList<GameImage*> pointers) const;
    void checkWin(QList<GameImage*> pointers) const;

  public slots:
    void imagePressed(GameImage *image);

  private:
    GameImage *m_lastCard;
    GameWindow *m_window;


};

#endif // GAME_H
