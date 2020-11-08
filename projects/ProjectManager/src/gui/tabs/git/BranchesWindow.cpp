/**
 * @file BranchesWindow.cpp
 * @brief Source de la fenêtre de gestion des branches
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "BranchesWindow.hpp"
#include "ui_BranchesWindow.h"

#include <QMessageBox>

/**
 * @param parent Le QWidget parent de cette fenêtre
 *
 * Contructeur de la classe BranchesWindow.@n
 * Ce constructeur rend la fenêtre modale.
 */
BranchesWindow::BranchesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BranchesWindow)
{
    ui->setupUi(this);

    this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_QuitOnClose);
}

/**
 * Destructeur de la classe BranchesWindow.
 */
BranchesWindow::~BranchesWindow()
{
    delete ui;
}

/**
 * @param branches Nouvelle liste des branches
 *
 * Met à jour la liste des branches en la remplaçant par la liste
 * @c branches fournies en argument de cette fonction. Si l'élément
 * qui était précédemment sélectionné est modifié/supprimé, le
 * premier élément de la liste devient l'élément sélectionné.
 */
void BranchesWindow::update_branches(QStringList branches)
{
    ui->lineEdit_add->clear();

    QString branch;
    QString selected = get_selected();
    for(int i = 0; i < branches.length(); i++)
    {
        branch = branches[i];
        if(branch.simplified() == "")
        {
            branches.removeAt(i);
            i--;
        }
        else if(branch[0] == QChar('*'))
        {
            branches[i] = branch.split(' ').at(1).simplified();
        }
        else
        {
            branches[i] = branch.simplified();
        }
    }

    // Ajout/Suppression
    for(int i = 0; i < ui->listWidget_branch->count(); i++)
    {
        branch = ui->listWidget_branch->item(i)->text().simplified();
        if(branches.contains(branch))
        {
            branches.takeAt(branches.indexOf(branch));
        }
        else
        {
            ui->listWidget_branch->takeItem(i);
            i--;
        }
    }
    if(branches.length() > 0)
    {
        ui->listWidget_branch->addItems(branches);
        ui->listWidget_branch->sortItems();
    }

    // Gestion sélection
    for(int i = 0; i < ui->listWidget_branch->count(); i++)
    {
        if(ui->listWidget_branch->item(i)->text() == selected)
        {
            ui->listWidget_branch->item(i)->setSelected(true);
            on_listWidget_branch_currentItemChanged(ui->listWidget_branch->item(i), nullptr);
            return;
        }
    }
    ui->listWidget_branch->item(0)->setSelected(true);
    on_listWidget_branch_currentItemChanged(ui->listWidget_branch->item(0), nullptr);
}

/**
 * @param current Nouvel item sélectionné
 *
 * Ce connecteur est activé lorsque l'utilisateur sélectionne un
 * nouvel item dans la liste.@n
 * Change le label de la branche sélectionnée avec le nom de l'item
 * @c current sélectionné.
 */
void BranchesWindow::on_listWidget_branch_currentItemChanged(QListWidgetItem *current, QListWidgetItem*)
{
    ui->label_selected->setText(current->text() + " ->");
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Ajouter.@n
 * Ajoute la branche si le nom est valide.
 * @sa check_branch_name().
 */
void BranchesWindow::on_pushButton_add_clicked()
{
    QString name = ui->lineEdit_add->text().simplified();
    if(check_branch_name(name))
        emit action(QStringList() << "branch" << name);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Renommer.@n
 * Renomme la branche sélectionnée avec le nom demandé si valide.
 * @sa check_branch_name().
 */
void BranchesWindow::on_pushButton_rename_clicked()
{
    QString name = ui->lineEdit_add->text().simplified();
    if(check_branch_name(name))
    {
        QString branch = get_selected();
        if(branch != "")
            emit action(QStringList() << "branch" << "-m" << branch << name);
    }
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Copier.@n
 * Si le nom est valide, copie la branche avec le nom demandé.
 * @sa check_branch_name().
 */
void BranchesWindow::on_pushButton_copy_clicked()
{
    QString name = ui->lineEdit_add->text().simplified();
    if(check_branch_name(name))
    {
        QString branch = get_selected();
        if(branch != "")
            emit action(QStringList() << "branch" << "-c" << branch << name);
    }
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Supprimer.@n
 * Supprime la branche sélectionnée.
 */
void BranchesWindow::on_pushButton_remove_clicked()
{
    QString branch = get_selected();
    if(branch != "") emit action(QStringList() << "branch" << "-d" << branch);
}

/**
 * @param name Nom de branche Git
 * @return @li @b true si le nom ne contient  que des chiffres ou des lettres
 *         @li @b false sinon
 *
 * Vérifie que le nom de la branche ne contient que des caractères alphanumériques.
 * @note Une popup d'erreur apparaît en cas de retour @b false.
 */
bool BranchesWindow::check_branch_name(const QString& name)
{
    for(int i = 0; i < name.length(); i++)
    {
        if(!name[i].isLetterOrNumber())
        {
            QMessageBox::warning(this,
                                 "Attention",
                                 "Un nom de branche ne peut contenir que des "
                                 "caractères alphanumériques !");
            return false;
        }
    }
    return true;
}

/**
 * @return Elément sélectionné
 *
 * Cherche l'élément sélectionné dans la liste et renvoie son texte.
 */
QString BranchesWindow::get_selected()
{
    if(ui->listWidget_branch->selectedItems().length() > 0)
    {
        return ui->listWidget_branch->selectedItems().at(0)->text().simplified();
    }
    return "";
}
