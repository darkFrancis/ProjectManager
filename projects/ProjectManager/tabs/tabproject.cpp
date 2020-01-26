#include "tabproject.hpp"
#include "ui_tabproject.h"
#include <QMessageBox>
#include <QFileDialog>
#include "context.hpp"
#include "settings/logger.hpp"

TabProject::TabProject(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabProject)
{
    ui->setupUi(this);
    logger(__PRETTY_FUNCTION__);
}

TabProject::~TabProject()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
}

void TabProject::on_pushButton_default_clicked()
{
    logger(__PRETTY_FUNCTION__);
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
    logger(__PRETTY_FUNCTION__);
    save();
}

void TabProject::init()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    ui->lineEdit_projectName->setText((ctx->projectName()));
    ui->lineEdit_author->setText(ctx->projectAuthor());
    ui->lineEdit_version->setText(ctx->projectVersion());
    ui->lineEdit_git->setText(ctx->gitPath());
    ui->lineEdit_doxyfile->setText(ctx->doxyfile());
    ui->textEdit->setText(ctx->projectDescription());
    QString type;
    switch(ui->comboBox_projectType->currentIndex())
    {
        case 0:
            type = TYPE_C;
            break;
        case 1:
            type = TYPE_CXX;
            break;
        case 2:
            type = TYPE_LIBC;
            break;
        case 3:
            type = TYPE_LIBCXX;
            break;
        case 4:
            type = TYPE_SHAREDC;
            break;
        case 5:
            type = TYPE_SHAREDCXX;
            break;
        default:
            break;
    }
}

void TabProject::save()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    ctx->setProjectName(ui->lineEdit_projectName->text());
    ctx->setProjectAuthor(ui->lineEdit_author->text());
    ctx->setProjectVersion(ui->lineEdit_version->text());
    ctx->setGitPath(ui->lineEdit_git->text());
    ctx->setDoxyfile(ui->lineEdit_doxyfile->text());
    ctx->setProjectDescription(ui->textEdit->toPlainText());
    QString type;
    switch(ui->comboBox_projectType->currentIndex())
    {
        case 0:
            type = TYPE_C;
            break;
        case 1:
            type = TYPE_CXX;
            break;
        case 2:
            type = TYPE_LIBC;
            break;
        case 3:
            type = TYPE_LIBCXX;
            break;
        case 4:
            type = TYPE_SHAREDC;
            break;
        case 5:
            type = TYPE_SHAREDCXX;
            break;
        default:
            break;
    }
    ctx->setProjectType(type);
    ctx->save();
}

void TabProject::clean()
{
    logger(__PRETTY_FUNCTION__);
    ui->lineEdit_projectName->setText("My Project");
    ui->lineEdit_author->setText("Unknow");
    ui->lineEdit_version->setText("0.0");
    ui->lineEdit_doxyfile->setText("");
    ui->lineEdit_git->setText("");
    ui->textEdit->setText("Description du projet");
    ui->comboBox_projectType->setCurrentIndex(0);
}

void TabProject::on_toolButton_doxyfile_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QString file_name = QFileDialog::getSaveFileName(this, "Doxyfile", Context::Instance()->lastSearch());
    QFileInfo file(file_name);
    ui->lineEdit_doxyfile->setText(file.absolutePath());
    Context::Instance()->setLastSearch(file.absoluteDir().absolutePath());
}

void TabProject::on_toolButton_git_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QString dir_name = QFileDialog::getExistingDirectory(this, "Dossier GIT", Context::Instance()->lastSearch());
    QDir dir(dir_name);
    ui->lineEdit_git->setText(dir.absolutePath());
    Context::Instance()->setLastSearch(dir.absolutePath());
}
