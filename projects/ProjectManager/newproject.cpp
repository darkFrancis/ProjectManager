#include "newproject.hpp"
#include "ui_newproject.h"
#include "context.hpp"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

NewProject::NewProject(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewProject)
{
    ui->setupUi(this);

    this->setWindowTitle("Nouveau Projet");
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
    Context::Instance()->setLastSearch(dir.absolutePath());
}

void NewProject::on_toolButton_doxyfile_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Doxyfile", Context::Instance()->lastSearch());
    QFileInfo file(file_name);
    ui->lineEdit_doxyfile->setText(file.absolutePath());
    Context::Instance()->setLastSearch(file.absoluteDir().absolutePath());
}

void NewProject::on_pushButton_cancel_clicked()
{
    this->close();
}

void NewProject::on_pushButton_create_clicked()
{
    if(ui->lineEdit_doxyfile->text().isEmpty() ||
       ui->lineEdit_mainGitDir->text().isEmpty() ||
       ui->lineEdit_projectName->text().isEmpty())
    {
        QMessageBox::information(this,
                                 "Attention",
                                 "Les champs doivent tous être complétés");
    }

    QString dir = ui->lineEdit_mainGitDir->text();
    if(dir[dir.length()-1] != QChar('/'))
    {
        dir.append(QChar('/'));
    }
    QString file_name = ui->lineEdit_projectName->text();
    if(file_name.right(FILE_EXTENSION.length()) != FILE_EXTENSION)
    {
        file_name.append(FILE_EXTENSION);
    }
    QFile file(dir + file_name);
    if(file.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << "# Project file" << endl;
        stream << "doxyfile=" << ui->lineEdit_doxyfile->text() << endl;
        stream << "git_dir=" << ui->lineEdit_mainGitDir->text() << endl;
        stream << endl;
        stream << "#Next infos to add with ProjectManager";

        file.close();
        emit created(dir + file_name);
        this->close();
    }
    else
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Impossible de créer le fichier de projet");
    }
}
