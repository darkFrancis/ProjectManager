/**
 * @file settingswindow.cpp
 * @brief Définition des fonctions de la classe SettingsWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "settingswindow.hpp"
#include "ui_settingswindow.h"
#include "logger.hpp"
#include <QMessageBox>

/**
 * @param parent Le QWidget parent de cette fenêtre
 *
 * Contructeur de la classe SettingsWindow.@n
 * Ce constructeur hérite de celui de QMainWindow et utilise le système des fichiers d'interface utilisateur.@n
 * Les différents champs sont remplis en fonction des attributs de l'instance Settings.@n
 * Voir @ref SETTING_GET, Ui.
 */
SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    logger(__PRETTY_FUNCTION__);

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
    ui->lineEdit_sourcesExt->setText(settings->sourcesExtensions().join(' '));
    ui->lineEdit_headersExt->setText(settings->headersExtensions().join(' '));
}

/**
 * Destructeur de la classe SettingsWindow.
 */
SettingsWindow::~SettingsWindow()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton OK de la fenêtre.@n
 * Il commande un enregistrement des modifications apportées à travers la
 * fonction SettingsWindow::save puis ferme cette fenêtre.
 */
void SettingsWindow::on_pushButton_ok_clicked()
{
    logger(__PRETTY_FUNCTION__);
    save();
    this->close();
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton Appliquer de la fenêtre.@n
 * Il commande un enregistrement des modifications apportées à travers la
 * fonction SettingsWindow::save.
 */
void SettingsWindow::on_pushButton_apply_clicked()
{
    logger(__PRETTY_FUNCTION__);
    save();
}

/**
 * Ce connecteur est activé lors d'un clic sur le bouton OK de la fenêtre.@n
 * Il ferme cette fenêtre.
 */
void SettingsWindow::on_pushButton_cancel_clicked()
{
    logger(__PRETTY_FUNCTION__);
    this->close();
}

/**
 * Enregistre les modification apportées par l'utilisateur à travers la fenêtre.@n
 * Voir @ref SETTING_SET.
 */
void SettingsWindow::save()
{
    logger(__PRETTY_FUNCTION__);
    Settings* setting = Settings::Instance();
    setting->setStyle(ui->comboBox_viewStyle->currentText());
    setting->setKeepSize(ui->checkBox_keepViewSize->isChecked());
    setting->setDoxygenTemplateDir(ui->lineEdit_doxygenTemplate->text());
    setting->setClearScreen(ui->checkBox_autoclearScreen->isChecked());
    setting->setColorNormal(ui->comboBox_colorNormal->currentText());
    setting->setColorSuccess(ui->comboBox_colorSuccess->currentText());
    setting->setColorError(ui->comboBox_colorError->currentText());
    setting->setSourcesExtensions(ui->lineEdit_sourcesExt->text().split(' '));
    setting->setHeadersExtensions(ui->lineEdit_headersExt->text().split(' '));
    setting->save();
}
