#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include<QWidget>
#include<QMainWindow>
#include<QGridLayout>
#include<QList>
#include<QLabel>
#include<QAction>

class GameImage;


class GameWindow : public QMainWindow
{
    Q_OBJECT

    public:
        GameWindow(QMainWindow *parent = 0);
        QAction* returnActionNewGame() { return actionNewGame; }
        void displayNewGame(QList<GameImage*> pointersOnImages);

    private:
        QWidget *m_centralArea;
        QGridLayout *images;
        QAction *actionNewGame;
};

#endif // GAMEWINDOW_H
