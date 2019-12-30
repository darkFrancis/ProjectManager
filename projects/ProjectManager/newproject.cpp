#include "newproject.hpp"
#include "ui_newproject.h"
#include "context.hpp"
#include <QFileDialog>

NewProject::NewProject(QWidget *parent, QString file) :
    QMainWindow(parent),
    ui(new Ui::NewProject)
{
    ui->setupUi(this);

    m_file = file;
    this->setWindowTitle("Nouveau fichier : " + file);
}

NewProject::~NewProject()
{
    delete ui;
}

void NewProject::on_toolButton_mainGitDir_clicked()
{
    QString dir_name = QFileDialog::getExistingDirectory(this, "Dossier GIT", Context::Instance()->lastSearch());
    QDir dir(dir_name);
    ui->lineEdit_mainGitDir->setText(dir.absolutePath());
}

void NewProject::on_toolButton_doxyfile_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Doxyfile", Context::Instance()->lastSearch());
    QFileInfo file(file_name);
    ui->lineEdit_doxyfile->setText(file.absolutePath());
}

void NewProject::on_pushButton_cancel_clicked()
{
    this->close();
}

void NewProject::on_pushButton_create_clicked()
{

}
