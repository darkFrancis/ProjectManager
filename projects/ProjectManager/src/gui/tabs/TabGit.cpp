/**
 * @file TabGit.cpp
 * @brief Définition de la classe TabGit
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "TabGit.hpp"
#include "ui_TabGit.h"

#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <QTimer>
#include "ErrorViewer.hpp"
#include "TagsWindow.hpp"
#include "BranchesWindow.hpp"
#include "Context.hpp"

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

    m_process = new QProcess();
    connect(&m_timer, &QTimer::timeout, this, &TabGit::update_all);
    ui->lineEdit_commit->setPlaceholderText(GIT_COMMIT_PLACEHOLDER);
}

/**
 * Destructeur de la classe TabGit.
 */
TabGit::~TabGit()
{
    clean();
    delete ui;
}

/**
 * Fonction d'initialisation de l'onglet TabGit.@n
 * Récupère les informations du projet avec les méthodes GET de la classe
 * Context pour charger les informations nécessaires au bon fonctionnement
 * de cet onglet. Puis démarre le timer TabGit::m_timer.@n
 * Voir @ref CONTEXT_GET.
 */
void TabGit::init()
{
    m_process->setWorkingDirectory(qCtx->projectDir());
    this->update_all();
    ui->comboBox_branch->setCurrentIndex(ui->comboBox_branch->findText(ui->label_branch->text().split(':').at(1).simplified()));
    ui->comboBox_remote->setCurrentIndex(0);
    m_timer.start(1000);
}

/**
 * Fonction de nettoyage de l'onglet Git.@n
 * Vide toute les liste de cet onglet et tue le processus en cours
 * s'il y en a un.
 */
void TabGit::clean()
{
    ui->listWidget_staged->clear();
    ui->listWidget_unstaged->clear();
    ui->checkBox_amend->setChecked(false);
    ui->lineEdit_commit->clear();
    ui->comboBox_branch->clear();
    ui->comboBox_remote->clear();
    m_process->kill();
    delete m_process;
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Commit.@n
 * Exécute la commande @b git @b commit grâce à la fonction TabGit::action.
 * Si aucun message n'est renseigné, le message #GIT_COMMIT_DEFAULT_MSG est
 * utilisé pour l'option @b -m de cette commande.
 */
void TabGit::on_pushButton_commit_clicked()
{
    QStringList args;
    args << "commit";
    if(ui->checkBox_amend->isChecked()) args << "--amend";
    args << "-m";
    QString msg = ui->lineEdit_commit->text().simplified();
    if(msg == QString("")) args << GIT_COMMIT_DEFAULT_MSG;
    else args << msg;
    if(action(args))
    {
        ui->lineEdit_commit->clear();
        ui->checkBox_amend->setChecked(false);
    }
}

/**
 * @param arg1 Nouvel état de la case
 *
 * Ce connecteur est activé en cas de changement d'état de la case cochable
 * amend.@n
 * @li Si cette case vient d'être cochée, affiche le dernier message de commit
 * dans la ligne d'édition permettant d'éditer le message du prochain commit.
 * @li Sinon, efface la ligne du message.
 */
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

/**
 * Ce connecteur est activé suite à un clic souris de l'utilisateur sur
 * le bouton outil "..." à droite de la sélection des branches.@n
 * Ouvre la fenêtre de gestion des branches.@n
 * Voir BranchesWindow.
 */
void TabGit::on_toolButton_branch_clicked()
{
    if(action(QStringList() << "branch"))
    {
        BranchesWindow* w = new BranchesWindow(this);
        connect(w, &BranchesWindow::action, this, &TabGit::action_branch);
        connect(this, &TabGit::branch_update, w, &BranchesWindow::update_branches);
        w->show();
        w->update_branches(m_output.split('\n'));
    }
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Add.@n
 * Exécute la commande @b git @b add grâce à la fonction TabGit::action.
 * Si aucun élément dans la liste Unstaged n'est sélectionné, alors cette
 * fonction considèrera qu'ils sont tous sélectionnés. Sinon, n'exécute
 * la commande que pour les éléments sélectionnés.
 */
void TabGit::on_pushButton_add_clicked()
{
    QStringList selection = getSelected(ui->listWidget_unstaged);
    if(selection.length() == 0) action(QStringList() << "add" << ".");
    else action(QStringList() << "add" << selection);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Reset.@n
 * Exécute la commande @b git @b reset grâce à la fonction TabGit::action.
 * Si aucun élément dans la liste Staged n'est sélectionné, alors cette
 * fonction considèrera qu'ils sont tous sélectionnés. Sinon, n'exécute
 * la commande que pour les éléments sélectionnés.
 */
void TabGit::on_pushButton_reset_clicked()
{
    QStringList selection = getSelected(ui->listWidget_staged);
    if(selection.length() == 0) action(QStringList() << "reset" << "HEAD");
    else action(QStringList() << "reset" << selection);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Checkout.@n
 * Exécute la commande @b git @b checkout @b -- grâce à la fonction
 * TabGit::action. Si aucun élément dans la liste Staged n'est sélectionné,
 * alors cette fonction ne fera absolument rien. Sinon, n'exécute la commande
 * que pour les éléments sélectionnés.
 */
void TabGit::on_pushButton_checkout_clicked()
{
    QStringList selection = getSelected(ui->listWidget_staged);
    selection << getSelected(ui->listWidget_unstaged);
    selection.removeDuplicates();
    if(selection.length() > 0)
    {
        QMessageBox::StandardButton rep;
        rep = QMessageBox::question(this,
                                    "Checkout",
                                    "Êtes-vous sûr de vouloir annuler les modifications"
                                    "apportées à ces fichiers ?\n" +
                                    selection.join('\n'));
        if(rep == QMessageBox::Yes) action(QStringList() << "checkout" << "--" << selection);
    }
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Gitk.@n
 * Exécute la commande @b gitk.
 */
void TabGit::on_pushButton_gitk_clicked()
{
    QProcess process;
    process.setWorkingDirectory(m_process->workingDirectory());
    process.startDetached("gitk", QStringList() << "--all" << "--date-order");
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Tags.@n
 * Ouvre la fenêtre de gestion des tags.
 */
void TabGit::on_pushButton_tags_clicked()
{
    while(!action(QStringList() << "tag", false)){}
    TagsWindow* w = new TagsWindow(this, m_output.split('\n'));
    connect(w, &TagsWindow::action, this, &TabGit::action_tags);
    connect(this, &TabGit::tag_created, w, &TagsWindow::clean_tag_name);
    connect(this, &TabGit::tag_update, w, &TagsWindow::update_tags);
    w->show();
}

/**
 * Ce connesteur est activé par un clic souris de l'utilisateur sur le bouton
 * Conflit.
 *
 * @todo Finir fenêtre de gestion des conflits et l'ouvrir
 */
void TabGit::on_pushButton_conflicts_clicked()
{
    QMessageBox::information(this,
                             "Information",
                             "Cette fonctionnalité est encore en cours de développement."
                             "Revenez plus tard.");
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Push.@n
 * Exécute la commande @b git @b push grâce à la fonction TabGit::action.
 * Cette commande va pousser la branche sélectionnée dans la liste déroulante
 * des branches vers le dépôt distant sélectionné dans la liste déroulantes
 * des dépôts distants.
 */
void TabGit::on_pushButton_push_clicked()
{
    action(QStringList() << "push" << ui->comboBox_remote->currentText() << ui->comboBox_branch->currentText());
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Fetch.@n
 * Exécute la commande @b git @b fetch grâce à la fonction TabGit::action.
 * Cette commande va récupérer les nouveaux commit depuis le dépôt distant
 * sélectionné dans la liste déroulantes des dépôts distants.
 */
void TabGit::on_pushButton_fetch_clicked()
{
    action(QStringList() << "fetch" << ui->comboBox_remote->currentText());
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Rebase.@n
 * Exécute la commande @b git @b rebase grâce à la fonction TabGit::action.
 * Cette commande va réorganiser les commit sur la branche courante.
 */
void TabGit::on_pushButton_rebase_clicked()
{
    action(QStringList() << "rebase");
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Exécuter.@n
 * Exécute la commande @b git @b &lt;cmd> grâce à la fonction TabGit::action.
 * La commande à exécuter est celle renseignée dans la ligne d'édition à la
 * gauche de ce bouton.
 */
void TabGit::on_pushButton_extra_clicked()
{
    if(action(ui->lineEdit_extra->text().split(' ')))
    {
        ui->lineEdit_extra->clear();
    }
}

/**
 * @param args Les argument pour la commande @b git
 * @param b_status Indicateur d'affichage du status de l'action
 * @return Si l'attribut TabGit::m_process est déjà en cours d'utilisation,
 * renvoie @c false, sinon, renvoie true après exécution de la fonction.
 *
 * Passe le curseur en mode attente. Exécute la commande @b git avec pour
 * arguments ceux passés en paramètres. Attend la fin de l'exécution de la
 * commande pour récupérer le code retour, la sortie et l'erreur.
 */
bool TabGit::action(const QStringList& args, bool b_status /*= true*/)
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

/**
 * Mise à jour des branches.@n
 * Cette fonction utilise la commande @b git @b branch pour récuppérer la liste
 * des branche du dépôt git et actualise la liste des branches de cet onglet.
 */
void TabGit::update_branches()
{
    if(action(QStringList() << "branch", false))
    {
        QStringList branch_list = m_output.split('\n');
        QString current_text = ui->comboBox_branch->currentText();
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
        ui->comboBox_branch->setCurrentIndex(ui->comboBox_branch->findText(current_text));
    }
}

/**
 * Mise à jour des dépôts distants.@n
 * Cette fonction utilise la commande @b git @b remote pour récuppérer la liste
 * des dépôts distants et actualise la liste des dépôts distants de cet onglet.
 */
void TabGit::update_remote()
{
    if(action(QStringList() << "remote", false))
    {
        QStringList remote_list = m_output.split('\n');
        QString current_text = ui->comboBox_remote->currentText();
        ui->comboBox_remote->clear();
        for(QString remote : remote_list)
        {
            remote = remote.simplified();
            if(remote.length() > 0)
            {
                ui->comboBox_remote->addItem(remote);
            }
        }
        ui->comboBox_remote->setCurrentIndex(ui->comboBox_remote->findText(current_text));
    }
}

/**
 * Mise à jour générale.@n
 * Appelle les fonctions TabGit::update_branches, TabGit::update_status et
 * TabGit::update_remote pour mettre à jour les listes de cet onglet.
 */
void TabGit::update_all()
{
    update_branches();
    update_status();
    update_remote();
    if(ui->listWidget_staged->count() == 0 && !ui->checkBox_amend->isChecked()) ui->pushButton_commit->setEnabled(false);
    else ui->pushButton_commit->setEnabled(true);
}

/**
 * @param c Caractère d'état du fichier
 * @param staged Provient de la colonne staged
 * @return Libellé à afficher
 *
 * Cette fonction permet de renvoyer le libellé à afficher en fonction du
 * caractère renvoyé par la fonction @b git @b status @b -s.
 */
QString TabGit::stateChar2Label(const QChar& c, bool staged /*= false*/)
{
    if(c == QChar('A')) return GIT_STATUS_LABEL_A;
    else if(c == QChar('C')) return GIT_STATUS_LABEL_C;
    else if(c == QChar('D')) return GIT_STATUS_LABEL_D;
    else if(c == QChar('M')) return GIT_STATUS_LABEL_M;
    else if(c == QChar('R')) return GIT_STATUS_LABEL_R;
    else if(c == QChar('U')) return GIT_STATUS_LABEL_U;
    else if(c == QChar('?') && !staged) return GIT_STATUS_LABEL_1;
    else if(c == QChar('!') && !staged) return GIT_STATUS_LABEL_2;
    else return "";
}

/**
 * @param list_view QListWidget d'où proviennent les items
 * @param only_files Booléen de sélection de la forme de sortie
 * @return Liste des éléments sélectionnés
 *
 * Renvoie la liste des éléments sélectionnés dans le QListWidget @c list_view
 * sous forme d'une liste de chaînes de caractères. Si @c only_files est passé
 * à @b true, cette liste ne contient pas l'état des fichiers de cette liste.
 */
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

/**
 * @param list_view QListWidget d'où proviennent les items
 * @param only_files Booléen de sélection de la forme de sortie
 * @return Liste des éléments
 *
 * Renvoie la liste des éléments dans le QListWidget @c list_view sous forme
 * d'une liste de chaînes de caractères. Si @c only_files est passé à @b true,
 * cette liste ne contient pas l'état des fichiers de cette liste.
 */
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

/**
 * Ce connecteur est activé par un retour clavier depuis la ligne d'édition des
 * commandes personnalisées.@n
 * Exécute la même action que la fonction TabGit::on_pushButton_extra_clicked.
 */
void TabGit::on_lineEdit_extra_returnPressed()
{
    on_pushButton_extra_clicked();
}

/**
 * Ce connesteur est activé par un clic souris de l'utilisateur sur le bouton
 * de merge de branche.@n
 * Appelle la fonction TabGit::action avec comme paramètre la commande @b git
 * @b merge et le nom de la branche sélectionnée dans la liste déroulante.
 */
void TabGit::on_pushButton_branchMerge_clicked()
{
    action(QStringList() << "merge" << ui->comboBox_branch->currentText());
}

/**
 * Ce connesteur est activé par un clic souris de l'utilisateur sur le bouton
 * de changement de branche (->).@n
 * Appelle la fonction TabGit::action avec comme paramètre la commande @b git
 * @b checkout et le nom de la branche sélectionnée dans la liste déroulante.
 */
void TabGit::on_pushButton_branchSwitch_clicked()
{
    action(QStringList() << "checkout" << ui->comboBox_branch->currentText());
}

/**
 * @param arg1 Nouveau texte de la liste déroulante
 *
 * Ce connecteur est appelé si le texte de la liste déroulante de sélection
 * des branches est modifié.@n
 * @li Si le nom de la branche de la liste déroulante est le nom de la branche
 * courante, désactive les boutons "Merge" et "->"
 * @li Sinon, ces boutons sont activés
 */
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

/**
 * @param args Argument pour la commande Git
 *
 * Ce connecteur est appelé par l'émission du signal TagsWindow::action.@n
 * La commande git contenue dans le paramètre @c args est exécutée par un
 * appel à la fonction TabGit::action. Il existe 2 commandes qui entraine
 * des actions supplémentaires :
 * @li @b push : ajout du dépôt distant dans la commande
 * @li création : émission du signal TabGit::tag_created en fin d'exécution
 * @li par défaut : émission du signal TabGit::tag_update en fin d'exécution
 */
void TabGit::action_tags(QStringList args)
{
    if(args.length() > 0)
    {
        if(args[0] == QString("push"))
        {
            args << ui->comboBox_remote->currentText() << "--tags";
        }
        if(action(args))
        {
            if(m_output.simplified() == "") emit tag_created(); // Création d'un nouveau tag
            while(!action(QStringList() << "tag")){}
            emit tag_update(m_output.split('\n'));
        }
    }
}

/**
 * @param args Argument pour la commande Git
 *
 * Ce connecteur est appelé par l'émission du signal BranchesWindow::action.@n
 * La commande git contenue dans le paramètre @c args est exécutée par un
 * appel à la fonction TabGit::action. Le signal TabGit::branch_update est
 * émit en fin d'exécution.
 */
void TabGit::action_branch(const QStringList& args)
{
    if(args.length() > 0)
    {
        if(action(args))
        {
            while(!action(QStringList() << "branch")){}
            emit branch_update(m_output.split('\n'));
        }
    }
}

/**
 * Ce connecteur est activé par un retour clavier depuis la ligne d'édition des
 * messages pour commit.@n
 * Exécute la même action que la fonction TabGit::on_pushButton_commit_clicked.
 */
void TabGit::on_lineEdit_commit_returnPressed()
{
    on_pushButton_commit_clicked();
}
