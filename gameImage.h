#ifndef GAMEIMAGE_H
#define GAMEIMAGE_H

#include<QWidget>
#include<QLabel>

class GameImage : public QLabel
{
    Q_OBJECT

    public:
        GameImage(int imageNumber, QLabel *parent = 0);
        bool eventFilter(QObject *obj, QMouseEvent *event);

        void setFound(bool answer) { m_found = answer; }
        bool found() const { return m_found; }
        bool faceDown() const { return m_faceDown; }
        int cardNumber() const { return m_imageNumber; }
        void turnCard();

    public slots:
        void turnCardSlot();

    signals:
        void pressedLabel(GameImage *currentImage);

    private:
        int m_imageNumber;
        bool m_faceDown;
        bool m_found;
        int m_width;
        int m_height;

};

#endif // GAMEIMAGE_H
