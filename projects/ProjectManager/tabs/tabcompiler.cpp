/**
 * @file tabcompiler.cpp
 * @brief Définition de la classe TabCompiler
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "tabcompiler.hpp"
#include "ui_tabcompiler.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QShortcut>
#include <QGridLayout>
#include "settings.hpp"
#include "context.hpp"
#include "sourceswindow.hpp"
#include "compilerparamwindow.hpp"
#include "logger.hpp"

/**
 * @param parent Le QWidget parent de cet onglet
 *
 * Contructeur de la classe TabCompiler. Il hérite de celui de Tab et utilise
 * le système des fichiers d'interface utilisateur.@n
 * Ajoute et initialise l'élément TabCompiler::m_displayer.@n
 * Voir Ui, ProcessDisplayer.
 */
TabCompiler::TabCompiler(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabCompiler)
{
    ui->setupUi(this);
    logger(__PRETTY_FUNCTION__);

    // Ajout de l'écran de display des commandes
    QGridLayout* layout = new QGridLayout();
    layout->setContentsMargins(0,0,0,0);
    m_displayer = new ProcessDisplayer(this);
    layout->addWidget(m_displayer);
    ui->groupBox_status->setLayout(layout);
    connect(m_displayer, SIGNAL(end()), this, SLOT(activate_action()));
}

/**
 * Destructeur de la classe TabCompiler
 */
TabCompiler::~TabCompiler()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
}

/**
 * Enregistre les modifications apportées par l'utilisateur.@n
 * Cette fonction utilise les méthodes SET de l'instance Context pour enregistrer
 * les éléments présents dans cet onglet (type de projet et chemins). Puis elle appelle
 * la fonction Context::save pour enregistrer les modification apportées dans le
 * fichier de projet.
 * Voir @ref CONTEXT_SET, @ref FILE, Ui.
 */
void TabCompiler::save()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    QString dir = ui->lineEdit_buildDir->text();
    if(dir.length() > 0 && dir.at(dir.length()-1) != QChar('/')) dir.append('/');
    ctx->setBuildDir(dir);
    ctx->setOutput(ui->lineEdit_output->text());
    ctx->setProjectType(label2type(ui->comboBox_projectType->currentText()));
    ctx->save();
}

/**
 * Cette fonction initialise l'onglet TabCompiler.@n
 * Elle initialise les liste déroulante à l'aide de la fonction initComboType,
 * pour ce qui est de la sélection du type de projet, et avec les labels
 * @ref COMPILE_ACTION, pour ce qui est des action de compilation à effectuer.
 * Les lignes d'édition sont remplies grâce aux méthodes GET de l'instance
 * Context.@n
 * Voir @ref CONTEXT_GET, Ui.
 */
void TabCompiler::init()
{
    // Init comboBox
    initComboType(ui->comboBox_projectType);
    ui->comboBox_action->addItems(QStringList() << TEXT_BUILDRUN
                                                << TEXT_BUILD
                                                << TEXT_RUN
                                                << TEXT_CLEAN
                                                << TEXT_INSTALL
                                                << TEXT_UNINSTALL);

    // Set default
    Context* ctx = Context::Instance();
    ui->comboBox_projectType->setCurrentIndex(ui->comboBox_projectType->findText(type2label(ctx->projectType())));
    ui->radioButton_debug->setChecked(true);
    ui->lineEdit_buildDir->setText(ctx->buildDir());
    ui->lineEdit_output->setText(ctx->output());
}

/**
 * Ce connecteur est activé par le signal ProcessDisplayer::end.@n
 * Rend accessible au clic le bouton d'exécution d'action.
 */
void TabCompiler::activate_action()
{
    ui->pushButton_action->setEnabled(true);
}

/**
 * Ce connecteur est activé en cas de clic sur le bouton outil de recherche de dossier de build.@n
 * Suite à une recherche de dossier (fenêtre de dialogue) :
 * @li Si le dossier retourné est vide, ne fait rien.
 * @li Sinon, mais à jour le context et écrit le chemin absolu dans la ligne de texte.
 */
void TabCompiler::on_toolButton_buildDir_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QString dir_path = QFileDialog::getExistingDirectory(this,
                                                         "Dossier de build",
                                                         Context::Instance()->lastSearch());
    if(!dir_path.isEmpty())
    {
        QDir dir(dir_path);
        Context::Instance()->setLastSearch(dir.absolutePath());
        ui->lineEdit_buildDir->setText(dir.absolutePath());
    }
}

/**
 * Ce connecteur est activé par un clic souris sur le bouton Sources par
 * l'utilisateur.@n
 * Ouvre une fenêtre SourcesWindow pour sélectionner/supprimer des fichiers
 * de sources, des headers ou des fichiers de ressources. Cette fenêtre bloque
 * les autre fenêtre de l'application tant qu'elle est présente pour forcer
 * l'utilisateur à finir la sélection (ou fermer cette même fenêtre).
 */
void TabCompiler::on_pushButton_sources_clicked()
{
    logger(__PRETTY_FUNCTION__);
    SourcesWindow* w = new SourcesWindow(this);
    connect(this, &TabCompiler::destroyed, w, &SourcesWindow::close);
    w->show();
}

/**
 * Ce connecteur est activé par un clic souris sur le bouton Paramètres par
 * l'utilisateur.@n
 * Ouvre une fenêtre CompilerParamWindow pour gérer les différentes options
 * de compilation. Cette fenêtre bloque les autre fenêtre de l'application
 * tant qu'elle est présente pour forcer l'utilisateur à finir la sélection
 * (ou fermer cette même fenêtre).
 */
void TabCompiler::on_pushButton_param_clicked()
{
    logger(__PRETTY_FUNCTION__);
    CompilerParamWindow* w = new CompilerParamWindow(this);
    connect(this, &TabCompiler::destroyed, w, &SourcesWindow::close);
    w->show();
}

/**
 * Ce connecteur s'active par un clic souris sur le bouton Exécuter par
 * l'utilisateur.@n
 * Il effectue une action en fonction de l'action de compilation sélectionnée
 * dans la liste déroulante.@n
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION.
 */
void TabCompiler::on_pushButton_action_clicked()
{
    logger(__PRETTY_FUNCTION__);
    ui->pushButton_action->setEnabled(false);
    if(Settings::Instance()->clearScreen())
    {
        m_displayer->clear();
    }
    if(ui->comboBox_action->currentText() == TEXT_BUILDRUN)
    {
        action_build_run();
    }
    else if(ui->comboBox_action->currentText() == TEXT_BUILD)
    {
        action_build();
    }
    else if(ui->comboBox_action->currentText() == TEXT_RUN)
    {
        action_run();
    }
    else if(ui->comboBox_action->currentText() == TEXT_CLEAN)
    {
        action_clean();
    }
    else if(ui->comboBox_action->currentText() == TEXT_INSTALL)
    {
        action_install();
    }
    else if(ui->comboBox_action->currentText() == TEXT_UNINSTALL)
    {
        action_uninstall();
    }
    else
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Action non reconnue !");
    }
}

/**
 * Fonction correspondant à l'action #TEXT_BUILDRUN.@n
 * Exécute les fonctions TabCompiler::action_build et
 * TabCompiler::action_run.@n
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION.
 */
void TabCompiler::action_build_run()
{
    logger(__PRETTY_FUNCTION__);
    action_build();
    action_run();
}

/**
 * Fonction correspondant à l'action #TEXT_BUILD.@n
 * @todo Ecrire cette fonction + la tester
 *
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION, ProcessDisplayer.
 */
void TabCompiler::action_build()
{
    logger(__PRETTY_FUNCTION__);

    /*Context* ctx = Context::Instance();
    QString compiler = (ctx->projectType() == TYPE_CXX ? "g++" : "gcc");
    QStringList obj_list;

    // Preprocess + Assembleur
    QString obj_tmp;
    QStringList param_list;
    param_list << "-c"
               << ctx->flagOverall()
               << (ctx->projectType() == TYPE_CXX ? ctx->flagCxx() : ctx->flagC())
               << ctx->flagDiag()
               << ctx->flagWarn()
               << ctx->flagDebug()
               << ctx->flagOpt()
               << ctx->flagInst()
               << ctx->flagDirs()
               << ctx->flagConvention()
               << ctx->flagOther()
               << ctx->flagPreprocess()
               << ctx->flagAssembler();
    for(QString source : ctx->sources())
    {
        QStringList param_tmp = param_list;
        int idx_last = source.lastIndexOf('.');
        int idx_first = source.lastIndexOf('/')+1;
        obj_tmp = source.mid(idx_first, idx_last-idx_first) + ".o";
        param_tmp << "-o" << obj_tmp << relativePath(source, ctx->buildDir());
        obj_list << obj_tmp;
        m_displayer->send_cmd(compiler, param_tmp, ctx->buildDir());
    }

    // Linkage
    param_list.clear();
    param_list << ctx->flagOverall()
               << (ctx->projectType() == TYPE_CXX ? ctx->flagCxx() : ctx->flagC())
               << ctx->flagDiag()
               << ctx->flagWarn()
               << ctx->flagDebug()
               << ctx->flagOpt()
               << ctx->flagInst()
               << ctx->flagDirs()
               << ctx->flagConvention()
               << ctx->flagOther();
    param_list << "-o"
               << ctx->projectName();
    for(QString obj : obj_list)
    {
        param_list << obj;
    }
    param_list << ctx->flagLinker();
    m_displayer->send_cmd(compiler, param_list, ctx->buildDir());*/
}

/**
 * Fonction correspondant à l'action #TEXT_RUN.@n
 * Exécute le programme se trouvant dans le dossier de build et portant
 * le nom de la sortie.@n
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION, ProcessDisplayer.
 */
void TabCompiler::action_run()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    QFileInfo info(ctx->buildDir() + ctx->output());
    m_displayer->send_cmd("./" + info.fileName(), QStringList(), info.absoluteDir().absolutePath());
}

/**
 * Fonction correspondant à l'action #TEXT_CLEAN.@n
 * Nettoie le dossieer de build en supprimant tous les fichier d'extension
 * .o générés lors d'une précédante compilation.@n
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION, ProcessDisplayer.
 */
void TabCompiler::action_clean()
{
    logger(__PRETTY_FUNCTION__);
    m_displayer->send_cmd("rm", QStringList() << "-rf" << "*.o", Context::Instance()->buildDir());
}

/**
 * Fonction correspondant à l'action #TEXT_INSTALL.@n
 * @todo Ecrire cette fonction (commande install) + la tester
 *
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION, ProcessDisplayer.
 */
void TabCompiler::action_install()
{
    logger(__PRETTY_FUNCTION__);
    QMessageBox::information(this,
                             "Information",
                             "Cette fonctionnalité est encore en cours de développement."
                             "Revenez plus tard.");
    ui->pushButton_action->setEnabled(true);
}

/**
 * Fonction correspondant à l'action #TEXT_UNINSTALL.@n
 * @todo Ecrire cette fonction (commande rm?) + la tester
 *
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION, ProcessDisplayer.
 */
void TabCompiler::action_uninstall()
{
    logger(__PRETTY_FUNCTION__);
    QMessageBox::information(this,
                             "Information",
                             "Cette fonctionnalité est encore en cours de développement."
                             "Revenez plus tard.");
    ui->pushButton_action->setEnabled(true);
}

/**
 * Ce connecteur est activé par un clic souris sur le bouton Défaut par l'utilisateur.@n
 * Il remet à zéro les informations de l'onglet TabCompiler:
 * @li Dossier de build : "ProjectDir"/build/
 * @li Sortie : bin/"ProjectName"
 */
void TabCompiler::on_pushButton_default_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QFileInfo info(Context::Instance()->projectFile());
    QString dir = info.absoluteDir().absolutePath();
    if(dir.at(dir.length()-1) != QChar('/')) dir.append('/');
    ui->lineEdit_buildDir->setText(dir + "build/");
    ui->lineEdit_output->setText("bin/" + Context::Instance()->projectName());
}

/**
 * Ce connecteur est activé par un clic souris sur le bouton Appliquer par l'utilisateur.@n
 * Il appelle enregistre les modifications apportées par l'utilisateur avec la fonction
 * TabCompiler::save.
 */
void TabCompiler::on_pushButton_apply_clicked()
{
    logger(__PRETTY_FUNCTION__);
    save();
}
