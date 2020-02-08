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
 * Ce constructeur ajoute les raccourcis clavier suivant :
 * @li &lt;Ctrl+X> pour faire appel à la fonction TabCompiler::forceEnd
 * @li &lt;Ctrl+E> pour effacer l'affichage de l'onglet
 *
 * Voir Ui.
 */
TabCompiler::TabCompiler(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabCompiler)
{
    ui->setupUi(this);
    logger(__PRETTY_FUNCTION__);

    QShortcut* shortcut_terminate = new QShortcut(QKeySequence("Ctrl+X"), this);
    connect(shortcut_terminate, &QShortcut::activated, this, &TabCompiler::forceEnd);
    QShortcut* shortcut_clear = new QShortcut(QKeySequence("Ctrl+E"), this);
    connect(shortcut_clear, &QShortcut::activated, ui->textEdit_status, &QTextEdit::clear);
}

/**
 * Destructeur de la classe TabCompiler
 */
TabCompiler::~TabCompiler()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
    delete m_process;
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
    if(dir.at(dir.length()-1) != QChar('/')) dir.append('/');
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

    m_process = nullptr;
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
    w->setAttribute(Qt::WA_QuitOnClose, false);
    w->setWindowModality(Qt::ApplicationModal);
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
    w->setAttribute(Qt::WA_QuitOnClose, false);
    w->setWindowModality(Qt::ApplicationModal);
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
    if(Settings::Instance()->clearScreen())
    {
        ui->textEdit_status->clear();
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
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION.
 */
void TabCompiler::action_build()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    QString compiler = (ctx->projectType()[ctx->projectType().length()-1] == QChar('x') ? "g++" : "gcc");
    // Preprocess + Assembleur
    for(int i = 0; i < ctx->sources().length(); i++)
    {
        QStringList param;
        param << "-c";
    }
    // Linkage
}

/**
 * Fonction correspondant à l'action #TEXT_RUN.@n
 * Exécute le programme se trouvant dans le dossier de build et portant
 * le nom de la sortie.@n
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION.
 */
void TabCompiler::action_run()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    QFileInfo info(ctx->buildDir() + ctx->output());
    send_cmd("./" + info.fileName(), QStringList(), info.absoluteDir().absolutePath());
}

/**
 * Fonction correspondant à l'action #TEXT_CLEAN.@n
 * Nettoie le dossieer de build en supprimant tous les fichier d'extension
 * .o générés lors d'une précédante compilation.@n
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION.
 */
void TabCompiler::action_clean()
{
    logger(__PRETTY_FUNCTION__);
    send_cmd("rm", QStringList() << "-rf" << "*.o", Context::Instance()->buildDir());
}

/**
 * Fonction correspondant à l'action #TEXT_INSTALL.@n
 * @todo Ecrire cette fonction (commande install) + la tester
 *
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION.
 */
void TabCompiler::action_install()
{
    logger(__PRETTY_FUNCTION__);
}

/**
 * Fonction correspondant à l'action #TEXT_UNINSTALL.@n
 * @todo Ecrire cette fonction (commande rm?) + la tester
 *
 * Voir @ref COMPILE_ACTION, @ref TABCOMPILER_ACTION.
 */
void TabCompiler::action_uninstall()
{
    logger(__PRETTY_FUNCTION__);
}

/**
 * @param cmd Commande à exécuter
 * @param param Arguments à passer à la commande
 * @param dir Répertoire dans lequel exécuter la commande
 *
 * Si un processus est déjà en cours, ajoute la commande à exécuter dans la
 * file d'attente via la fonction TabCompiler::addCommand. Sinon, prépare le
 * processus et demande son exécution en le connectant comme suit :
 * @li Sortie standard -> TabCompiler::updateStandardOutput
 * @li Erreur standard -> TabCompiler::updateStandardError
 * @li Fin d'exécution -> TabCompiler::endCmd
 *
 * Cette fonction désactive le bouton d'exécution de commandes.@n
 * Voir TabCompiler::m_process.
 */
void TabCompiler::send_cmd(QString cmd, QStringList param /*= QStringList()*/, QString dir /*= "."*/)
{
    logger("    cmd: " + cmd + " " + param.join(' '));
    ui->pushButton_action->setEnabled(false);
    if(m_process == nullptr)
    {
        m_process = new QProcess(this);
        ui->textEdit_status->append("> " + cmd + " " + param.join(' '));
        m_process->setWorkingDirectory(dir);
        m_process->start(cmd, param);
        connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(updateStandardOutput()));
        connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(updateStandardError()));
        connect(m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(endCmd(int,QProcess::ExitStatus)));
    }
    else
    {
        addCommand(cmd, param, dir);
    }
}

/**
 * Ce connecteur est activé lorsqu'il est possible de lire la sortie standard
 * du processus en cours. La lecture de sortie de processus est cablée sur la
 * sortie standard et la fonction TabCompiler::readProcess est appelée.@n
 * Voir TabCompiler::m_process.
 */
void TabCompiler::updateStandardOutput()
{
    m_process->setReadChannel(QProcess::StandardOutput);
    readProcess();
}

/**
 * Ce connecteur est activé lorsqu'il est possible de lire l'erreur standard
 * du processus en cours. La lecture de sortie de processus est cablée sur
 * l'erreur standard et la fonction TabCompiler::readProcess est appelée.@n
 * Voir TabCompiler::m_process.
 */
void TabCompiler::updateStandardError()
{
    m_process->setReadChannel(QProcess::StandardError);
    readProcess();
}

/**
 * Lecture de la sortie du processus en cours.@n
 * Utilise un format HTML pour afficher la sortie/erreur du processus en cours
 * avec un texte coloré selon le cas (voir Settings::m_color_normal et
 * Settings::m_color_error).@n
 * Voir TabCompiler::m_process.
 */
void TabCompiler::readProcess()
{
    QString to_write = "";
    to_write += "<p style=\"color:";
    to_write += (m_process->readChannel() == QProcess::StandardOutput ? Settings::Instance()->colorNormal() : Settings::Instance()->colorError());
    to_write += "\">";

    QString line = "";
    bool first = true;
    while(m_process->canReadLine())
    {
        if(first)
            first = false;
        else
            to_write += "<br/>";
        line = m_process->readLine();
        // Format
        line = line.left(line.length()-1);
        line = line.replace('<', "&lt;").replace('>', "&gt;").replace(' ', "&nbsp;");
        to_write.append(line);
    }
    to_write += "</p>";
    ui->textEdit_status->append(to_write);
}

/**
 * @param exitCode Code retour de l'exécution du processus
 * @param exitStatus Status final du processus
 *
 * Ce connecteur est activé lorsque le processus en cours se termine.@n
 * Utilise un format HTML pour afficher le résultat du processus en cours
 * avec un texte coloré selon le cas (voir Settings::m_color_success et
 * Settings::m_color_error). Si il reste des commandes à exécuter dans
 * la fie d'attente, exécute la suivante à l'aide de la fonction
 * TabCompiler::send_cmd. Sinon, réactive le bouton d'exécution des
 * commandes.@n
 * Voir TabCompiler::m_process, Command.
 */
void TabCompiler::endCmd(int exitCode, QProcess::ExitStatus exitStatus)
{
    logger("    end_cmd: " + QString::number(exitCode));
    Settings* setting = Settings::Instance();
    bool ok = exitStatus == QProcess::NormalExit;
    QString result = "<p style=\"color:";
    result += (ok ? setting->colorSuccess() : setting->colorError());
    result += "\">";
    result += (ok ? "OK" : "Crash");
    result += " (exit_code=" + QString::number(exitCode) + ")";
    result += "<br/></p>";
    ui->textEdit_status->append(result);
    delete m_process;
    m_process = nullptr;

    // Next command
    if(m_commands.length() > 0)
    {
        Command cmd = m_commands.takeFirst();
        send_cmd(cmd.programm, cmd.params, cmd.dir);
    }
    else
    {
        ui->pushButton_action->setEnabled(true);
    }
}

/**
 * @param cmd Nom de la commande
 * @param param Arguments de la commande
 * @param dir Répertoire dans lequel exécuter la commande
 *
 * Ajoute une commande dans la file d'attente des commandes, TabCompiler::m_commands.@n
 * Un objet Command est créé avec les arguments de cette fonction avant d'être
 * ajouté à cette liste. Cette commande sera exécutée pluus tard par la fonction
 * TabCompiler::send_cmd.@n
 * Voir TabCompiler::endCmd.
 */
void TabCompiler::addCommand(QString cmd, QStringList param, QString dir)
{
    Command command;
    command.programm = cmd;
    command.params = param;
    command.dir = dir;
    m_commands.append(command);
}

/**
 * Tue le processus en cours.@n
 * Ceci entraine un crash du processus si celui-ci n'était pas terminé.
 * Le connecteur TabCompiler::endCmd est donc appelé.@n
 * Voir TabCompiler::m_process.
 */
void TabCompiler::forceEnd()
{
    logger(__PRETTY_FUNCTION__);
    m_commands.clear();
    m_process->kill();
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
