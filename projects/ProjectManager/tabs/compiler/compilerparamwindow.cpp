/**
 * @file compilerparamwindow.cpp
 * @brief Définition de la classe CompilerParamWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "compilerparamwindow.hpp"
#include "ui_compilerparamwindow.h"
#include "paramselectionwindow.hpp"
#include "settings/settings.hpp"
#include "context.hpp"
#include "settings/logger.hpp"
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
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options générales.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_OVERALL.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_overall_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_OVERALL);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options de langage C.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_LANGUAGE_C.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_languageC_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_LANGUAGE_C);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options de langage C++.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_LANGUAGE_CXX.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_languageCxx_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_LANGUAGE_CXX);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options de diagnostique.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_DIAGNOSTIC.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_diagnostic_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_DIAGNOSTIC);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options des warnings.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_WARNINGS.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_warnings_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_WARNINGS);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options de debug.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_DEBUG.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_debug_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_DEBUG);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options d'optimisation.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_OPTI.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_optimization_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_OPTI);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options d'instrumentation.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_INSTRU.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_instrumentation_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_INSTRU);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options du préprocesseur.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_PREPROCESSOR.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_preprocessor_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_PREPROCESSOR);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options de l'assembleur.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_ASSEMBLER.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_assembler_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_ASSEMBLER);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options du linker.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_LINKER.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_linker_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_LINKER);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options des dossiers.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_DIRS.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_dirs_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_DIRS);
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton outil des options de convention de code.@n
 * Il appel la fonction CompilerParamWindow::open_param avec le mot clé #COMPILE_CODE_CONV.@n
 * Voir @ref KW_COMPILE.
 */
void CompilerParamWindow::on_toolButton_codeConvention_clicked()
{
    logger(__PRETTY_FUNCTION__);
    open_param(COMPILE_CODE_CONV);
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
    if(kw == COMPILE_OVERALL)
    {
        add_option(ui->lineEdit_overall, option);
    }
    else if(kw == COMPILE_LANGUAGE_C)
    {
        add_option(ui->lineEdit_languageC, option);
    }
    else if(kw == COMPILE_LANGUAGE_CXX)
    {
        add_option(ui->lineEdit_languageCxx, option);
    }
    else if(kw == COMPILE_DIAGNOSTIC)
    {
        add_option(ui->lineEdit_diagnostic, option);
    }
    else if(kw == COMPILE_WARNINGS)
    {
        add_option(ui->lineEdit_warnings, option);
    }
    else if(kw == COMPILE_DEBUG)
    {
        add_option(ui->lineEdit_debug, option);
    }
    else if(kw == COMPILE_OPTI)
    {
        add_option(ui->lineEdit_optimization, option);
    }
    else if(kw == COMPILE_INSTRU)
    {
        add_option(ui->lineEdit_instrumentation, option);
    }
    else if(kw == COMPILE_PREPROCESSOR)
    {
        add_option(ui->lineEdit_preprocessor, option);
    }
    else if(kw == COMPILE_ASSEMBLER)
    {
        add_option(ui->lineEdit_assembler, option);
    }
    else if(kw == COMPILE_LINKER)
    {
        add_option(ui->lineEdit_linker, option);
    }
    else if(kw == COMPILE_DIRS)
    {
        add_option(ui->lineEdit_dirs, option);
    }
    else if(kw == COMPILE_CODE_CONV)
    {
        add_option(ui->lineEdit_codeConvention, option);
    }
    else
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Mot clé non reconnu !");
    }
}

/**
 * @param line_edit Ligne d'édition dans laquelle ajouter l'option
 * @param option Option à ajouter
 *
 * Ajoute l'option au texte de la ligne d'édition @c line_edit.@n
 * Si @c option est déjà présente sur la ligne d'édition, un message d'avertissement
 * est affiché à l'utilisateur.
 */
void CompilerParamWindow::add_option(QLineEdit *line_edit, QString option)
{
    logger("    add_option " + option);
    QStringList options = line_edit->text().split(QChar(' '));
    if(options.contains(option))
    {
        QMessageBox::warning(this,
                             "Attention",
                             "Attention, cette option est présente en plusieurs exemplaires.");
    }
    line_edit->setText(line_edit->text() + " " + option);
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
    w->setAttribute(Qt::WA_QuitOnClose, false);
    w->setWindowModality(Qt::ApplicationModal);
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
    ui->lineEdit_overall->setText(ctx->flagOverall().join(' '));
    ui->lineEdit_languageC->setText(ctx->flagC().join(' '));
    ui->lineEdit_languageCxx->setText(ctx->flagCxx().join(' '));
    ui->lineEdit_diagnostic->setText(ctx->flagDiag().join(' '));
    ui->lineEdit_warnings->setText(ctx->flagWarn().join(' '));
    ui->lineEdit_debug->setText(ctx->flagDebug().join(' '));
    ui->lineEdit_optimization->setText(ctx->flagOpt().join(' '));
    ui->lineEdit_instrumentation->setText(ctx->flagInst().join(' '));
    ui->lineEdit_preprocessor->setText(ctx->flagPreprocess().join(' '));
    ui->lineEdit_assembler->setText(ctx->flagAssembler().join(' '));
    ui->lineEdit_linker->setText(ctx->flagLinker().join(' '));
    ui->lineEdit_dirs->setText(ctx->flagDirs().join(' '));
    ui->lineEdit_codeConvention->setText(ctx->flagConvention().join(' '));
    ui->lineEdit_other->setText(ctx->flagOther().join(' '));
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
    ctx->setFlagOverall(ui->lineEdit_overall->text().split(' '));
    ctx->setFlagC(ui->lineEdit_languageC->text().split(' '));
    ctx->setFlagCxx(ui->lineEdit_languageCxx->text().split(' '));
    ctx->setFlagDiag(ui->lineEdit_diagnostic->text().split(' '));
    ctx->setFlagWarn(ui->lineEdit_warnings->text().split(' '));
    ctx->setFlagDebug(ui->lineEdit_debug->text().split(' '));
    ctx->setFlagOpt(ui->lineEdit_optimization->text().split(' '));
    ctx->setFlagInst(ui->lineEdit_instrumentation->text().split(' '));
    ctx->setFlagPreprocess(ui->lineEdit_preprocessor->text().split(' '));
    ctx->setFlagAssembler(ui->lineEdit_assembler->text().split(' '));
    ctx->setFlagLinker(ui->lineEdit_linker->text().split(' '));
    ctx->setFlagDirs(ui->lineEdit_dirs->text().split(' '));
    ctx->setFlagConvention(ui->lineEdit_codeConvention->text().split(' '));
    ctx->setFlagOther(ui->lineEdit_other->text().split(' '));
    ctx->save();
}
