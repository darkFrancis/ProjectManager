/**
 * @file newproject.cpp
 * @brief Définition des fonctions de la classe NewProject
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "newproject.hpp"
#include "ui_newproject.h"
#include "context.hpp"
#include "logger.hpp"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

/**
 * @param parent Le QWidget parent de cette fenêtre
 *
 * Contructeur de la classe MainWindow.@n
 * Ce constructeur hérite de celui de QMainWindow et utilise le système des fichiers
 * d'interface utilisateur.@n
 * Ce constructeur va initialiser les différents champs requis pour la création d'un
 * nouveau projet à l'aide des méthodes GET de l'instance Context:
 * @li Nom de projet : @b Project
 * @li Dossier du projet : Context::m_last_search
 * @li Dossier Git : Context::m_last_search + @b ".git"
 * @li Fichier Doxygen : Context::m_last_search + @b "Doxyfile"
 * @li Type de projet : #TYPE_C
 *
 * Voir @ref CONTEXT_GET, Ui.
 */
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
    ui->lineEdit_projectDir->setText(dir);
    ui->lineEdit_doxyfile->setText(dir + "Doxyfile");
    initComboType(ui->comboBox_projectType);
    ui->comboBox_projectType->setCurrentIndex(0);
    this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_QuitOnClose, false);
}

/**
 * Desctructeur de la classe NewProject.
 */
NewProject::~NewProject()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
}

/**
 * Ce connecteur est activé par un clic souris par l'utilisateur sur le bouton
 * outil de recherche de dossier de projet.@n
 * Ouvre une fenêtre de recherche de dossier. Si l'utilisateur sélectionne un
 * dossier, sont chemin absolu est écrit dans la ligne d'édition correspondante
 * et se termine par le caractère @b '/'.
 */
void NewProject::on_toolButton_projectDir_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QString dir_name = QFileDialog::getExistingDirectory(this,
                                                         "Dossier de projet",
                                                         Context::Instance()->lastSearch());
    if(dir_name != QString(""))
    {
        QDir dir(dir_name);
        dir_name = dir.absolutePath();
        if(dir_name[dir_name.length()-1] != QChar('/'))
        {
            dir_name.append('/');
        }
        ui->lineEdit_projectDir->setText(dir_name);
        Context::Instance()->setLastSearch(dir.absolutePath());
    }
}

/**
 * Ce connecteur est activé par un clic souris par l'utilisateur sur le bouton
 * outil de recherche de fichier Doxygen.@n
 * Ouvre une fenêtre de recherche de fichier. Si l'utilisateur sélectionne un
 * fichier, sont chemin absolu est écrit dans la ligne d'édition correspondante.
 */
void NewProject::on_toolButton_doxyfile_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     "Doxyfile",
                                                     Context::Instance()->lastSearch());
    if(file_name != QString(""))
    {
        QFileInfo file(file_name);
        ui->lineEdit_doxyfile->setText(file.absoluteFilePath());
        Context::Instance()->setLastSearch(file.absoluteDir().absolutePath());
    }
}

/**
 * Ce connecteur est activé par un clic souris par l'utilisateur sur le bouton
 * Annuler.@n
 * Ferme cette fenêtre.
 */
void NewProject::on_pushButton_cancel_clicked()
{
    logger(__PRETTY_FUNCTION__);
    this->close();
}

/**
 * Ce connecteur est activé par un clic souris par l'utilisateur sur le bouton
 * Créer.@n
 * Si toutes les lignes de cette fenêtre ont été renseignées, génére un fichier
 * projet de la forme &lt;nom de projet>.#FILE_EXTENSION. Renseigne les différents
 * champs de cette fenêtre dans ce fichier avec les mots clés associés. Une fois
 * le fichier de projet généré, émet le signal NewwProject::created puis ferme
 * cette fenêtre.@n
 * Voir @ref PROJECT_FLAGS.
 */
void NewProject::on_pushButton_create_clicked()
{
    logger(__PRETTY_FUNCTION__);
    if(ui->lineEdit_doxyfile->text().isEmpty() ||
       ui->lineEdit_projectName->text().isEmpty() ||
       ui->lineEdit_projectDir->text().isEmpty())
    {
        QMessageBox::information(this,
                                 "Attention",
                                 "Les champs doivent tous être complétés");
        return;
    }

    QString dir_pro = ui->lineEdit_projectDir->text();
    QString file_name = ui->lineEdit_projectName->text();
    if(file_name.right(FILE_EXTENSION.length()) != FILE_EXTENSION)
    {
        file_name.append(FILE_EXTENSION);
    }
    QFile file(dir_pro + file_name);
    if(file.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly))
    {
        logger("    label=" + ui->comboBox_projectType->currentText());
        logger("    type=" + label2type(ui->comboBox_projectType->currentText()));
        QTextStream stream(&file);
        stream << "# Project file" << endl
               << KW_PROJECT_NAME << "=" << ui->lineEdit_projectName->text() << endl
               << KW_PROJECT_TYPE << "=" << label2type(ui->comboBox_projectType->currentText()) << endl
               << KW_DOXYFILE << "=" << ui->lineEdit_doxyfile->text() << endl
               << KW_BUILD_DIR << "=" << dir_pro << "build/" <<endl
               << KW_OUTPUT << "=" << dir_pro << "out/" << endl
               << endl
               << "#Next infos will be added by ProjectManager";

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
