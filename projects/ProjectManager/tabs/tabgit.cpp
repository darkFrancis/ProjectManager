#include "tabgit.hpp"
#include "ui_tabgit.h"

TabGit::TabGit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabGit)
{
    ui->setupUi(this);
}

TabGit::~TabGit()
{
    delete ui;
}
