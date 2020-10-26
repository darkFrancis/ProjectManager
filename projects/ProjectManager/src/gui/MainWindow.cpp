/**
 * @file MainWindow.cpp
 * @brief Definition de la fenêtre principale
 * @author Dark Francis
 * @date 25/10/2020
 */
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>

#include "TabDoxygen.hpp"
#include "TabGit.hpp"
#include "version.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->addTab(new Tab(this), "Projet");
    ui->tabWidget->addTab(new TabDoxygen(this), "Doxygen");
    ui->tabWidget->addTab(new TabGit(this), "Git");
    ui->tabWidget->addTab(new Tab(this), "Infos Qt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionPr_f_rences_triggered()
{

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,
                       "A propos de " + _APPLICATION_NAME_,
                       "<p>"
                       "Auteur : Dark Francis<br/>"
                       "Date de création : 21/12/2019"
                       "</p>");
}

void MainWindow::on_actionNouveau_triggered()
{

}

void MainWindow::on_actionOuvrir_triggered()
{

}

void MainWindow::on_actionEnregistrer_triggered()
{

}

void MainWindow::on_actionQuitter_triggered()
{

}
