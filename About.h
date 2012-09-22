#ifndef ABOUT_H
#define ABOUT_H

#include <QtGui>

class FenPrincipale;

class About : public QDialog
{
     public:
        About(FenPrincipale* parent);

     private:
        QPushButton* m_fermer;
        QLabel* m_nom;
        QLabel* m_icone;
        QLabel* m_texte;

};

#endif // ABOUT_H
