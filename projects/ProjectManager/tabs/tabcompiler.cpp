#include "tabcompiler.hpp"
#include "ui_tabcompiler.h"

TabCompiler::TabCompiler(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabCompiler)
{
    ui->setupUi(this);
}

TabCompiler::~TabCompiler()
{
    delete ui;
}
