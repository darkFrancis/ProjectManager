/**
 * @file tabcompiler.cpp
 */

#include "tabcompiler.hpp"
#include "ui_tabcompiler.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QShortcut>
#include <QDebug>
#include "settings/settings.hpp"
#include "context.hpp"
#include "compiler/sourceswindow.hpp"
#include "compiler/compilerparamwindow.hpp"
#include "settings/logger.hpp"

TabCompiler::TabCompiler(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabCompiler)
{
    /**
     * @brief Constructeur de TabCompiler
     * @param parent Le QWidget parent
     */
    ui->setupUi(this);
    logger(__PRETTY_FUNCTION__);

    initComboType(ui->comboBox_projectType);
    ui->comboBox_projectType->setCurrentIndex(ui->comboBox_projectType->findText(type2label(Context::Instance()->projectType())));

    QShortcut* shortcut_terminate = new QShortcut(QKeySequence("Ctrl+X"), this);
    connect(shortcut_terminate, &QShortcut::activated, this, &TabCompiler::forceEnd);
    QShortcut* shortcut_clear = new QShortcut(QKeySequence("Ctrl+E"), this);
    connect(shortcut_clear, &QShortcut::activated, ui->textEdit_status, &QTextEdit::clear);

    m_process = nullptr;
}
TabCompiler::~TabCompiler()
{
    /**
     * @brief Destructeur de TabCompiler
     */
    logger(__PRETTY_FUNCTION__);
    delete ui;
    delete m_process;
}

void TabCompiler::save()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    QString dir = ui->lineEdit_buildDir->text();
    if(dir.at(dir.length()-1) != QChar('/')) dir.append('/');
    ctx->setBuildDir(dir);
    ctx->setOutput(ui->lineEdit_output->text());
}

void TabCompiler::init()
{
    Context* ctx = Context::Instance();
    ui->comboBox_projectType->setCurrentIndex(ui->comboBox_projectType->findText(ctx->projectType()));
    ui->radioButton_debug->setChecked(true);
    ui->lineEdit_buildDir->setText(ctx->buildDir());
    ui->lineEdit_output->setText(ctx->output());
}

/**
 * @brief Ce SLOT est appelé en cas de clic sur le bouton de recherche de dossier de build
 *
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

void TabCompiler::on_pushButton_sources_clicked()
{
    logger(__PRETTY_FUNCTION__);
    SourcesWindow* w = new SourcesWindow(this);
    connect(this, &TabCompiler::destroyed, w, &SourcesWindow::close);
    w->setAttribute(Qt::WA_QuitOnClose, false);
    w->setWindowModality(Qt::ApplicationModal);
    w->show();
}

void TabCompiler::on_pushButton_param_clicked()
{
    logger(__PRETTY_FUNCTION__);
    CompilerParamWindow* w = new CompilerParamWindow(this);
    connect(this, &TabCompiler::destroyed, w, &SourcesWindow::close);
    w->setAttribute(Qt::WA_QuitOnClose, false);
    w->setWindowModality(Qt::ApplicationModal);
    w->show();
}


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

void TabCompiler::action_build_run()
{
    logger(__PRETTY_FUNCTION__);
    action_build();
    action_run();
}

void TabCompiler::action_build()
{
    logger(__PRETTY_FUNCTION__);
    /**
     * @todo
     */
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

void TabCompiler::action_run()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    QFileInfo info(ctx->buildDir() + ctx->output());
    send_cmd("./" + info.fileName(), QStringList(), info.absoluteDir().absolutePath());
}

void TabCompiler::action_clean()
{
    logger(__PRETTY_FUNCTION__);
    send_cmd("rm", QStringList() << "-rf" << "*.o", Context::Instance()->buildDir());
}

void TabCompiler::action_install()
{
    /**
     * @todo utiliser commande install
     */
    logger(__PRETTY_FUNCTION__);
}

void TabCompiler::action_uninstall()
{
    /**
     * @todo fonction de désinstallation
     */
    logger(__PRETTY_FUNCTION__);
}

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

void TabCompiler::updateStandardOutput()
{
    m_process->setReadChannel(QProcess::StandardOutput);
    readProcess();
}

void TabCompiler::updateStandardError()
{
    m_process->setReadChannel(QProcess::StandardError);
    readProcess();
}

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

void TabCompiler::addCommand(QString cmd, QStringList param, QString dir)
{
    Command command;
    command.programm = cmd;
    command.params = param;
    command.dir = dir;
    m_commands.append(command);
}

void TabCompiler::forceEnd()
{
    logger(__PRETTY_FUNCTION__);
    m_commands.clear();
    m_process->kill();
}

void TabCompiler::on_pushButton_default_clicked()
{
    logger(__PRETTY_FUNCTION__);
    QFileInfo info(Context::Instance()->projectFile());
    QString dir = info.absoluteDir().absolutePath();
    if(dir.at(dir.length()-1) != QChar('/')) dir.append('/');
    ui->lineEdit_buildDir->setText(dir + "build/");
    ui->lineEdit_output->setText("bin/" + Context::Instance()->projectName());
}

void TabCompiler::on_pushButton_apply_clicked()
{
    logger(__PRETTY_FUNCTION__);
    save();
}
