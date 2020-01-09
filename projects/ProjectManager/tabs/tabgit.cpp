#include "tabgit.hpp"
#include "ui_tabgit.h"

#include <QDir>
#include <QProcess>
#include "context.hpp"

TabGit::TabGit(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabGit)
{
    ui->setupUi(this);
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

TabGit::~TabGit()
{
    delete ui;
}

void TabGit::on_pushButton_clicked()
{
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
        process.startDetached("gitkraken -p " + Context::Instance()->gitPath());
    }
}
