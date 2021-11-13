/**
 * @file TabProject.cpp
 * @brief Source de l'onglet de projet
 * @author Dark Francis
 * @date 26/10/2020
 */
#include "gui/tabs/TabProject.hpp"
#include "ui_TabProject.h"

#include <QFileDialog>
#include <QMessageBox>

#include "tools/Context.hpp"

/**
 * @param parent QWidget parent
 *
 * Constructeur de la classe TabProject.
 */
TabProject::TabProject(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabProject)
{
    ui->setupUi(this);
}

/**
 * Destructeur de la classe TabProject.
 */
TabProject::~TabProject()
{
    delete ui;
}

/**
 * Initialise l'onglet projet. Remplit la listes des sous-projets.
 */
void TabProject::init()
{
    clean();
    qCtx->loadSubProjects();
    ui->listWidget_projects->addItems(qCtx->subProjects());
    emit projectListChange();
}

/**
 * Nettoie la liste des sous-projets.
 */
void TabProject::clean()
{
    ui->listWidget_projects->clear();
}

/**
 * Enregistre la liste des sous-projets.
 */
void TabProject::save()
{
    qCtx->saveSubProjects();
}

/**
 * Cette méthode est appelée par un clic sur le bouton "Ajouter".@n
 * Permet à l'utilisateur de sélectionner des projets à ajouter à
 * la liste des sous-projets.
 */
void TabProject::on_pushButton_add_clicked()
{
    QString projectFile = QFileDialog::getOpenFileName(this,
                                                       "Fichier de projet",
                                                       qCtx->lastSearch(),
                                                       "Projet Qt (CMakeLists.txt *.pro)");
    if(projectFile != "")
    {
        qCtx->setLastSearch(projectFile);
        projectFile = qCtx->pathFromProject(QFileInfo(projectFile).absoluteFilePath());
        for(int i = 0; i < ui->listWidget_projects->count(); i++)
        {
            if(ui->listWidget_projects->item(i)->text() == projectFile)
            {
                QMessageBox::warning(this,
                                     "Attention",
                                     "Ce projet est déjà présent !");
                return;
            }
        }
        qCtx->addSubProject(projectFile);
        ui->listWidget_projects->addItem(projectFile);
        ui->listWidget_projects->sortItems();
        emit projectListChange();
    }
}

/**
 * Supprime les sous-projets sélectionnés de la listes des sous-projets.
 */
void TabProject::on_pushButton_delete_clicked()
{
    QList<QListWidgetItem*> selection = ui->listWidget_projects->selectedItems();
    if(selection.length() > 0)
    {
        for(QListWidgetItem* item : selection)
        {
            if(qCtx->removeSubProject(item->text().trimmed()))
                delete item;
        }
        emit projectListChange();
    }
}
