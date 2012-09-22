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

    public slots:
        void nouvellePartie();
        void quitter();
        void afficherAbout();
        void cheat();

    private:
        LabelImageJeu* m_derniereCarte;
        QWidget* zoneCentrale;
        QGridLayout* grilleJeu;
        QList<LabelImageJeu*> listeImagesJeu;

    protected:
        void closeEvent(QCloseEvent *event);
        void enregistrerSettings(QString nomFenetre);
        void chargerSettings(QString nomFenetre);
};

#endif // FENPRINCIPALE_H
