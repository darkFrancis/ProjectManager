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
#include <QFileDialog>
#include <QFileInfo>

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
    ui->textEdit_compilerOption->append(" " + option);
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
 * dans les différents widgets associés afin de pouvoir les éditer ensuite.@n
 * Voir @ref CONTEXT_GET, Ui.
 */
void CompilerParamWindow::init()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();

    // Tab defines
    ui->listWidget_define->clear();
    ui->listWidget_define->addItems(ctx->defines());
    ui->lineEdit_nameDefine->clear();
    ui->lineEdit_valueDefine->clear();

    // Tab IncludePath
    ui->listWidget_includePath->clear();
    ui->listWidget_includePath->addItems(ctx->includePath());
    ui->lineEdit_includePath->clear();

    // Tab lib links
    ui->listWidget_links->clear();
    ui->listWidget_links->addItems(ctx->libs());
    ui->lineEdit_links->clear();

    // Tab Compiler options
    ui->comboBox_compilerOption->addItems(QStringList() << KW_FLAG_OVERALL
                                          << KW_FLAG_LANGUAGE_C
                                          << KW_FLAG_LANGUAGE_CXX
                                          << KW_FLAG_DIAGNOSTIC
                                          << KW_FLAG_WARNINGS
                                          << KW_FLAG_DEBUG
                                          << KW_FLAG_OPTI
                                          << KW_FLAG_INSTRU
                                          << KW_FLAG_PREPROCESSOR
                                          << KW_FLAG_ASSEMBLER
                                          << KW_FLAG_LINKER
                                          << KW_FLAG_DIRS
                                          << KW_FLAG_CODE_CONV
                                          << KW_FLAG_OTHER);
    ui->comboBox_compilerOption->setCurrentIndex(0);
    ui->textEdit_compilerOption->setText(ctx->compilerFlags().join(' '));

    // Tab Extra
    ui->listWidget_preBuild->clear();
    ui->listWidget_preBuild->addItems(ctx->cmdPreBuild());
    ui->listWidget_postBuild->clear();
    ui->listWidget_postBuild->addItems(ctx->cmdPostBuild());
    ui->listWidget_extraClean->clear();
    ui->listWidget_extraClean->addItems(ctx->cmdExtraClean());
    ui->lineEdit_extraCmd->clear();

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

    ctx->setDefines(itemsFromList(ui->listWidget_define));
    ctx->setIncludePath(itemsFromList(ui->listWidget_includePath));
    ctx->setLibs(itemsFromList(ui->listWidget_links));
    ctx->setCompilerFlags(ui->textEdit_compilerOption->toPlainText().split(' '));
    ctx->setCmdPreBuild(itemsFromList(ui->listWidget_preBuild));
    ctx->setCmdPostBuild(itemsFromList(ui->listWidget_postBuild));
    ctx->setCmdExtraClean(itemsFromList(ui->listWidget_extraClean));

    ctx->save();
}

/**
 * Ce connecteur est activé par un clic souris utilisateur sur le bouton Ajouter de
 * l'onglet des define.@n
 * Si le nom du define est bien au format alphanumérique et sans espace, l'ajoute à
 * la liste des defines avec sont éventuelle valeur.
 */
void CompilerParamWindow::on_pushButton_addDefine_clicked()
{
    ui->lineEdit_nameDefine->setText(ui->lineEdit_nameDefine->text().simplified());
    ui->lineEdit_valueDefine->setText(ui->lineEdit_valueDefine->text().trimmed());
    QString item = ui->lineEdit_nameDefine->text();

    // Check
    for(QChar c : item)
    {
        if(!c.isLetterOrNumber())
        {
            QMessageBox::warning(this,
                                 "Attention",
                                 "Seuls les caractères alphanumériques sont autorisés pour"
                                 "nommer un define !");
            return;
        }
    }

    // add value
    if(ui->lineEdit_valueDefine->text() != "")
    {
        item += "=" + ui->lineEdit_valueDefine->text();
    }
    ui->listWidget_define->addItem(item);

    // Clear lines
    ui->lineEdit_nameDefine->clear();
    ui->lineEdit_valueDefine->clear();
}

/**
 * Ce connecteur est activé par un clic souris utilisateur sur le bouton Supprimer de
 * l'onglet des defines.@n
 * Supprime tous les éléments sélectionnés de la liste des defines.
 */
void CompilerParamWindow::on_pushButton_removeDefine_clicked()
{
    for(QListWidgetItem* item : ui->listWidget_define->selectedItems())
    {
        delete item;
    }
}

/**
 * Ce connecteur est activé par un clic souris utilisateur sur le bouton outil de
 * l'onglet des chemins à inclure.@n
 * Ouvre une boîte de dialogue pour rechercher un dossier à inclure. Une fois
 * celui-ci trouvé, inscrit son chemin relatif dans la ligne d'édition de cet
 * onglet.
 */
void CompilerParamWindow::on_toolButton_includePath_clicked()
{
    Context* ctx = Context::Instance();
    QString dir_path = QFileDialog::getExistingDirectory(this,
                                                         "Dossier à inclure",
                                                         ctx->lastSearch());
    dir_path = dir_path.simplified();
    if(dir_path != "")
    {
        QDir dir(dir_path);
        ctx->setLastSearch(dir.absolutePath());
        ui->lineEdit_includePath->setText(relativePath(dir.absolutePath(), QFileInfo(ctx->projectFile()).absolutePath()));
    }
}

/**
 * Ce connecteur est activé par un clic souris utilisateur sur le bouton Ajouter de
 * l'onglet des chemins à inclure.@n
 * Ajoute le texte de la ligne d'édition dans la liste de l'onglet des chemins à
 * inclure puis efface cette ligne.
 */
void CompilerParamWindow::on_pushButton_addIncludePath_clicked()
{
    if(ui->lineEdit_includePath->text().trimmed() != "")
    {
        ui->listWidget_includePath->addItem(ui->lineEdit_includePath->text().trimmed());
        ui->lineEdit_includePath->clear();
    }
}

/**
 * Ce connecteur est activé par un clic souris utilisateur sur le bouton Supprimer de
 * l'onglet des chemins à inclure.@n
 * Supprime tous les éléments sélectionnés de la liste des chemins à inclure.
 */
void CompilerParamWindow::on_pushButton_removeIncludePath_clicked()
{
    for(QListWidgetItem* item : ui->listWidget_includePath->selectedItems())
    {
        delete item;
    }
}

/**
 * Ce connecteur est activé par un clic souris utilisateur sur le bouton outil de
 * l'onglet des liens.@n
 * Ouvre une boîte de dialogue pour rechercher une librairie à lier. Une fois
 * celle-ci trouvée, inscrit son chemin absolu dans la ligne d'édition de cet
 * onglet.
 */
void CompilerParamWindow::on_toolButton_links_clicked()
{
    Context* ctx = Context::Instance();
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     "Librairie",
                                                     ctx->lastSearch(),
                                                     "Librairies (*.a *.so *.a.* *.so.*)");
    file_name = file_name.simplified();
    if(file_name != "")
    {
        QFileInfo info(file_name);
        ctx->setLastSearch(info.absolutePath());
        ui->lineEdit_links->setText(info.absoluteFilePath());
    }
}

/**
 * Ce connecteur est activé par un clic souris utilisateur sur le bouton Ajouter de
 * l'onglet des liens.@n
 * Ajoute le texte de la ligne d'édition dans la liste de l'onglet des liens puis
 * efface cette ligne.
 */
void CompilerParamWindow::on_pushButton_addLinks_clicked()
{
    if(ui->lineEdit_links->text().trimmed() != "")
    {
        ui->listWidget_links->addItem(ui->lineEdit_links->text().trimmed());
        ui->lineEdit_links->clear();
    }
}

/**
 * Ce connecteur est activé par un clic souris utilisateur sur le bouton Supprimer de
 * l'onglet des liens.@n
 * Supprime tous les éléments sélectionnés de la liste des liens.
 */
void CompilerParamWindow::on_pushButton_removeLinks_clicked()
{
    for(QListWidgetItem* item : ui->listWidget_links->selectedItems())
    {
        delete item;
    }
}

/**
 * Ce connecteur est activé par un clic souris utilisateur sur le bouton outil de
 * l'onglet des options de compilation.@n
 * Appelle la fonction CompilerParamWindow::open_param avec comme paramètre le mot
 * clé affiché dans la liste déroulante à gauche du bouton outil.
 */
void CompilerParamWindow::on_toolButton_compilerOption_clicked()
{
    open_param(ui->comboBox_compilerOption->currentText());
}

/**
 * Ce connecteur est activé par un clic souris utilisateur sur le bouton + de
 * l'onglet des commandes spéciales.@n
 * Ajoute le texte de la ligne d'édition dans la liste de l'onglet actif puis
 * efface cette ligne.
 */
void CompilerParamWindow::on_toolButton_addExtraCmd_clicked()
{
    QListWidget* list;
    if(ui->tabWidget_extraCmd->currentIndex() == IDX_TAB_EXTRA_PRE) list = ui->listWidget_preBuild;
    else if(ui->tabWidget_extraCmd->currentIndex() == IDX_TAB_EXTRA_POST) list = ui->listWidget_postBuild;
    else if(ui->tabWidget_extraCmd->currentIndex() == IDX_TAB_EXTRA_CLEAN) list = ui->listWidget_extraClean;
    else
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Onglet courant inconnu !");
        return;
    }

    if(ui->lineEdit_extraCmd->text().trimmed() != "")
    {
        list->addItem(ui->lineEdit_extraCmd->text().trimmed());
        ui->lineEdit_extraCmd->clear();
    }
}

/**
 * Ce connecteur est activé par un clic souris utilisateur sur le bouton Supprimer de
 * l'onglet des commandes spéciales.@n
 * Supprime les commande sélectionnées dans l'onglet actif.
 */
void CompilerParamWindow::on_pushButton_removeExtraCmd_clicked()
{
    QListWidget* list;
    if(ui->tabWidget_extraCmd->currentIndex() == IDX_TAB_EXTRA_PRE) list = ui->listWidget_preBuild;
    else if(ui->tabWidget_extraCmd->currentIndex() == IDX_TAB_EXTRA_POST) list = ui->listWidget_postBuild;
    else if(ui->tabWidget_extraCmd->currentIndex() == IDX_TAB_EXTRA_CLEAN) list = ui->listWidget_extraClean;
    else
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Onglet courant inconnu !");
        return;
    }

    for(QListWidgetItem* item : list->selectedItems())
    {
        delete item;
    }
}

/**
 * @param widget Widget contenant la liste des éléments à retourner
 * @return La liste des éléments de la liste passés en paramètre
 *
 * Cette fonction permet d'obtenir la liste de chaîne de caractères de tous les éléments
 * d'une liste widget de type QListWidget.
 */
QStringList CompilerParamWindow::itemsFromList(QListWidget *widget)
{
    QStringList tmp;
    for(QListWidgetItem* item : widget->findItems("", Qt::MatchContains))
    {
        tmp << item->text();
    }
    return tmp;
}
