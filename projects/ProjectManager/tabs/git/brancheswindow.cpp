#include "brancheswindow.hpp"
#include "ui_brancheswindow.h"

#include <QMessageBox>

BranchesWindow::BranchesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BranchesWindow)
{
    ui->setupUi(this);
}

BranchesWindow::~BranchesWindow()
{
    delete ui;
}

void BranchesWindow::update_branches(QStringList branches)
{
    QString branch;
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
    ui->listWidget_branch->clear();
    ui->listWidget_branch->addItems(branches);
    ui->listWidget_branch->item(0)->setSelected(true);
}

void BranchesWindow::on_listWidget_branch_currentItemChanged(QListWidgetItem *current, QListWidgetItem*)
{
    ui->label_selected->setText(current->text() + " ->");
}

void BranchesWindow::on_pushButton_add_clicked()
{
    QString name = ui->lineEdit_add->text().simplified();
    for(int i = 0; i < name.length(); i++)
    {
        if(!name[i].isLetterOrNumber())
        {
            QMessageBox::warning(this,
                                 "Attention",
                                 "Un nom de branches ne peut contenir que des"
                                 "caractères alphanumériques !");
            return;
        }
    }
    emit action(QStringList() << "branch" << name);
}

void BranchesWindow::on_pushButton_rename_clicked()
{

}

void BranchesWindow::on_pushButton_copy_clicked()
{

}

void BranchesWindow::on_pushButton_remove_clicked()
{

}
