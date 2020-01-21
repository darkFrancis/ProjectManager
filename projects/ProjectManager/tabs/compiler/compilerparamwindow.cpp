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
    open_param(COMPILE_OVERALL);
}

void CompilerParamWindow::on_toolButton_languageCOptions_clicked()
{
    open_param(COMPILE_LANGUAGE_C);
}

void CompilerParamWindow::on_toolButton_languageCxxOptions_clicked()
{
    open_param(COMPILE_LANGUAGE_CXX);
}

void CompilerParamWindow::selected(QString kw, QString option)
{
    if(kw == COMPILE_OVERALL)
    {
        add_option(ui->lineEdit_overallOptions, option);
    }
    else if(kw == COMPILE_LANGUAGE_C)
    {
        add_option(ui->lineEdit_languageCOptions, option);
    }
    else if(kw == COMPILE_LANGUAGE_CXX)
    {
        add_option(ui->lineEdit_languageCxxOptions, option);
    }
    else
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Mot clé non reconnu !");
    }
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

void CompilerParamWindow::open_param(QString kw)
{
    ParamSelectionWindow* w = new ParamSelectionWindow(this, kw);
    connect(w, &ParamSelectionWindow::selected, this, &CompilerParamWindow::selected);
    w->setAttribute(Qt::WA_QuitOnClose, false);
    w->setWindowModality(Qt::ApplicationModal);
    w->show();
}
