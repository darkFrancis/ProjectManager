#include "settingswindow.hpp"
#include "ui_settingswindow.h"
#include <QMessageBox>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    QList<Color>* colors;

    try
    {
       colors = Settings::Instance()->colors();
    }
    catch (QString msg)
    {
        QMessageBox::critical(this, "Erreur", msg);
    }

    QPixmap pixmap(20, 15);
    for(int i = 0; i < colors->length(); i++)
    {
        pixmap.fill(QColor::fromRgb(colors->at(i).red, colors->at(i).green, colors->at(i).blue));
        ui->comboBox_colorNormal->addItem(QIcon(pixmap), colors->at(i).name);
        ui->comboBox_colorError->addItem(QIcon(pixmap), colors->at(i).name);
        ui->comboBox_colorSuccess->addItem(QIcon(pixmap), colors->at(i).name);
    }

    // Set values
    Settings* settings = Settings::Instance();
    ui->comboBox_viewStyle->setCurrentIndex(ui->comboBox_viewStyle->findText(settings->style()));
    ui->checkBox_keepViewSize->setChecked(settings->keepSize());
    ui->lineEdit_doxygenTemplate->setText(settings->doxygenTemplateDir());
    ui->checkBox_autoclearScreen->setChecked(settings->clearScreen());
    ui->comboBox_colorNormal->setCurrentIndex(ui->comboBox_colorNormal->findText(settings->colorNormal()));
    ui->comboBox_colorError->setCurrentIndex(ui->comboBox_colorError->findText(settings->colorError()));
    ui->comboBox_colorSuccess->setCurrentIndex(ui->comboBox_colorSuccess->findText(settings->colorSuccess()));
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
    setting->setColorNormal(ui->comboBox_colorNormal->currentText());
    setting->setColorSuccess(ui->comboBox_colorSuccess->currentText());
    setting->setColorError(ui->comboBox_colorError->currentText());
    setting->save();
}
