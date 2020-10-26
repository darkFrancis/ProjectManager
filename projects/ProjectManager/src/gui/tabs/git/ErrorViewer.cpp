/**
 * @file ErrorViewer.cpp
 * @brief Définition de la classe ErrorViewer
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "ErrorViewer.hpp"
#include "ui_ErrorViewer.h"

/**
 * @param parent Le QWidget parent de cet onglet
 * @param error Erreur à afficher
 * @param details Détails de l'erreur
 *
 * Contructeur de la classe ErrorViewer.@n
 * Ce constructeur hérite de celui de QMainWindow et utilise le système des fichiers
 * d'interface utilisateur.@n
 * Ajoute les textes passés en arguments aux widgets associés. Cette fenêtre est modale.@n
 * Voir Ui.
 */
ErrorViewer::ErrorViewer(QWidget *parent, const QString& error, const QString& details) :
    QMainWindow(parent),
    ui(new Ui::ErrorViewer)
{
    ui->setupUi(this);

    this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_QuitOnClose, false);
    ui->label_error->setText(error);
    ui->textEdit_details->setHidden(true);
    ui->textEdit_details->setText(details);
}

/**
 * Destructeur de la classe ErrorViewer.
 */
ErrorViewer::~ErrorViewer()
{
    delete ui;
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le
 * bouton Détails.@n
 * Affiche/masque la zone de texte de détail de l'erreur. Redimmentionne
 * la fenêtre au besoin.
 */
void ErrorViewer::on_pushButton_details_clicked()
{
    int h, w;
    if(ui->textEdit_details->isVisible())
    {
        ui->textEdit_details->setHidden(true);
        h = ui->label_error->height() +
            ui->pushButton_details->height() +
            ui->centralwidget->layout()->margin() * 3;
        w = ui->label_error->width() +
            ui->centralwidget->layout()->margin() * 2;
    }
    else
    {
        ui->textEdit_details->setVisible(true);
        h = ui->label_error->height() +
            ui->pushButton_details->height() +
            ui->textEdit_details->height() +
            ui->centralwidget->layout()->margin() * 4;
        w = ui->textEdit_details->width() +
            ui->centralwidget->layout()->margin() * 2;
    }
    this->setGeometry(this->x(), this->y(), w, h);
}
