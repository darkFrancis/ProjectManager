#include "inc/gui/NewWindow.hpp"
#include "ui_NewWindow.h"

NewWindow::NewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewWindow)
{
    ui->setupUi(this);
}

NewWindow::~NewWindow()
{
    delete ui;
}
