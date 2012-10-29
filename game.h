#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QLabel>

class GameImage;
class GameWindow;


class Game : public QWidget
{
  Q_OBJECT

  public:
    Game();
    ~Game();
    int countCardsFaceDown() const;
    void checkWin();

  public slots:
    void imagePressed(GameImage *image);
    void newGame();

  private:
    GameImage *m_lastCard;
    GameWindow *m_window;
    QList<GameImage*> m_pointersOnCards;

};

int generateNumber(int a);

#endif // GAME_H
