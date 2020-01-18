#include "tabproject.hpp"
#include "ui_tabproject.h"
#include <QMessageBox>
#include <QFileDialog>
#include "context.hpp"

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
    /**
      @todo
      */
}

void TabProject::init()
{
    Context* ctx = Context::Instance();
    ui->lineEdit_author->setText(ctx->projectAuthor());
}

void TabProject::clean()
{
    ui->lineEdit_author->setText("Unknow");
    ui->lineEdit_version->setText("0.0");
    ui->lineEdit_projectName->setText("My Project");
    ui->lineEdit_doxyfile->setText("");
    ui->lineEdit_git->setText("");
    ui->textEdit->setText("Description du projet");
}

void TabProject::on_toolButton_doxyfile_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Doxyfile", Context::Instance()->lastSearch());
    QFileInfo file(file_name);
    ui->lineEdit_doxyfile->setText(file.absolutePath());
    Context::Instance()->setLastSearch(file.absoluteDir().absolutePath());
}

void TabProject::on_toolButton_git_clicked()
{
    QString dir_name = QFileDialog::getExistingDirectory(this, "Dossier GIT", Context::Instance()->lastSearch());
    QDir dir(dir_name);
    ui->lineEdit_git->setText(dir.absolutePath());
    Context::Instance()->setLastSearch(dir.absolutePath());
}
