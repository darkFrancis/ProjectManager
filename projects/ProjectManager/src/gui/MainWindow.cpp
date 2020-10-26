/**
 * @file MainWindow.cpp
 * @brief Definition de la fenêtre principale
 * @author Dark Francis
 * @date 25/10/2020
 */
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "TabDoxygen.hpp"
#include "TabGit.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->addTab(new QWidget(this), "Projet");
    ui->tabWidget->addTab(new TabDoxygen(this), "Doxygen");
    ui->tabWidget->addTab(new TabGit(this), "Git");
    ui->tabWidget->addTab(new QWidget(this), "Infos Qt");
}

MainWindow::~MainWindow()
{
    delete ui;
}
