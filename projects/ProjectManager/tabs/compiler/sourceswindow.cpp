#include "sourceswindow.hpp"
#include "ui_sourceswindow.h"

SourcesWindow::SourcesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SourcesWindow)
{
    ui->setupUi(this);
}

SourcesWindow::~SourcesWindow()
{
    delete ui;
}
