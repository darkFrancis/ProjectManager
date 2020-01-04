#include "gitstatus.hpp"
#include "ui_gitstatus.h"

GitStatus::GitStatus(QWidget *parent, QString line) :
    QWidget(parent),
    ui(new Ui::GitStatus)
{
    ui->setupUi(this);

    if(line != "")
    {
        newLine(line);
    }
}

GitStatus::~GitStatus()
{
    delete ui;
}

void GitStatus::newLine(QString line)
{
    setStatus(line.left(2));
    setFile(line.right(line.length()-3));
    ui->checkBox->setChecked(false);
}

void GitStatus::setFile(QString file)
{
    ui->label_file->setText(file);
}

QString GitStatus::file()
{
    return ui->label_file->text();
}

void GitStatus::setStatus(QString status)
{
    if(status.length() == 2)
    {
        m_status_str = status;
        m_status.status_index = status[0].toLatin1();
        m_status.status_worktree = status[1].toLatin1();
        setStatusName(m_status.status_index, ui->label_status_index);
        setStatusName(m_status.status_worktree, ui->label_status_worktree);
    }
    else
    {
        throw(QString("Erreur, le status doit être codé sur 2 caractères"));
    }
}

QString GitStatus::statusStr()
{
    return m_status_str;
}

sGitStatus GitStatus::status()
{
    return m_status;
}

void GitStatus::setChecked(bool checked /*= true*/)
{
    ui->checkBox->setChecked(checked);
}

bool GitStatus::isChecked()
{
    return ui->checkBox->isChecked();
}

void GitStatus::setStatusName(char status, QLabel *label)
{
    if(status == ' ')
    {
        label->setText("Non modifié");
    }
    else if(status == 'M')
    {
        label->setText("Modifié");
    }
    else if(status == 'A')
    {
        label->setText("Ajouté");
    }
    else if(status == 'D')
    {
        label->setText("Supprimé");
    }
    else if(status == 'R')
    {
        label->setText("Renommé");
    }
    else if(status == 'C')
    {
        label->setText("Copié");
    }
    else if(status == 'U')
    {
        label->setText("Non fusionné");
    }
    else if(status == '!')
    {
        label->setText("Ignoré");
    }
    else if(status == '?')
    {
        label->setText("Non suivi");
    }
    else
    {
        label->setText("###Unknow###");
        throw(QString("Erreur, status inconnu : ") + status);
    }
}
