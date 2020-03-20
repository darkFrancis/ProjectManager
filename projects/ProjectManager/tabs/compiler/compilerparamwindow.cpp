/**
 * @file compilerparamwindow.cpp
 * @brief Définition de la classe CompilerParamWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "compilerparamwindow.hpp"
#include "ui_compilerparamwindow.h"
#include "paramselectionwindow.hpp"
#include "settings.hpp"
#include "context.hpp"
#include "logger.hpp"
#include <QMessageBox>

/**
 * @param parent Le QWidget parent de cette fenêtre
 *
 * Contructeur de la classe CompilerParamWindow.@n
 * Ce constructeur hérite de celui de QMainWindow et utilise le système des fichiers d'interface utilisateur.@n
 * Les listes de paramètres sont remplies en fonction des mot clé avec la fonction CompilerParamWindow::init.@n
 * Voir @ref KW_COMPILE, Ui.
 */
CompilerParamWindow::CompilerParamWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompilerParamWindow)
{
    ui->setupUi(this);
    logger(__PRETTY_FUNCTION__);
    init();
}

/**
 * Destructeur de la classe CompilerParamWindow.
 */
CompilerParamWindow::~CompilerParamWindow()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton Appliquer.@n
 * Il applique les modification apportées par l'utilisateur par l'appel
 * à la fonction CompilerParamWindow::apply.
 */
void CompilerParamWindow::on_pushButton_apply_clicked()
{
    logger(__PRETTY_FUNCTION__);
    apply();
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton OK.@n
 * Il applique les modification apportées par l'utilisateur par l'appel
 * à la fonction CompilerParamWindow::apply puis ferme la fenêtre.
 */
void CompilerParamWindow::on_pushButton_ok_clicked()
{
    logger(__PRETTY_FUNCTION__);
    apply();
    this->close();
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton Fermer.@n
 * Ferme la fenêtre.
 */
void CompilerParamWindow::on_pushButton_close_clicked()
{
    logger(__PRETTY_FUNCTION__);
    this->close();
}

/**
 * @param kw Mot clé des options de compilation
 * @param option Option sélectionnée
 *
 * Ce connecteur est activé par le signal ParamSelectionWindow::selected.@n
 * Il demande l'ajout d'une option dans le champs correspondant avec la
 * fonction CompilerParamWindow::add_option.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::selected(QString kw, QString option)
{
    logger("    selected " + kw + " | " + option);
}

/**
 * @param kw Mot clé des options de compilateur
 *
 * Ouvre une fenêtre ParamSelectionWindow pour sélectionner une option de
 * compilation avec pour paramètre le mot clé @c kw. Cette fenêtre bloque
 * les autres fenêtres de l'application tant qu'elle est présente pour forcer
 * l'utilisateur à finir la sélection (ou fermer cette même fenêtre).@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::open_param(QString kw)
{
    logger("    open_param " + kw);
    ParamSelectionWindow* w = new ParamSelectionWindow(this, kw);
    connect(w, &ParamSelectionWindow::selected, this, &CompilerParamWindow::selected);
    w->show();
}

/**
 * Initialise la fenêtre.@n Récupère les différentes listes d'options grâce
 * aux méthodes GET de l'instance Context. Ces listes sont ensuite écrites
 * dans les différents champs de saisie de la fenêtre, chaque éléments étant
 * séparé des autres par un espace.@n
 * Voir @ref CONTEXT_GET, Ui.
 */
void CompilerParamWindow::init()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();

    this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_QuitOnClose, false);
}

/**
 * Enregistre les différentes modifications appliquées par l'utilisateur.@n
 * Chaque ligne d'édition forme une liste d'éléments séparés par des espaces.
 * Ceux si sont ensuite envoyés à la classe Context par l'intermédiaire des
 * méthodes SET. Puis le Context est enregistré avec la méthode Context::save.
 * Voir @ref CONTEXT_SET, Ui.
 */
void CompilerParamWindow::apply()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();

    ctx->save();
}
