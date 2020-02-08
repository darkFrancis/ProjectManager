/**
 * @file tabgit.cpp
 * @brief Définition de la classe TabGit
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "tabgit.hpp"
#include "ui_tabgit.h"

#include <QDir>
#include <QProcess>
#include "context.hpp"
#include "logger.hpp"

/**
 * @param parent Le QWidget parent de cet onglet
 *
 * Contructeur de la classe TabDoxygen. Il hérite de celui de Tab et utilise
 * le système des fichiers d'interface utilisateur.@n
 * Ce constructeur écrit le texte correspondant à la présence ou non du dossier
 * Git donné par l'instance Context.@n
 * Voir @ref CONTEXT_GET, Ui.
 */
TabGit::TabGit(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabGit)
{
    ui->setupUi(this);
    logger(__PRETTY_FUNCTION__);
    QDir git_dir(Context::Instance()->gitPath());
    if(!git_dir.exists())
    {
        m_git_exists = false;
        ui->pushButton->setText("Créer le dossier Git");
    }
    else
    {
        m_git_exists = true;
    }
}

/**
 * Destructeur de la classe TabGit.
 */
TabGit::~TabGit()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Git de la fenêtre.@n
 * Si le dossier Git n'existe pas, le créé, sinon, démarre GitKraken.
 */
void TabGit::on_pushButton_clicked()
{
    logger(__PRETTY_FUNCTION__);
    if(!m_git_exists)
    {
        QProcess process;
        process.setWorkingDirectory(Context::Instance()->gitPath());
        process.start("git init");
        if(!process.waitForFinished())
        {
            throw(QString("Erreur, impossible d'initialiser le répertoire Git"));
        }
        ui->pushButton->setText("Lancer GitKraken");
    }
    else
    {
        QProcess process;
        process.startDetached("gitkraken -p " + Context::Instance()->gitPath() + " &");
    }
}
