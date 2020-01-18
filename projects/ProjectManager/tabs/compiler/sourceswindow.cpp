#include "sourceswindow.hpp"
#include "ui_sourceswindow.h"
#include <QFileDialog>
#include "context.hpp"
#include "settings/settings.hpp"

SourcesWindow::SourcesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SourcesWindow)
{
    ui->setupUi(this);

    connect(ui->listWidget_sources, &QListWidget::itemClicked, this, &SourcesWindow::setChecked);
    connect(ui->listWidget_headers, &QListWidget::itemClicked, this, &SourcesWindow::setChecked);
    connect(ui->listWidget_ressources, &QListWidget::itemClicked, this, &SourcesWindow::setChecked);
}

SourcesWindow::~SourcesWindow()
{
    delete ui;
}

QStringList SourcesWindow::getSources()
{
    QStringList source_list;
    for(int i = 0; i < ui->listWidget_sources->count(); i++)
    {
        source_list.append(ui->listWidget_sources->item(i)->text());
    }
    return source_list;
}

QStringList SourcesWindow::getHeaders()
{
    QStringList header_list;
    for(int i = 0; i < ui->listWidget_headers->count(); i++)
    {
        header_list.append(ui->listWidget_headers->item(i)->text());
    }
    return header_list;
}

QStringList SourcesWindow::getRessources()
{
    QStringList ressource_list;
    for(int i = 0; i < ui->listWidget_ressources->count(); i++)
    {
        ressource_list.append(ui->listWidget_ressources->item(i)->text());
    }
    return ressource_list;
}

void SourcesWindow::on_pushButton_add_clicked()
{
    QStringList file_list = QFileDialog::getOpenFileNames(this,
                                                          "Ajout de fichiers",
                                                          Context::Instance()->lastSearch());
    if(!file_list.isEmpty())
    {
        QFileInfo info(file_list[file_list.length()-1]);
        Context::Instance()->setLastSearch(info.absoluteDir().absolutePath());

        QString file_name;
        QString extension;
        QString file_path;
        int idx;
        for(int i = 0; i < file_list.length(); i++)
        {
            info.setFile(file_list[i]);
            info.refresh();
            file_name = info.fileName();

            // Get extension
            idx = file_name.lastIndexOf(QChar('.'));
            if(idx > -1)
            {
                extension = file_name.right(file_name.length() - idx - 1);
            }
            else
            {
                extension = "";
            }

            // Get file type
            if(isSource(extension))
            {
                addItem(file_list[i], ui->listWidget_sources);
            }
            else if(isHeader(extension))
            {
                addItem(file_list[i], ui->listWidget_headers);
            }
            else // Ressource
            {
                addItem(file_list[i], ui->listWidget_ressources);
            }
        }

        // Sort
        ui->listWidget_sources->sortItems();
        ui->listWidget_headers->sortItems();
        ui->listWidget_ressources->sortItems();
    }
}

void SourcesWindow::on_pushButton_remove_clicked()
{
    QList<QListWidgetItem*> rem_sources;
    QList<QListWidgetItem*> rem_headers;
    QList<QListWidgetItem*> rem_ressources;

    for(int i = 0; i < ui->listWidget_sources->count(); i++)
    {
        if(ui->listWidget_sources->item(i)->checkState() == Qt::Checked)
        {
            rem_sources.append(ui->listWidget_sources->item(i));
        }
    }
    for(int i = 0; i < ui->listWidget_headers->count(); i++)
    {
        if(ui->listWidget_headers->item(i)->checkState() == Qt::Checked)
        {
            rem_headers.append(ui->listWidget_headers->item(i));
        }
    }
    for(int i = 0; i < ui->listWidget_ressources->count(); i++)
    {
        if(ui->listWidget_ressources->item(i)->checkState() == Qt::Checked)
        {
            rem_ressources.append(ui->listWidget_ressources->item(i));
        }
    }

    for(int i = 0; i < rem_sources.length(); i++)
    {
        delete rem_sources[i];
    }
    for(int i = 0; i < rem_headers.length(); i++)
    {
        delete rem_headers[i];
    }
    for(int i = 0; i < rem_ressources.length(); i++)
    {
        delete rem_ressources[i];
    }
}

/**
 * @brief SourcesWindow::setChecked permet de définir l'état (coché/non coché) d'un item de la liste
 *
 * @li Si l'item est coché, le décoche
 * @li Sinon, le coche
 * @param item L'item à définir
 */
void SourcesWindow::setChecked(QListWidgetItem* item)
{
    if(item->checkState() == Qt::Checked)
    {
        item->setCheckState(Qt::Unchecked);
    }
    else
    {
        item->setCheckState(Qt::Checked);
    }
}

void SourcesWindow::addItem(QString text, QListWidget* widget)
{
    QListWidgetItem* item = new QListWidgetItem(text);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    widget->addItem(item);
}

/**
 * @brief SourcesWindow::isSource permet de savoir si un fichier est une source
 * @param extension Permet de spécifier l'extension du fichier
 * @return @li true si le fichier est un fichier source
 *         @li false sinon
 */
bool SourcesWindow::isSource(QString extension)
{
    return Settings::Instance()->sourcesExtensions().contains(extension);
}

/**
 * @brief SourcesWindow::isHeader permet de savoir si un fichier est un header
 * @param extension Permet de spécifier l'extension du fichier
 * @return @li true si le fichier est un fichier header
 *         @li false sinon
 */
bool SourcesWindow::isHeader(QString extension)
{
    return Settings::Instance()->headersExtensions().contains(extension);
}
