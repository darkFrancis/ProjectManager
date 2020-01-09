#include "tabproject.hpp"
#include "ui_tabproject.h"
#include <QMessageBox>

TabProject::TabProject(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabProject)
{
    ui->setupUi(this);
}

TabProject::~TabProject()
{
    delete ui;
}

void TabProject::on_pushButton_default_clicked()
{
    QMessageBox::StandardButtons rep;
    rep = QMessageBox::question(this,
                                "Valeurs par défaut",
                                "Etes vous sûr de vouloir restaurer les valeurs par défaut ?"
                                "Toutes les valeurs de cette fenêtre seront effacées.");
    if(rep == QMessageBox::Yes)
    {
        clean();
    }
}

void TabProject::on_pushButton_apply_clicked()
{
    emit apply(this);
}

void TabProject::clean()
{
    ui->lineEdit_author->setText("Unknow");
    ui->lineEdit_version->setText("0.0");
    ui->lineEdit_projectName->setText("My Project");
    ui->textEdit->setText("Description du projet");
}

QStringList TabProject::getInfo()
{
    QStringList ret;
    ret << "projectname=" + ui->lineEdit_projectName->text();
    ret << "author=" + ui->lineEdit_author->text();
    ret << "version=" + ui->lineEdit_version->text();
    ret << "description=" + ui->textEdit->toPlainText();
    return ret;
}
