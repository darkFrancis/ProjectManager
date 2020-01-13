#include "settingswindow.hpp"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
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
