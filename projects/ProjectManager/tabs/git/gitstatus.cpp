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
        if(status == "!!")
        {
            m_type = GitStatusType::Ignored;
        }
        else if(status == "??")
        {
            m_type = GitStatusType::Untracked;
        }
        else if(status[0] == ' ')
        {
            m_type = GitStatusType::WorkTree;
        }
        else if(status[1] == ' ')
        {
            m_type = GitStatusType::Index;
        }
        else
        {
            m_type = GitStatusType::IndexAndWorkTree;
        }
    }
    else
    {
        throw(QString("Erreur, le status doit être codé sur 2 caractères"));
    }
}

void GitStatus::setNameFor(GitStatusType type)
{
    switch (type)
    {
        case GitStatusType::Ignored:
            ui->checkBox->setVisible(false);
            if(m_status_str == "!!")
            {
                ui->label_status->setText(getStatusName('!'));
            }
            else
            {
                ui->label_status->setText(getStatusName('X'));
                throw(QString("Erreur, mauvaise catégorie : " + m_status_str + " != Ignored"));
            }
            break;
        case GitStatusType::Untracked:
            if(m_status_str == "??")
            {
                ui->label_status->setText(getStatusName('?'));
                ui->checkBox->setVisible(true);
            }
            else
            {
                ui->label_status->setText(getStatusName('X'));
                ui->checkBox->setVisible(false);
                throw(QString("Erreur, mauvaise catégorie : " + m_status_str + " != Untracked"));
            }
            break;
        case GitStatusType::Index:
            ui->checkBox->setVisible(false);
            if(m_type == GitStatusType::Index || m_type == GitStatusType::IndexAndWorkTree)
            {
                ui->label_status->setText(getStatusName(m_status_str[0]));
                ui->label_file->setText("<a href=\"" + ui->label_file->text() + "\">" + ui->label_file->text() + "</a>");
            }
            else
            {
                ui->label_status->setText(getStatusName('X'));
                throw(QString("Erreur, mauvaise catégorie : " + m_status_str + " != Index"));
            }
            break;
        case GitStatusType::WorkTree:
            if(m_type == GitStatusType::WorkTree || m_type == GitStatusType::IndexAndWorkTree)
            {
                ui->label_status->setText(getStatusName(m_status_str[1]));
                ui->checkBox->setVisible(true);
            }
            else
            {
                ui->label_status->setText(getStatusName('X'));
                ui->checkBox->setVisible(false);
                throw(QString("Erreur, mauvaise catégorie : " + m_status_str + " != WorkTree"));
            }
            break;
        case GitStatusType::IndexAndWorkTree:
            ui->checkBox->setVisible(false);
            throw(QString("Impossible d'affecter à IndexAndWorkTree"));
    }
}

QString GitStatus::statusStr()
{
    return m_status_str;
}

GitStatusType GitStatus::statusType()
{
    return m_type;
}

void GitStatus::setChecked(bool checked /*= true*/)
{
    ui->checkBox->setChecked(checked);
}

bool GitStatus::isChecked()
{
    return ui->checkBox->isChecked();
}

QString GitStatus::getStatusName(QChar status)
{
    if(status == ' ')
    {
        return "Non modifié";
    }
    else if(status == 'M')
    {
        return "Modifié";
    }
    else if(status == 'A')
    {
        return "Ajouté";
    }
    else if(status == 'D')
    {
        return "Supprimé";
    }
    else if(status == 'R')
    {
        return "Renommé";
    }
    else if(status == 'C')
    {
        return "Copié";
    }
    else if(status == 'U')
    {
        return "Non fusionné";
    }
    else if(status == '!')
    {
        return "Ignoré";
    }
    else if(status == '?')
    {
        return "Non suivi";
    }
    else
    {
        return "###Unknow###";
    }
}

void GitStatus::on_label_file_linkActivated(const QString &link)
{
    emit diff(link);
}
