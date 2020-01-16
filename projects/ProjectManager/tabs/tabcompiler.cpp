/**
 * @file tabcompiler.cpp
 */

#include "tabcompiler.hpp"
#include "ui_tabcompiler.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include "settings/settings.hpp"
#include "context.hpp"
#include "compiler/sourceswindow.hpp"

TabCompiler::TabCompiler(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabCompiler)
{
    /**
     * @brief Constructeur de TabCompiler
     * @param parent Le QWidget parent
     */
    ui->setupUi(this);
}
TabCompiler::~TabCompiler()
{

    /**
     * @brief Destructeur de TabCompiler
     */
    delete ui;
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

void TabCompiler::on_toolButton_gestion_clicked()
{
    /**
     * @todo ajout gestion define et linkage
     */
    if(ui->comboBox_gestion->currentText() == TEXT_SOURCES)
    {
        SourcesWindow* w = new SourcesWindow(this);
        w->show();
    }
}

void TabCompiler::on_pushButton_action_clicked()
{
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
    else if(ui->comboBox_action->currentText() == TEXT_MAKEFILE)
    {
        action_makefile();
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
    /**
     * @todo
     */
    send_cmd("ping", QStringList() << "-c 4" << "riot.de");
}

void TabCompiler::action_build()
{
    /**
     * @todo
     */
    send_cmd("ping", QStringList() << "--help");
}

void TabCompiler::action_run()
{
    /**
     * @todo
     */
    send_cmd("doxygen", QStringList() << "-w" << "rtgbd" << "iufjdh");
}

void TabCompiler::action_clean()
{
    /**
     * @todo
     */
    send_cmd("echo", QStringList() << "accents:éàèê");
}

void TabCompiler::action_makefile()
{
    /**
     * @todo
     */
    QFileInfo project_file(Context::Instance()->project());
    QDir project_dir(project_file.absoluteDir());

}

void TabCompiler::action_install()
{
    /**
     * @todo
     */
}

void TabCompiler::action_uninstall()
{
    /**
     * @todo
     */
}

void TabCompiler::send_cmd(QString cmd, QStringList param /*= QStringList()*/, QString dir /*= "."*/)
{
    m_process = new QProcess(this);
    ui->textEdit_status->append("> " + cmd + " " + param.join(' '));
    m_process->setWorkingDirectory(dir);
    m_process->start(cmd, param);
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(updateStandardOutput()));
    connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(updateStandardError()));
    connect(m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(endCmd(int,QProcess::ExitStatus)));
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
    Settings* setting = Settings::Instance();
    bool ok = exitStatus == QProcess::NormalExit;
    QString result = "<p style=\"color:";
    result += (ok ? setting->colorSuccess() : setting->colorError());
    result += "\">";
    result += (ok ? "OK" : "Crash");
    result += " (exit_code=" + QString::number(exitCode) + ")";
    result += "</p><br/><br/>";
    ui->textEdit_status->append(result);
    m_process->deleteLater();
}
