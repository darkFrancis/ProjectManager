/**
 * @file MainWindow.cpp
 * @brief Source de la fenêtre principale
 * @author Dark Francis
 * @date 25/10/2020
 */
#include "gui/MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include <QShortcut>

#include "gui/tabs/TabDoxygen.hpp"
#include "gui/tabs/TabGit.hpp"
#include "version/version.hpp"
#include "tools/Context.hpp"
#include "Logger/Logger.hpp"

#define ActionOnTabs(action) \
    do { QStringList errList; \
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
    }} while(false)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setEnabled(false);
    ui->label_currentProject->setHidden(true);

    // Ajout tabs
    TabGit* tabGit = new TabGit(this);
    TabDoxygen* tabDoxygen = new TabDoxygen(this);
    ui->tabWidget->addTab(tabGit, "Git");
    ui->tabWidget->addTab(tabDoxygen, "Doxygen");

    // Connections
    connect(tabGit, &Tab::status, ui->statusBar, &QStatusBar::showMessage);
    connect(tabDoxygen, &Tab::status, ui->statusBar, &QStatusBar::showMessage);

    // Gestion shortcut
    QShortcut* shortAbout = new QShortcut(QKeySequence(Qt::Key_F1), this);
    QShortcut* shortAbout2 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F1), this);
    connect(shortAbout, &QShortcut::activated, this, &MainWindow::on_actionAbout_triggered);
    connect(shortAbout2, &QShortcut::activated, this, &MainWindow::on_actionAbout_triggered);

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
                       "Version : " + _VERSION_ +
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
