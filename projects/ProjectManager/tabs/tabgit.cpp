/**
 * @file tabgit.cpp
 * @brief Définition de la classe TabGit
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "tabgit.hpp"
#include "ui_tabgit.h"

#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include "context.hpp"
#include "logger.hpp"
#include "context.hpp"

/**
 * @param parent Le QWidget parent de cet onglet
 *
 * Contructeur de la classe TabDoxygen. Il hérite de celui de Tab et utilise
 * le système des fichiers d'interface utilisateur.@n
 * Initialise son attribut TabGit::m_process.@n
 * Voir Ui.
 */
TabGit::TabGit(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabGit)
{
    ui->setupUi(this);
    logger(__PRETTY_FUNCTION__);

    m_process = new QProcess();
}

/**
 * Destructeur de la classe TabGit.
 */
TabGit::~TabGit()
{
    logger(__PRETTY_FUNCTION__);
    clear();
    delete ui;
}

void TabGit::init()
{
    Context* ctx = Context::Instance();
    QFileInfo info(ctx->projectFile());
    m_process->setWorkingDirectory(info.absolutePath());
}

void TabGit::clear()
{
    ui->listWidget_staged->clear();
    ui->listWidget_unstaged->clear();
    ui->checkBox_amend->setChecked(false);
    ui->lineEdit_commit->clear();
    ui->comboBox_branch->clear();
    m_process->kill();
    delete m_process;
}

void TabGit::on_pushButton_commit_clicked()
{
    QStringList args;
    args << "commit";
    if(ui->checkBox_amend->isChecked()) args << "--amend";
    args << "-m";
    QString msg = ui->lineEdit_commit->text().simplified();
    if(msg == QString("")) args << GIT_COMMIT_DEFAULT_MSG;
    else args << msg;
    action(args);
}

void TabGit::on_checkBox_amend_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        /**
          * @todo Récupérer dernier commit pour ajout à la description
          */
    }
    else
    {
        ui->lineEdit_commit->clear();
        ui->lineEdit_commit->setPlaceholderText(GIT_COMMIT_PLACEHOLDER);
    }
}

void TabGit::on_comboBox_branch_currentTextChanged(const QString &arg1)
{
    action(QStringList() << "checkout" << arg1);
}

void TabGit::on_toolButton_branch_clicked()
{

}

void TabGit::on_pushButton_add_clicked()
{
    action(QStringList() << "");
}

void TabGit::on_pushButton_reset_clicked()
{
    QStringList items;
    for(int i = 0; i < ui->listWidget_staged->count(); i++)
    {

    }
    action(QStringList() << "reset");
}

void TabGit::on_pushButton_checkout_clicked()
{
    action(QStringList() << "");
}

void TabGit::on_pushButton_gitk_clicked()
{
    QProcess process;
    process.setWorkingDirectory(m_process->workingDirectory());
    process.startDetached("gitk");
}

void TabGit::on_pushButton_tags_clicked()
{
    update_status();
}

void TabGit::on_pushButton_push_clicked()
{
    action(QStringList() << "push" << "origin" << ui->comboBox_branch->currentText());
}

void TabGit::on_pushButton_fetch_clicked()
{
    action(QStringList() << "fetch");
}

void TabGit::on_pushButton_rebase_clicked()
{
    if(action(QStringList() << "rebase" << ui->comboBox_branch->currentText()))
    {
        if(m_last_exit_code > 0)
        {

        }
    }
}

void TabGit::on_pushButton_extra_clicked()
{
    action(ui->lineEdit_extra->text().split(' '));
    ui->lineEdit_extra->clear();
}

/**
 * @param args Les argument pour la commande @b git
 * @return Si l'attribut TabGit::m_process est déjà en cours d'utilisation,
 * renvoie @c false, sinon, renvoie true après exécution de la fonction.
 *
 * Passe le curseur en mode attente. Exécute la commande @b git avec pour
 * arguments ceux passés en paramètres. Attend la fin de l'exécution de la
 * commande pour récupérer le code retour, la sortie et l'erreur.
 */
bool TabGit::action(QStringList args)
{
    if(m_process->state() == QProcess::NotRunning && args.length() > 0)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        emit status("Lancement git " + args.at(0), 3);
        m_process->start("git", args);
        m_process->waitForFinished();
        m_error = m_process->readAllStandardError();
        m_output = m_process->readAllStandardOutput();
        m_last_exit_code = m_process->exitCode();
        if(m_process->exitStatus() != QProcess::NormalExit) m_last_exit_code = -1;
        emit status("Fin d'exécution (code retour : " + QString::number(m_last_exit_code) + ")", 2);
        QApplication::restoreOverrideCursor();
        return true;
    }
    return false;
}

void TabGit::update_status()
{
    if(action(QStringList() << "status" << "-s"))
    {
        QStringList state_list = m_output.split('\n');
        state_list.sort();
        m_unmerged.clear();
        ui->listWidget_staged->clear();
        ui->listWidget_unstaged->clear();
        for(QString state : state_list)
        {
            if(state.length() > 3)
            {
                QString file_name = state.right(state.length()-3);
                if(state.at(0) == QChar('U') ||
                   state.at(1) == QChar('U'))
                {
                    m_unmerged.append(file_name);
                }
                else
                {
                    QString label0 = stateChar2Label(state.at(0));
                    QString label1 = stateChar2Label(state.at(1), true);
                    if(label0 != "")
                    {
                        ui->listWidget_staged->addItem(label0 + " : " + file_name);
                    }
                    if(label1 != "")
                    {
                        ui->listWidget_unstaged->addItem(label1 + " : " + file_name);
                    }
                }
            }
        }
    }
}

QString TabGit::stateChar2Label(QChar c, bool staged /*= false*/)
{
    if(c == QChar('A')) return GIT_STATUS_LABEL_A;
    else if(c == QChar('C')) return GIT_STATUS_LABEL_C;
    else if(c == QChar('D')) return GIT_STATUS_LABEL_D;
    else if(c == QChar('M')) return GIT_STATUS_LABEL_M;
    else if(c == QChar('R')) return GIT_STATUS_LABEL_R;
    else if(c == QChar('?') && !staged) return GIT_STATUS_LABEL_1;
    else if(c == QChar('!') && !staged) return GIT_STATUS_LABEL_2;
    else return "";
}

void TabGit::on_lineEdit_extra_returnPressed()
{
    on_pushButton_extra_clicked();
}
