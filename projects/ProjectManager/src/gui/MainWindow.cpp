/**
 * @file MainWindow.cpp
 * @brief Definition de la fenêtre principale
 * @author Dark Francis
 * @date 25/10/2020
 */
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>

#include "TabProject.hpp"
#include "TabDoxygen.hpp"
#include "TabGit.hpp"
#include "version.hpp"
#include "Context.hpp"
#include "Logger.hpp"

#define ActionOnTabs(action) \
    { QStringList errList; \
    for(int i = 0; i < ui->tabWidget->count(); i++) \
    { \
        try { reinterpret_cast<Tab*>(ui->tabWidget->widget(i))->action(); } \
        catch (QString msg) { errList << msg; } \
    } \
    if(errList.length() > 0) \
    { \
        QString msg = errList.join('\n'); \
        QMessageBox::critical(this, "Erreur", msg); \
        qLog->error(msg); \
    }}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setEnabled(false);
    ui->label_currentProject->setHidden(true);

    // Ajout tabs
    TabProject* tabProject = new TabProject(this);
    TabDoxygen* tabDoxygen = new TabDoxygen(this);
    TabGit* tabGit = new TabGit(this);
    ui->tabWidget->addTab(tabProject, "Projet");
    ui->tabWidget->addTab(tabDoxygen, "Doxygen");
    ui->tabWidget->addTab(tabGit, "Git");

    // Connections
    connect(tabProject, &TabProject::projectListChange, tabGit, &TabGit::updateProjectNames);

    // Init
    if(qCtx->projectDir() != "")
    {
        ActionOnTabs(init);
        enable();
    }
    setWindowTitle(_APPLICATION_NAME_ + " - " + _VERSION_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,
                       "A propos de " + _APPLICATION_NAME_,
                       QString("<p>") +
                       "Auteur : Dark Francis<br/>"
                       "Date de création : 21/12/2019<br/>"
                       "<br/>"
                       "Build : " +
                       D_BUILD_DAY + '/' + D_BUILD_MONTH + '/' + D_BUILD_YEAR +
                       ' ' + __TIME__[0]+__TIME__[1] + ':' + __TIME__[3]+__TIME__[4] + ':' + __TIME__[6]+__TIME__[7] +
                       "<br/>"
                       "Version : " + APP_VERSION +
                       "</p>");
}

void MainWindow::on_actionNouveau_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this,
                                                    "Répertoire de projet",
                                                    qCtx->projectDir());
    if(dir != "")
    {
        qCtx->setLastSearch(dir);
        QDir projectDir(QDir(dir).absoluteFilePath(qCtx->projectHiddenDirName()));
        if(projectDir.exists())
        {
            QMessageBox::warning(this,
                                 "Attention",
                                 "Ce dossier contient déjà un projet !\n"
                                 "Ce projet va s'ouvrir.");
        }
        else
        {
            projectDir.mkpath(".");
        }
        qCtx->setProjectDir(dir);
        ActionOnTabs(init);
        enable();
    }
}

void MainWindow::on_actionOuvrir_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this,
                                                    "Répertoire de projet",
                                                    qCtx->projectDir());
    if(dir != "")
    {
        qCtx->setLastSearch(dir);
        qCtx->setProjectDir(dir);
        ActionOnTabs(init);
        enable();
    }
}

void MainWindow::on_actionEnregistrer_triggered()
{
    ActionOnTabs(save);
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}

void MainWindow::enable()
{
    ui->tabWidget->setEnabled(true);
    ui->label_currentProject->setVisible(true);
    ui->label_currentProject->setText(qCtx->projectDir());
}
