#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include "LabelImageJeu.h"

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

    public:
        FenPrincipale();

        void setDerniereCarte(LabelImageJeu* derniereCarte);
        LabelImageJeu* derniereCarte();

        int nombreRandom(QList<int> &nombres);
        void gagne();
        int cartesRetournees();

        void centreFenetre();

    public slots:
        void nouvellePartie();

    private:
        LabelImageJeu* m_derniereCarte;
        bool m_partieEnCours;
        QWidget* zoneCentrale;
        QGridLayout* grilleJeu;
        QList<LabelImageJeu*> listeImagesJeu;
};

#endif // FENPRINCIPALE_H
