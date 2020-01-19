#include "compilerparamwindow.hpp"
#include "ui_compilerparamwindow.h"
#include "paramselectionwindow.hpp"
#include "settings/settings.hpp"
#include <QMessageBox>

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

void CompilerParamWindow::on_toolButton_overallOptions_clicked()
{
    ParamSelectionWindow* w = new ParamSelectionWindow(this, COMPILE_OVERALL);
    connect(this, &CompilerParamWindow::destroyed, w, &ParamSelectionWindow::close);
    connect(w, &ParamSelectionWindow::selected, this, &CompilerParamWindow::overall_selected);
    w->show();
}

void CompilerParamWindow::overall_selected(QString option)
{
    add_option(ui->lineEdit_overallOptions, option);
}

void CompilerParamWindow::on_toolButton_languageCOptions_clicked()
{
    ParamSelectionWindow* w = new ParamSelectionWindow(this, COMPILE_LANGUAGE_C);
    connect(this, &CompilerParamWindow::destroyed, w, &ParamSelectionWindow::close);
    connect(w, &ParamSelectionWindow::selected, this, &CompilerParamWindow::language_c_selected);
    w->show();
}

void CompilerParamWindow::language_c_selected(QString option)
{
    add_option(ui->lineEdit_languageCOptions, option);
}

void CompilerParamWindow::on_toolButton_languageCxxOptions_clicked()
{
    ParamSelectionWindow* w = new ParamSelectionWindow(this, COMPILE_LANGUAGE_CXX);
    connect(this, &CompilerParamWindow::destroyed, w, &ParamSelectionWindow::close);
    connect(w, &ParamSelectionWindow::selected, this, &CompilerParamWindow::language_cxx_selected);
    w->show();
}

void CompilerParamWindow::language_cxx_selected(QString option)
{
    add_option(ui->lineEdit_languageCxxOptions, option);
}

void CompilerParamWindow::add_option(QLineEdit *line_edit, QString option)
{
    QStringList options = line_edit->text().split(QChar(' '));
    if(options.contains(option))
    {
        QMessageBox::warning(this,
                             "Attention",
                             "Attention, cette option est présente en plsieurs exemplaires.");
    }
    line_edit->setText(line_edit->text() + " " + option);
}
