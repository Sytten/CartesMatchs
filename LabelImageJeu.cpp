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
        FenPrincipale* pFenPrincipale = qobject_cast<FenPrincipale*>(parent());

        if(pFenPrincipale)
        {

            int nombreCartesRetournees = pFenPrincipale->cartesRetournees();

            //Si aucune carte retournée
            if(nombreCartesRetournees == 0)
            {
                retourner(this);

                m_voitFace = true;
                pFenPrincipale->setDerniereCarte(this);
            }

            //Si une carte retournée
            if(nombreCartesRetournees == 1)
            {
                retourner(this);
                m_voitFace = true;

                //on vérifie si les deux images sont pareilles
                    LabelImageJeu* pDerniereCarte = pFenPrincipale->derniereCarte();
                if(pDerniereCarte)
                {
                    if(pDerniereCarte->m_numeroImage == m_numeroImage)
                    {
                        m_trouver = true;
                        pDerniereCarte->m_trouver = true;

                        pFenPrincipale->gagne();
                    }

                    else
                    {
                        retourner(this);
                        retourner(pDerniereCarte);
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
void LabelImageJeu::retourner(LabelImageJeu* carte)
{
    if(carte->m_voitFace)
    {
        carte->setPixmap(QPixmap(":/Images/endo.jpg"));
        carte->m_voitFace = false;
    }

    if(!carte->m_voitFace)
    {
        QString filepath;
        filepath += ":/Cartes/cartes/carte" + carte->m_numeroImage;
        filepath += ".jpg";
        carte->setPixmap(QPixmap(filepath));
    }
}
