#include "brancheswindow.hpp"
#include "ui_brancheswindow.h"

BranchesWindow::BranchesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BranchesWindow)
{
    ui->setupUi(this);
}

BranchesWindow::~BranchesWindow()
{
    delete ui;
}
