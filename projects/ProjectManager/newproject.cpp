#include "newproject.hpp"
#include "ui_newproject.h"
#include "context.hpp"
#include "settings/logger.hpp"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

NewProject::NewProject(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewProject)
{
    ui->setupUi(this);
    logger(__PRETTY_FUNCTION__);

    Context* ctx = Context::Instance();
    ui->lineEdit_projectName->setText("Project");
    QString dir = ctx->lastSearch();
    if(dir.at(dir.length()-1) != '/') dir.append('/');
    ui->lineEdit_mainGitDir->setText(dir + ".git");
    ui->lineEdit_doxyfile->setText(dir + "Doxyfile");
    initComboType(ui->comboBox_projectType);
    ui->comboBox_projectType->setCurrentIndex(0);
}

NewProject::~NewProject()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
}

void NewProject::on_toolButton_projectDir_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QString dir_name = QFileDialog::getExistingDirectory(this, "Dossier de projet", Context::Instance()->lastSearch());
    QDir dir(dir_name);
    ui->lineEdit_projectDir->setText(dir.absolutePath());
    Context::Instance()->setLastSearch(dir.absolutePath());
}

void NewProject::on_toolButton_mainGitDir_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QString dir_name = QFileDialog::getExistingDirectory(this, "Dossier GIT", Context::Instance()->lastSearch());
    QDir dir(dir_name);
    ui->lineEdit_mainGitDir->setText(dir.absolutePath());
    Context::Instance()->setLastSearch(dir.absolutePath());
}

void NewProject::on_toolButton_doxyfile_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QString file_name = QFileDialog::getSaveFileName(this, "Doxyfile", Context::Instance()->lastSearch());
    QFileInfo file(file_name);
    ui->lineEdit_doxyfile->setText(file.absoluteFilePath());
    Context::Instance()->setLastSearch(file.absoluteDir().absolutePath());
}

void NewProject::on_pushButton_cancel_clicked()
{
    logger(__PRETTY_FUNCTION__);
    this->close();
}

void NewProject::on_pushButton_create_clicked()
{
    logger(__PRETTY_FUNCTION__);
    if(ui->lineEdit_doxyfile->text().isEmpty() ||
       ui->lineEdit_mainGitDir->text().isEmpty() ||
       ui->lineEdit_projectName->text().isEmpty() ||
       ui->lineEdit_projectDir->text().isEmpty())
    {
        QMessageBox::information(this,
                                 "Attention",
                                 "Les champs doivent tous être complétés");
        return;
    }

    QString dir_git = ui->lineEdit_mainGitDir->text();
    QString dir_pro = ui->lineEdit_projectDir->text();
    if(dir_pro[dir_pro.length()-1] != QChar('/'))
    {
        dir_pro.append(QChar('/'));
    }
    if(dir_git[dir_git.length()-1] != QChar('/'))
    {
        dir_git.append(QChar('/'));
    }
    dir_git.append(".git");
    QString file_name = ui->lineEdit_projectName->text();
    if(file_name.right(FILE_EXTENSION.length()) != FILE_EXTENSION)
    {
        file_name.append(FILE_EXTENSION);
    }
    QFile file(dir_pro + file_name);
    if(file.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << "# Project file" << endl;
        stream << KW_PROJECT_NAME << "=" << ui->lineEdit_projectName->text() << endl;
        stream << KW_PROJECT_TYPE << "=" << label2type(ui->comboBox_projectType->currentText()) << endl;
        stream << KW_GIT_PATH << "=" << dir_git << endl;
        stream << KW_DOXYFILE << "=" << ui->lineEdit_doxyfile->text() << endl;
        stream << endl;
        stream << "#Next infos will be added by ProjectManager";

        file.close();

        Context::Instance()->setProjectFile(dir_pro + file_name);
        emit created();
        this->close();
    }
    else
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Impossible de créer le fichier de projet");
    }
}
