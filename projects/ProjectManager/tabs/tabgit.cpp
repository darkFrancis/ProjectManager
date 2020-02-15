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
#include <QTimer>
#include "context.hpp"
#include "logger.hpp"
#include "context.hpp"
#include "errorviewer.hpp"
#include <QDebug>

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
    connect(&m_timer, &QTimer::timeout, this, &TabGit::update_all);
    ui->lineEdit_commit->setPlaceholderText(GIT_COMMIT_PLACEHOLDER);
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
    this->update_all();
    ui->comboBox_branch->setCurrentIndex(ui->comboBox_branch->findText(ui->label_branch->text().split(':').at(1).simplified()));
    m_timer.start(1000);
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
    if(action(args)) ui->lineEdit_commit->clear();
}

void TabGit::on_checkBox_amend_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        while(!action(QStringList() << "log" << "-n1" << "--pretty=format:%s", false)){}
        ui->lineEdit_commit->setText(m_output);
    }
    else
    {
        ui->lineEdit_commit->clear();
    }
}

void TabGit::on_toolButton_branch_clicked()
{

}

void TabGit::on_pushButton_add_clicked()
{
    QStringList selection = getSelected(ui->listWidget_unstaged);
    if(selection.length() == 0) action(QStringList() << "add" << ".");
    else action(QStringList() << "add" << selection);
}

void TabGit::on_pushButton_reset_clicked()
{
    QStringList selection = getSelected(ui->listWidget_staged);
    if(selection.length() == 0) action(QStringList() << "reset" << "HEAD");
    else action(QStringList() << "reset" << selection);
}

void TabGit::on_pushButton_checkout_clicked()
{
    QStringList selection = getSelected(ui->listWidget_staged);
    if(selection.length() == 0) action(QStringList() << "checkout" << "--" << ".");
    else action(QStringList() << "checkout" << "--" << selection);
}

void TabGit::on_pushButton_gitk_clicked()
{
    QProcess process;
    process.setWorkingDirectory(m_process->workingDirectory());
    process.startDetached("gitk", QStringList() << "--all");
}

void TabGit::on_pushButton_tags_clicked()
{

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
    action(QStringList() << "rebase" << ui->comboBox_branch->currentText());
}

void TabGit::on_pushButton_extra_clicked()
{
    if(action(ui->lineEdit_extra->text().split(' ')))
    {
        ui->lineEdit_extra->clear();
    }
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
bool TabGit::action(QStringList args, bool b_status /*= true*/)
{
    if(m_process->state() == QProcess::NotRunning && args.length() > 0)
    {
        if(b_status) emit status("Lancement git " + args.at(0), 3);
        m_process->start("git", args);
        m_process->waitForFinished();
        m_error = m_process->readAllStandardError();
        m_output = m_process->readAllStandardOutput();
        m_last_exit_code = m_process->exitCode();
        if(m_process->exitStatus() != QProcess::NormalExit) m_last_exit_code = -1;
        if(b_status) emit status("Fin d'exécution (code retour : " + QString::number(m_last_exit_code) + ")", 2);
        if(b_status && m_last_exit_code > 0)
        {
            ErrorViewer *w = new ErrorViewer(this,
                                             "Erreur d'exécution de la commande git",
                                             m_error);
            w->show();
            return false;
        }
        return true;
    }
    return false;
}

/**
 * Mise à jour du status.@n
 * Cette fonction utilise la commande @b git @b status pour récuppérer l'état courant
 * du dépôt git et actualise les listes de fichiers de cet onglet.
 */
void TabGit::update_status()
{
    QStringList tmp_select_stage = getSelected(ui->listWidget_staged, false);
    QStringList tmp_select_unstage = getSelected(ui->listWidget_unstaged, false);
    QStringList tmp_stage = getAllItems(ui->listWidget_staged, false);
    QStringList tmp_unstage = getAllItems(ui->listWidget_unstaged, false);

    if(action(QStringList() << "status" << "-s", false))
    {
        QStringList state_list = m_output.split('\n');
        state_list.sort();
        m_unmerged.clear();

        // Ajout des nouveaux items
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
                    QString label0 = stateChar2Label(state.at(0), true);
                    QString label1 = stateChar2Label(state.at(1));
                    if(label0 != "")
                    {
                        QString text = label0 + " : " + file_name;
                        if(!tmp_stage.contains(text))
                        {
                            ui->listWidget_staged->addItem(text);
                            if(tmp_select_stage.contains(text))
                            {
                                ui->listWidget_staged->item(ui->listWidget_staged->count()-1)->setSelected(true);
                            }
                        }
                        else
                        {
                            tmp_stage.removeOne(text);
                        }
                    }
                    if(label1 != "")
                    {
                        QString text = label1 + " : " + file_name;
                        if(!tmp_unstage.contains(text))
                        {
                            ui->listWidget_unstaged->addItem(label1 + " : " + file_name);
                            if(tmp_select_unstage.contains(text))
                            {
                                ui->listWidget_unstaged->item(ui->listWidget_unstaged->count()-1)->setSelected(true);
                            }
                        }
                        else
                        {
                            tmp_unstage.removeOne(text);
                        }
                    }
                }
            }
        }

        // Suppression des items qui n'existent plus
        for(int i = 0; i < tmp_stage.length(); i++)
        {
            for(int j = 0; j < ui->listWidget_staged->count(); j++)
            {
                if(tmp_stage[i] == ui->listWidget_staged->item(j)->text())
                {
                    ui->listWidget_staged->takeItem(j);
                }
            }
        }
        for(int i = 0; i < tmp_unstage.length(); i++)
        {
            for(int j = 0; j < ui->listWidget_unstaged->count(); j++)
            {
                if(tmp_unstage[i] == ui->listWidget_unstaged->item(j)->text())
                {
                    ui->listWidget_unstaged->takeItem(j);
                }
            }
        }

        // Tri
        ui->listWidget_staged->sortItems();
        ui->listWidget_unstaged->sortItems();
    }
}

void TabGit::update_branches()
{
    if(action(QStringList() << "branch", false))
    {
        QStringList branch_list = m_output.split('\n');
        int current_select = ui->comboBox_branch->currentIndex();
        ui->comboBox_branch->clear();
        for(QString branch : branch_list)
        {
            branch = branch.simplified();
            if(branch.length() > 0)
            {
                if(branch[0] == QChar('*'))
                {
                    branch = branch.right(branch.length()-2);
                    ui->label_branch->setText("Branche courante : " + branch);
                }
                ui->comboBox_branch->addItem(branch);
            }
        }
        ui->comboBox_branch->setCurrentIndex(current_select);
    }
}

void TabGit::update_all()
{
    update_branches();
    update_status();
    if(ui->listWidget_staged->count() == 0 && !ui->checkBox_amend->isChecked()) ui->pushButton_commit->setEnabled(false);
    else ui->pushButton_commit->setEnabled(true);
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

QStringList TabGit::getSelected(QListWidget *list_view, bool only_files /*= true*/)
{
    QStringList items;
    for(int i = 0; i < list_view->count(); i++)
    {
        if(list_view->item(i)->isSelected())
        {
            if(only_files) items << list_view->item(i)->text().split(':').at(1).simplified();
            else items << list_view->item(i)->text();
        }
    }
    return items;
}

QStringList TabGit::getAllItems(QListWidget *list_view, bool only_files /*= true*/)
{
    QStringList items;
    for(int i = 0; i < list_view->count(); i++)
    {
        if(only_files) items << list_view->item(i)->text().split(':').at(1).simplified();
        else items << list_view->item(i)->text();
    }
    return items;
}

void TabGit::on_lineEdit_extra_returnPressed()
{
    on_pushButton_extra_clicked();
}

void TabGit::on_pushButton_branchMerge_clicked()
{
    action(QStringList() << "merge" << ui->comboBox_branch->currentText());
}

void TabGit::on_pushButton_branchSwitch_clicked()
{
    action(QStringList() << "checkout" << ui->comboBox_branch->currentText());
}

void TabGit::on_comboBox_branch_currentIndexChanged(const QString &arg1)
{
    if(arg1 == ui->label_branch->text().split(':').at(1).simplified())
    {
        ui->pushButton_branchSwitch->setEnabled(false);
        ui->pushButton_branchMerge->setEnabled(false);
    }
    else
    {
        ui->pushButton_branchSwitch->setEnabled(true);
        ui->pushButton_branchMerge->setEnabled(true);
    }
}
