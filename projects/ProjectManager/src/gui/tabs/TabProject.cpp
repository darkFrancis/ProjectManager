#include "TabProject.hpp"
#include "ui_TabProject.h"

#include <QFileDialog>
#include <QMessageBox>

#include "Context.hpp"

TabProject::TabProject(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabProject)
{
    ui->setupUi(this);
}

TabProject::~TabProject()
{
    delete ui;
}

void TabProject::init()
{
    clean();
    qCtx->loadSubProjects();
    ui->listWidget_projects->addItems(qCtx->subProjects());
}

void TabProject::clean()
{
    ui->listWidget_projects->clear();
}

void TabProject::save()
{
    qCtx->saveSubProjects();
}

void TabProject::on_pushButton_add_clicked()
{
    QString projectFile = QFileDialog::getOpenFileName(this,
                                                       "Fichier de projet",
                                                       qCtx->lastSearch(),
                                                       "Projet Qt (*.pro)");
    if(projectFile != "")
    {
        qCtx->setLastSearch(projectFile);
        projectFile = QFileInfo(projectFile).absoluteFilePath();
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
    }
}

void TabProject::on_pushButton_delete_clicked()
{
    QList<QListWidgetItem*> selection = ui->listWidget_projects->selectedItems();
    for(QListWidgetItem* item : selection)
    {
        if(qCtx->removeSubProject(item->text().trimmed()))
            delete item;
    }
}
