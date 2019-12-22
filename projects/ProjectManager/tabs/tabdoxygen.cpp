#include "tabdoxygen.hpp"
#include "ui_tabdoxygen.h"

TabDoxygen::TabDoxygen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabDoxygen)
{
    ui->setupUi(this);
}

TabDoxygen::~TabDoxygen()
{
    delete ui;
}
