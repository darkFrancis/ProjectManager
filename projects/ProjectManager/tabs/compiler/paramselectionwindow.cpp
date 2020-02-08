/**
 * @file paramselectionwindow.cpp
 * @brief Définition de la classe ParamSelectionWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "paramselectionwindow.hpp"
#include "ui_paramselectionwindow.h"
#include "settings.hpp"
#include "logger.hpp"
#include <QMessageBox>
#include <QStandardItemModel>

/**
 * @param parent Le QWidget parent de cette fenêtre
 * @param param_type Mot clé de paramètre de compilation
 *
 * Contructeur de la classe ParamSelectionWindow.@n
 * Ce constructeur hérite de celui de QMainWindow et utilise le système des fichiers
 * d'interface utilisateur.@n
 * La liste de paramètres est remplie en fonction du mot clé @c param_type. Ce mot clé
 * permet de charger une liste d'option par défaut grâce aux fonctions GET de l'instance
 * Settings. Une liste à deux colonnes est ensuite complétée avec ces informations.
 * @li La première colonne fait référence à l'option à passer en paramètre au compilateur
 * @li La deuxième colonne fait référence à la description brève de cette option
 * @li Le tooltip affiché en passant la souris au dessus de ces champs est la description
 * complète de cette option
 *
 * La première colonne est redimentionnée automatiquement en fonction de ces informations
 * car celles-ci sont d'une importance majeure. La deuxième colonne se redimentionne
 * automatiquement avec la fenêtre. Ensuite, la première ligne est sélectionnée par défaut.
 * La sélection est forcée en mode sélection de ligne et non sélection de cellule (option
 * par défaut).@n
 * Voir @ref KW_COMPILE, @ref SETTING_GET, @ref HTML_TAG, Ui.
 */
ParamSelectionWindow::ParamSelectionWindow(QWidget *parent, QString param_type) :
    QMainWindow(parent),
    ui(new Ui::ParamSelectionWindow)
{
    ui->setupUi(this);
    logger(__PRETTY_FUNCTION__);
    m_kw = param_type;

    QList<CompilerOption>* option_list = nullptr;
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList() << "Option" << "Description");
    if(m_kw == COMPILE_OVERALL)
    {
        option_list = Settings::Instance()->overallOptions();
    }
    else if(m_kw == COMPILE_LANGUAGE_C)
    {
        option_list = Settings::Instance()->languageCOptions();
    }
    else if(m_kw == COMPILE_LANGUAGE_CXX)
    {
        option_list = Settings::Instance()->languageCxxOptions();
    }
    else if(m_kw == COMPILE_DIAGNOSTIC)
    {
        option_list = Settings::Instance()->diagnosticOptions();
    }
    else if(m_kw == COMPILE_WARNINGS)
    {
        option_list = Settings::Instance()->warningsOptions();
    }
    else if(m_kw == COMPILE_DEBUG)
    {
        option_list = Settings::Instance()->debugOptions();
    }
    else if(m_kw == COMPILE_OPTI)
    {
        option_list = Settings::Instance()->optimizationOptions();
    }
    else if(m_kw == COMPILE_INSTRU)
    {
        option_list = Settings::Instance()->instrumentationOptions();
    }
    else if(m_kw == COMPILE_PREPROCESSOR)
    {
        option_list = Settings::Instance()->preprocessorOptions();
    }
    else if(m_kw == COMPILE_ASSEMBLER)
    {
        option_list = Settings::Instance()->assemblerOptions();
    }
    else if(m_kw == COMPILE_LINKER)
    {
        option_list = Settings::Instance()->linkerOptions();
    }
    else if(m_kw == COMPILE_DIRS)
    {
        option_list = Settings::Instance()->dirsOptions();
    }
    else if(m_kw == COMPILE_CODE_CONV)
    {
        option_list = Settings::Instance()->codeConvOptions();
    }
    else
    {
        QMessageBox::warning(this,
                             "Mauvais paramètre",
                             "Erreur, impossible de trouver les options pour " + param_type);
    }

    if(option_list)
    {
        QStandardItem* item = nullptr;
        CompilerOption current_option;
        for(int i = 0; i < option_list->length(); i++)
        {
            current_option = option_list->at(i);
            item = new QStandardItem(current_option.option);
            item->setToolTip(HTML_BEGIN + current_option.tooltip + HTML_END);
            model->setItem(i, 0, item);
            item = new QStandardItem(current_option.brief);
            item->setToolTip(HTML_BEGIN + current_option.tooltip + HTML_END);
            model->setItem(i, 1, item);
        }
    }
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->selectRow(0);
}

/**
 * Destructeur de la classe ParamSelectionWindow
 */
ParamSelectionWindow::~ParamSelectionWindow()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
}

/**
 * Ce connecteur est activé par un clic sur le bouton Fermer.@n
 * Ferme la fenêtre.
 */
void ParamSelectionWindow::on_pushButton_close_clicked()
{
    logger(__PRETTY_FUNCTION__);
    this->close();
}

/**
 * Ce connecteur est activé par un clic sur le bouton OK.@n
 * Emet le signal ParamSelectionWindow::selected avec comme paramètre le
 * mot clé ParamSelectionWindow::m_kw et la valeur de la première cellule
 * de la case sélectionnée (l'option).@n
 * Ferme la fenêtre.
 */
void ParamSelectionWindow::on_pushButton_ok_clicked()
{
    logger(__PRETTY_FUNCTION__);
    emit selected(m_kw, ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0).data().toString());
    this->close();
}
