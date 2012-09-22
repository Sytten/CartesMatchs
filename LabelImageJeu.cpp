#include "LabelImageJeu.h"
#include "FenPrincipale.h"

/***********Le constructeur**********/
LabelImageJeu::LabelImageJeu(int numeroImage): QLabel(), m_numeroImage(numeroImage)
{
    //Initialisation d'attributs
    m_trouver = false;
    m_voitFace = false;

    //calcul de la taille d'image selon �cran
    QDesktopWidget bureau;
    QRect surface_bureau = bureau.screenGeometry();
    h = surface_bureau.height()/6 - 25;
    w = h;

    //On affiche l'endo
    QPixmap imageBase(":/Images/endo.jpg");
    imageBase = imageBase.scaled(w, h);
    setPixmap(imageBase);

}


/**********R�impl�mentation de la fonction mousePressEvent***********/
void LabelImageJeu::mousePressEvent(QMouseEvent *event)
{  
    if (event->button() == Qt::LeftButton && m_trouver != true)
    {
        pFenPrincipale = qobject_cast<FenPrincipale*>(parent()->parent());

        if(pFenPrincipale)
        {
            int nombreCartesRetournees = pFenPrincipale->cartesRetournees();

            //Si aucune carte retourn�e
            if(nombreCartesRetournees == 0)
            {
                retourner();
                pFenPrincipale->setDerniereCarte(this);
            }

            //Si une carte retourn�e
            if(nombreCartesRetournees == 1)
            {
                retourner();

                //on v�rifie si les deux images sont pareilles
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
                        QTimer::singleShot(1200, this, SLOT(continuerRetourner()));
                    }
                }
            }
        }
    }
}


/**********Acc�s � attribut m_trouver**********/
bool LabelImageJeu::trouver()
{
    return m_trouver;
}


/**********Acc�s � attribut m_voitFace**********/
bool LabelImageJeu::voitFace()
{
    return m_voitFace;
}


/**********Retourner la carte**********/
void LabelImageJeu::retourner()
{
    if(m_voitFace){ //si on voit la face
        QPixmap imageBase(":/Images/endo.jpg");
        imageBase = imageBase.scaled(w, h);
        setPixmap(imageBase);
    }

    else
    {
        QString filepath(":/Cartes/cartes/carte%1.jpg");
        QPixmap imageJeu(filepath.arg(m_numeroImage));
        imageJeu = imageJeu.scaled(w, h);
        setPixmap(imageJeu);
    }
    m_voitFace = !m_voitFace; //changer pour l'oppos� car on vient de faire une action plus haut
}


/**********Slot appel� apr�s 1,2 sec**********/
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
