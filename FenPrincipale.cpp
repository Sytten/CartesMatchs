#include "FenPrincipale.h"

/**********Constructeur***********/
FenPrincipale::FenPrincipale() : QMainWindow()
{
    //Initialisation d'attributs
    m_derniereCarte = 0;
    m_partieEnCours = false;

    //cr�ation de la fenetre de base
    zoneCentrale = new QWidget;
    zoneCentrale->setStyleSheet("border-image: url(:/Images/start.jpg);"
                                    "background-repeat: no-repeat;");
    resize(800, 600);

    centreFenetre();

    //cr�ation des menus
    QMenu *menuPartie = menuBar()->addMenu("&Partie");
    QMenu *menuAide = menuBar()->addMenu("&?");

        //Menu Partie
        QAction *actionJouer = menuPartie->addAction("Nouvelle &partie");
            actionJouer->setShortcut(QKeySequence(Qt::Key_F2));
        menuPartie->addSeparator();
        QAction *actionOptions = menuPartie->addAction("&Options (� venir)");
            actionOptions->setShortcut(QKeySequence(Qt::Key_F4));
        QAction *actionStatistiques = menuPartie->addAction("&Statistiques (� venir)");
            actionStatistiques->setShortcut(QKeySequence(Qt::Key_F5));
        menuPartie->addSeparator();
        QAction *actionQuitter = menuPartie->addAction("&Quitter");
            actionQuitter->setShortcut(QKeySequence(Qt::Key_Escape));

        //Menu Help
        QAction *actionPropos = menuAide->addAction("� propos de CartesMatchs");
            actionPropos->setShortcut(QKeySequence(Qt::Key_F6));


    //connections
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionJouer, SIGNAL(triggered()), this, SLOT(nouvellePartie()));



    setCentralWidget(zoneCentrale);
}


/**********Lancement d'une nouvelle partie**********/
void FenPrincipale::nouvellePartie()
{
    delete zoneCentrale;
    listeImagesJeu.clear();

    QList<int> nombres;

    zoneCentrale = new QWidget;
    grilleJeu = new QGridLayout;


    for(int i = 1; i < 19; i++)
    {
        nombres << i << i;
    }

    for(int i = 0; i < 36; i++)
    {
        listeImagesJeu.append(new LabelImageJeu(nombreRandom(nombres)));
    }

    int numeroImage = 0;

    for(int x = 0; x < 6; x++)
    {
        for(int y = 0; y < 6; y++)
        {
            grilleJeu->addWidget(listeImagesJeu.at(numeroImage), y, x);
            numeroImage++;
        }
    }

    zoneCentrale->setStyleSheet("background-color: black");

    zoneCentrale->setLayout(grilleJeu);
    setCentralWidget(zoneCentrale);

    centreFenetre();
}


/**********Mettre en m�moire la derni�re carte retourn�e**********/
void FenPrincipale::setDerniereCarte(LabelImageJeu* derniereCarte)
{
    m_derniereCarte = derniereCarte;
}


/**********G�n�rer un notre random**********/
int FenPrincipale::nombreRandom(QList<int> &nombres)
{
    int nombreRandom = rand()% nombres.count();
    nombres.removeAt(nombreRandom);

    return nombreRandom;
}


/**********Gagn�**********/
void FenPrincipale::gagne()
{
    int cartes(0);

    for(int i = 0; i < 36; i++)
    {
        if(listeImagesJeu.at(i)->trouver() == false)
        {
            cartes++;
        }
    }

    if(!cartes)
    {
        delete zoneCentrale;
        listeImagesJeu.clear();

        zoneCentrale = new QWidget;
        zoneCentrale->setStyleSheet("border-image: url(:/Images/start.jpg);"
                                     "background-repeat: no-repeat;");
        resize(800, 600);

        centreFenetre();
    }
}


/**********Centrer la fen�tre**********/
void FenPrincipale::centreFenetre()
{
    QDesktopWidget bureau;
    QRect surface_bureau = bureau.screenGeometry();
    int x = surface_bureau.width()/2 - width()/2;
    int y = surface_bureau.height()/2 - height()/2;
    move(x,y);
}


/**********Compter cartes retourn�es**********/
int FenPrincipale::cartesRetournees()
{
    int cartes(0);

    for(int i = 0; i < 36; i++)
    {
        if(listeImagesJeu.at(i)->voitFace() == true && listeImagesJeu.at(i)->trouver() == false)
        {
            cartes++;
        }
    }

    return cartes;
}


/**********Retourner la derni�re carte retourn�e**********/
LabelImageJeu* FenPrincipale::derniereCarte()
{
    return m_derniereCarte;
}
