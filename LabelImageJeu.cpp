#include "LabelImageJeu.h"
#include "FenPrincipale.h"

/***********Le constructeur**********/
LabelImageJeu::LabelImageJeu(int numeroImage): QLabel(), m_numeroImage(numeroImage)
{
    //Initialisation d'attributs
    m_trouver = false;
    m_voitFace = false;

    //On affiche l'endo
    setPixmap(QPixmap(":/Images/endo.jpg"));

}


/**********Réimplémentation de la fonction mousePressEvent***********/
void LabelImageJeu::mousePressEvent(QMouseEvent *event)
{  
    if (event->button() == Qt::LeftButton && m_trouver != true)
    {
        pFenPrincipale = qobject_cast<FenPrincipale*>(parent()->parent());

        if(pFenPrincipale)
        {
            int nombreCartesRetournees = pFenPrincipale->cartesRetournees();

            //Si aucune carte retournée
            if(nombreCartesRetournees == 0)
            {
                retourner();
                pFenPrincipale->setDerniereCarte(this);
            }

            //Si une carte retournée
            if(nombreCartesRetournees == 1)
            {
                retourner();

                //on vérifie si les deux images sont pareilles
                    pDerniereCarte = pFenPrincipale->derniereCarte();
                if(pDerniereCarte)
                {
                    if(pDerniereCarte->m_numeroImage == m_numeroImage && pDerniereCarte != this)
                    {
                        m_trouver = true;
                        pDerniereCarte->m_trouver = true;

                        pFenPrincipale->gagne();
                    }

                    else
                    {
                        qApp->processEvents();
                        QTimer::singleShot(1200, this, SLOT(continuerRetourner()));
                    }
                }
            }
        }
    }
}


/**********Accès à attribut m_trouver**********/
bool LabelImageJeu::trouver()
{
    return m_trouver;
}


/**********Accès à attribut m_voitFace**********/
bool LabelImageJeu::voitFace()
{
    return m_voitFace;
}


/**********Retourner la carte**********/
void LabelImageJeu::retourner()
{
    if(m_voitFace)
    {
      setPixmap(QPixmap(":/Images/endo.jpg"));
    }

    else
    {
        QString filepath(":/Cartes/cartes/carte%1.jpg");
        setPixmap(QPixmap(filepath.arg(m_numeroImage)));
    }
    m_voitFace = !m_voitFace ;
}


/**********Slot appelé après 1,2 sec**********/
void LabelImageJeu::continuerRetourner()
{
    retourner();
    pDerniereCarte->retourner();

    pFenPrincipale->setDerniereCarte(0);
}

void LabelImageJeu::setTrouver(bool trouver)
{
   m_trouver = trouver;
}
