#include "gitstatus.hpp"
#include "ui_gitstatus.h"

GitStatus::GitStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GitStatus)
{
    ui->setupUi(this);
}

GitStatus::~GitStatus()
{
    delete ui;
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
    if(status.length() != 2)
    {
        throw(QString("Erreur, le status doit faire éxactement 2 charactères !"));
    }
    if(status[0])
}

QString GitStatus::statusStr()
{
    return m_status_str;
}

eGitStatus GitStatus::status()
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
