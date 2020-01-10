/**
 * @file tabcompiler.cpp
 */

#include "tabcompiler.hpp"
#include "ui_tabcompiler.h"

TabCompiler::TabCompiler(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabCompiler)
{
    /**
     * @brief Constructeur de TabCompiler
     * @param parent Le QWidget parent
     */
    ui->setupUi(this);
}
TabCompiler::~TabCompiler()
{

    /**
     * @brief Destructeur de TabCompiler
     */
    delete ui;
}
