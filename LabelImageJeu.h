#ifndef LABELIMAGEJEU_H
#define LABELIMAGEJEU_H

#include <QtGui>

class LabelImageJeu : public QLabel
{
    public:
        LabelImageJeu(int numeroImage);
        void mousePressEvent(QMouseEvent *event);

        void retourner(LabelImageJeu* carte);

        bool trouver();
        bool voitFace();

    private:
        bool m_trouver;
        bool m_voitFace;
        int m_numeroImage;
};

#endif // LABELIMAGEJEU_H
