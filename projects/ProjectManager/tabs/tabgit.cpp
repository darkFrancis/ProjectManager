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
 * Voir Ui.
 */
TabGit::TabGit(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabGit)
{
    ui->setupUi(this);
    logger(__PRETTY_FUNCTION__);
}

/**
 * Destructeur de la classe TabGit.
 */
TabGit::~TabGit()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
}

void TabGit::init()
{

}

void TabGit::clear()
{
    ui->listWidget_staged->clear();
    ui->listWidget_unstaged->clear();
    ui->checkBox_amend->setChecked(false);
    ui->lineEdit_commit->clear();
    ui->comboBox_branch->clear();
}

void TabGit::on_pushButton_commit_clicked()
{

}

void TabGit::on_checkBox_amend_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        /**
          * @todo Récupérer dernier commit pour ajout à la description
          */
    }
    else
    {
        ui->lineEdit_commit->clear();
        ui->lineEdit_commit->setPlaceholderText(GIT_COMMIT_PLACEHOLDER);
    }
}

void TabGit::on_comboBox_branch_currentTextChanged(const QString &arg1)
{

}

void TabGit::on_toolButton_branch_clicked()
{

}

void TabGit::on_pushButton_add_clicked()
{

}

void TabGit::on_pushButton_reset_clicked()
{

}

void TabGit::on_pushButton_checkout_clicked()
{

}

void TabGit::on_pushButton_gitk_clicked()
{

}

void TabGit::on_pushButton_tags_clicked()
{

}

void TabGit::on_pushButton_push_clicked()
{

}

void TabGit::on_pushButton_fetch_clicked()
{

}

void TabGit::on_pushButton_rebase_clicked()
{

}
