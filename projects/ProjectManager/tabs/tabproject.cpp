/**
 * @file tabproject.cpp
 * @brief Définition de la classe TabProject
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "tabproject.hpp"
#include "ui_tabproject.h"
#include <QMessageBox>
#include <QFileDialog>
#include "context.hpp"
#include "logger.hpp"

/**
 * @param parent Le QWidget parent de cet onglet
 *
 * Contructeur de la classe TabDoxygen. Il hérite de celui de Tab et utilise
 * le système des fichiers d'interface utilisateur.@n
 * Ce constructeur initialise sa liste déroulante contenant les type possible
 * de projet avec la fonction initComboType.@n
 * Voir Ui.
 */
TabProject::TabProject(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabProject)
{
    ui->setupUi(this);
    logger(__PRETTY_FUNCTION__);
    initComboType(ui->comboBox_projectType);
}

/**
 * Destructeur de la classe TabProject.
 */
TabProject::~TabProject()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
}

/**
 * Ce connecteurest activé par un clic souris de l'utilisateur sur le bouton Défaut.@n
 * Une fenêtre de confirmation est affiché à l'utilisateur. S'il confirme son action,
 * la fonction clean est appelée pour remettre les valeurs par défaut.
 */
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

/**
 * Ce connecteurest activé par un clic souris de l'utilisateur sur le bouton Appliquer.@n
 * La fonction save est appelée pour enregistrer les valeurs saisies par l'utilisateur.
 */
void TabProject::on_pushButton_apply_clicked()
{
    logger(__PRETTY_FUNCTION__);
    save();
}

/**
 * Fonction d'initialisation de l'onglet Projet.@n
 * Utilise les méthodes GET de l'instance Context pour remplir les différent champs de cet
 * onglet avec les valeurs du projet.@n
 * Voir @ref CONTEXT_GET, Ui.
 */
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
    ui->comboBox_projectType->setCurrentIndex(ui->comboBox_projectType->findText(type2label(ctx->projectType())));
}

/**
 * Fonction d'enregistrement de l'onglet Projet.@n
 * Utilise les méthodes SET de l'instance Context pour enregistrer les modifications apportées
 * par l'utilisateur sur l'onglet Projet. Puis appelle la fonction Context::save.@n
 * Voir @ref CONTEXT_SET, Ui.
 */
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
    ctx->setProjectType(label2type(ui->comboBox_projectType->currentText()));
    ctx->save();
}

/**
 * Fonction de nettoyage de l'onglet Projet.@n
 * Remet à zéro les valeurs de l'onglet projet:
 * @li Nom de Projet : @b My @b Project
 * @li Auteur : @b Unknown
 * @li Version : @b 0.0
 * @li Doxyfile : @e Vide
 * @li Chemin vers GIT : @e vide
 * @li Description du projet : @b Description @b du @b Projet
 * @li Type de projet : @b Application @b C
 */
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

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * du fichier Doxyfile.@n
 * Demande à l'utilisateur de sélectionner le fichier Doxyfile grâce à une boîte de
 * dialogue. Si un fichier est sélectionné, renseigne son chemin dans la ligne
 * d'édition associée.@n
 * Voir Ui.
 */
void TabProject::on_toolButton_doxyfile_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QString file_name = QFileDialog::getSaveFileName(this, "Doxyfile", Context::Instance()->lastSearch());
    if(file_name != "")
    {
        QFileInfo file(file_name);
        ui->lineEdit_doxyfile->setText(file.absolutePath());
        Context::Instance()->setLastSearch(file.absoluteDir().absolutePath());
    }
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * du dossier Git.@n
 * Demande à l'utilisateur de sélectionner le dossier GIT grâce à une boîte de
 * dialogue. Si un dossier est sélectionné, renseigne son chemin dans la ligne
 * d'édition associée.@n
 * Voir Ui.
 */
void TabProject::on_toolButton_git_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QString dir_name = QFileDialog::getExistingDirectory(this, "Dossier GIT", Context::Instance()->lastSearch());
    if(dir_name != "")
    {
        QDir dir(dir_name);
        dir_name = dir.absolutePath();
        if(dir_name[dir_name.length()-1] != QChar('/'))
        {
            dir_name.append('/');
        }
        ui->lineEdit_git->setText(dir_name);
        Context::Instance()->setLastSearch(dir.absolutePath());
    }
}
