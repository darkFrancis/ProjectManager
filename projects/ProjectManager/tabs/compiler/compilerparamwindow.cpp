#include "compilerparamwindow.hpp"
#include "ui_compilerparamwindow.h"

CompilerParamWindow::CompilerParamWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompilerParamWindow)
{
    ui->setupUi(this);
}

CompilerParamWindow::~CompilerParamWindow()
{
    delete ui;
}
