#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include<QWidget>
#include<QMainWindow>
#include<QGridLayout>
#include<QList>
#include<QLabel>
#include<gameImage.h>

class GameWindow : public QMainWindow
{
    Q_OBJECT

    public:
        GameWindow(QMainWindow *parent = 0);
        QList<GameImage*> pointers() const { return imagesPointers; }

    public slots:
        void newGame();
        //void about();

    private:
        QWidget *m_centralArea;
        QGridLayout *images;
        QList<GameImage*> imagesPointers;
};

#endif // GAMEWINDOW_H
