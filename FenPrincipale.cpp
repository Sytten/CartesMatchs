#include "FenPrincipale.h"
#include "About.h"
#include <QDebug>

/**********Constructeur***********/
FenPrincipale::FenPrincipale() : QMainWindow()
{
    //Initialisation d'attributs
    m_derniereCarte = 0;
    m_dejaEnregistre = false;

    //création de la fenetre de base
    zoneCentrale = new QWidget;
    zoneCentrale->setStyleSheet("border-image: url(:/Images/start.jpg);");

    chargerSettings("FenBase");

    //création des menus
    QMenu *menuPartie = menuBar()->addMenu("&Partie");
    QMenu *menuAide = menuBar()->addMenu("&?");

        //Menu Partie
        QAction *actionJouer = menuPartie->addAction("Nouvelle &partie");
            actionJouer->setShortcut(QKeySequence(Qt::Key_F2));
        menuPartie->addSeparator();
        QAction *actionQuitter = menuPartie->addAction("&Quitter");
            actionQuitter->setShortcut(QKeySequence(Qt::Key_Escape));

        //Menu Help
        QAction *actionPropos = menuAide->addAction("À propos de CartesMatchs");
            actionPropos->setShortcut(QKeySequence(Qt::Key_F6));


    //connections
    connect(actionQuitter, SIGNAL(triggered()), this, SLOT(quitter()));
    connect(actionJouer, SIGNAL(triggered()), this, SLOT(nouvellePartie()));
    connect(actionPropos, SIGNAL(triggered()), this, SLOT(afficherAbout()));

    setCentralWidget(zoneCentrale);
}


/**********Lancement d'une nouvelle partie**********/
void FenPrincipale::nouvellePartie()
{
    if(!m_dejaEnregistre){
        enregistrerSettings("FenBase");
    }
    m_dejaEnregistre = true;

    delete zoneCentrale;
    listeImagesJeu.clear(); //Au cas où il y aurait une partie déjà en cours

    QList<int> nombres;

    zoneCentrale = new QWidget;
    grilleJeu = new QGridLayout;


    for(int i = 1; i < 19; i++) //initialisation du tableau 2x chaque nombre jusqu'à 18
    {
        nombres << i << i;
    }

    for(int i = 0; i < 36; i++) //création des objets (cartes)
    {
        listeImagesJeu.append(new LabelImageJeu(nombreRandom(nombres)));
    }

    int numeroImage = 0;

    for(int x = 0; x < 6; x++) //Placer les cartes dans une grille
    {
        for(int y = 0; y < 6; y++)
        {
            grilleJeu->addWidget(listeImagesJeu.at(numeroImage), y, x);
            numeroImage++;
        }
    }

    //définir le fond
    zoneCentrale->setObjectName("zone1");
    zoneCentrale->setStyleSheet("QWidget#zone1 { border-image: url(:/Images/fond.jpg); }");

    zoneCentrale->setLayout(grilleJeu);
    setCentralWidget(zoneCentrale);

    chargerSettings("FenJeu");
}


/**********Mettre en mémoire la dernière carte retournée**********/
void FenPrincipale::setDerniereCarte(LabelImageJeu* derniereCarte)
{
    m_derniereCarte = derniereCarte;
}


/**********Générer un notre random**********/
int FenPrincipale::nombreRandom(QList<int> &nombres)
{
    int nombreRandom = rand()% nombres.count();
    int nombreTableau = nombres.at(nombreRandom);
    nombres.removeAt(nombreRandom);

    return nombreTableau;
}


/**********Gagné**********/
void FenPrincipale::gagne()
{
    int cartes(0);

    for(int i = 0; i < 36; i++) //regarder si une carte est encore à trouver = false
    {
        if(listeImagesJeu.at(i)->trouver() == false)
        {
            cartes++;
        }
    }

    if(cartes == 0) //si aucune, on changement pour l'interface de départ
    {
        //enregistrerSettings("FenJeu");

        delete zoneCentrale;
        listeImagesJeu.clear();

        zoneCentrale = new QWidget;
        zoneCentrale->setStyleSheet("border-image: url(:/Images/start.jpg);");

        setCentralWidget(zoneCentrale);
        chargerSettings("FenBase");
    }
}


/**********Compter cartes retournées**********/
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


/**********Retourner la dernière carte retournée**********/
LabelImageJeu* FenPrincipale::derniereCarte()
{
    return m_derniereCarte;
}


/**********Enregistrer les settings**********/
void FenPrincipale::enregistrerSettings(QString nomFenetre)
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup(nomFenetre);
    QString nom = "position" + nomFenetre;
    settings.setValue(nom, this->geometry());
    settings.endGroup();
}


/**********Charger les settings**********/
void FenPrincipale::chargerSettings(QString nomFenetre)
{
    QDesktopWidget bureau; //center la fenetre (trouver les coordonnées)
    QRect surface_bureau = bureau.screenGeometry();
    int x = surface_bureau.width()/2 - width()/2;
    int y = surface_bureau.height()/2 - height()/2;
    int h = surface_bureau.height();

    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup(nomFenetre);
    QString nom = "position" + nomFenetre;
    QRect maPosition = settings.value(nom).toRect();
    if(maPosition.isEmpty()) //si le fichier .ini est vide
        {
            if(nomFenetre == "FenBase"){
                maPosition.setRect(x, y, 800, 600);
            }
            if(nomFenetre == "FenJeu"){
                maPosition.setRect(x, y, 600, h);
            }
        }
    setGeometry(maPosition);
    settings.endGroup();
}


/**********Slot quitter personnalisé**********/
void FenPrincipale::quitter()
{
    if(listeImagesJeu.isEmpty()){ //enregistrer la position de la fenêtre avant de quitter
        enregistrerSettings("FenBase");
    }
    else{
        enregistrerSettings("FenJeu");
    }

    qApp->quit();
}


/**********Réimplémentation de l'event close(croix rouge)**********/
void FenPrincipale::closeEvent(QCloseEvent *event)
{
    if(listeImagesJeu.isEmpty()){ //enregistrer la position de la fenêtre avant de quitter
        enregistrerSettings("FenBase");
    }
    else{
        enregistrerSettings("FenJeu");
    }

    event->accept();
}


/**********Afficher about du jeu**********/
void FenPrincipale::afficherAbout()
{
    About *fenetreAbout = new About(this);
        fenetreAbout->exec();
}
