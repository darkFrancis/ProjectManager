#include "settingswindow.hpp"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
     QList<Color>* colors = Settings::Instance()->colors();
    for(int i = 0; i < colors->length(); i++)
    {
        ui->comboBox_colorNormal->addItem(colors->at(i).name);
        //ui->comboBox_colorNormal->setItemData(i, colors->at(i).hex_name, Qt::DecorationRole);
    }

    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_pushButton_ok_clicked()
{
    save();
    this->close();
}

void SettingsWindow::on_pushButton_apply_clicked()
{
    save();
}

void SettingsWindow::on_pushButton_cancel_clicked()
{
    this->close();
}

void SettingsWindow::save()
{
    Settings* setting = Settings::Instance();
    setting->setStyle(ui->comboBox_viewStyle->currentText());
    setting->setKeepSize(ui->checkBox_keepViewSize->isChecked());
    setting->setDoxygenTemplateDir(ui->lineEdit_doxygenTemplate->text());
    setting->setClearScreen(ui->checkBox_autoclearScreen->isChecked());
    setting->save();
}
