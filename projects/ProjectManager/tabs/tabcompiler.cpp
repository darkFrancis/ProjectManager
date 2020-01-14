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
    if(ui->comboBox_action->currentText() == TEXT_BUILDRUN)
    {
        action_build();
        action_run();
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

void TabCompiler::action_build()
{
    /**
     * @todo
     */
    send_cmd("tree");
}

void TabCompiler::action_run()
{
    /**
     * @todo
     */
    send_cmd("ping 192.168.1.254");
}

void TabCompiler::action_clean()
{
    /**
     * @todo
     */
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
    if(Settings::Instance()->clearScreen())
    {
        ui->textEdit_status->clear();
    }
    QProcess* p = new QProcess(this);
    p->setWorkingDirectory(dir);
    p->start(cmd, param);
    connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(updateStandardOutput()));
    connect(p, SIGNAL(readyReadStandardError()), this, SLOT(updateStandardError()));
    p->waitForFinished(-1);
}

void TabCompiler::updateStandardOutput()
{
    QProcess* process = qobject_cast<QProcess*>(sender());
    process->setReadChannel(QProcess::StandardOutput);
    //ui->textEdit_status->append("<div style=\"color:white\">");
    while(process->canReadLine())
    {
        ui->textEdit_status->append(process->readLine());
    }
    //ui->textEdit_status->append("</div>");
}

void TabCompiler::updateStandardError()
{
    QProcess* process = qobject_cast<QProcess*>(sender());
    process->setReadChannel(QProcess::StandardError);
    //ui->textEdit_status->append("<div style=\"color:red\">");
    while(process->canReadLine())
    {
        ui->textEdit_status->append(process->readLine());
    }
    //ui->textEdit_status->append("</div>");
}
