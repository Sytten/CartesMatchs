#ifndef LABELIMAGEJEU_H
#define LABELIMAGEJEU_H

#include <QtGui>
class FenPrincipale;

class LabelImageJeu : public QLabel
{
    Q_OBJECT

    public:
        LabelImageJeu(int numeroImage);
        void mousePressEvent(QMouseEvent *event);

        void retourner();

        bool trouver();
        bool voitFace();

        void setTrouver(bool trouver);

    public slots:
        void continuerRetourner();

    private:
        bool m_trouver;
        bool m_voitFace;
        int m_numeroImage;

        int w;
        int h;

        FenPrincipale* pFenPrincipale;
        LabelImageJeu* pDerniereCarte;
};

#endif // LABELIMAGEJEU_H
