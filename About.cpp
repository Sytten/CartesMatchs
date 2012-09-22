#include "About.h"
#include "FenPrincipale.h"

About::About(FenPrincipale *parent): QDialog(parent)
{
    m_fermer = new QPushButton("Fermer");
    m_nom = new QLabel("CartesMatchs");
        m_nom->setFont(QFont("Comic Sans MS", 20));
    m_icone = new QLabel();
        m_icone->setPixmap(QPixmap(":/Images/icone.png"));
    QString texte = "Ce jeu à été réalisé par <strong>Sytten</strong> (programmation) et <strong>Raph</strong> (graphisme)";
        texte += "<br />avec la précieuse aide de <a href=\"http://www.developpez.net/forums/u329028/winjerome\">Winjerome</a> et <a href=\"http://www.developpez.net/forums/u268393/gbdivers\">gbdivers</a> du forum developpez.net.";
        texte += "<br />Merci à vous deux!<br /><br />Ce jeu à été créé avec Qt 4.7.4 et est sous licence <strong>GPL</strong><br />Pour voir le code source, veuillez cliquer <a href=\"https://github.com/Sytten/CartesMatchs\">ici</a>";
    m_texte = new QLabel(texte);
        m_texte->setTextFormat(Qt::RichText);
        m_texte->setTextInteractionFlags(Qt::TextBrowserInteraction);
        m_texte->setOpenExternalLinks(true);
    QFrame* ligne = new QFrame();
        ligne->setFrameShape(QFrame::HLine);
        ligne->setFrameShadow(QFrame::Sunken);

    QHBoxLayout* layoutTop = new QHBoxLayout;
        layoutTop->addWidget(m_icone);
        layoutTop->addWidget(m_nom);

    QVBoxLayout* layoutCentral = new QVBoxLayout;
        layoutCentral->addLayout(layoutTop);
        layoutCentral->addWidget(ligne);
        layoutCentral->addWidget(m_texte);
        layoutCentral->addWidget(m_fermer);
            layoutCentral->setAlignment(m_fermer, Qt::AlignCenter);

    setLayout(layoutCentral);

    connect(m_fermer, SIGNAL(clicked()), this, SLOT(close()));
}
