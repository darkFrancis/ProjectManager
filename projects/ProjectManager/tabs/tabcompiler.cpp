/**
 * @file tabcompiler.cpp
 */

#include "tabcompiler.hpp"
#include "ui_tabcompiler.h"
#include <QFileDialog>
#include <QMessageBox>
#include "context.hpp"

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
     * @todo
     */
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
}

void TabCompiler::action_run()
{
    /**
     * @todo
     */
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
