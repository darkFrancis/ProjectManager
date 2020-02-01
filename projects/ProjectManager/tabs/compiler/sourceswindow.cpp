/**
 * @file sourceswindow.cpp
 * @brief Définition de la classe SourcesWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "sourceswindow.hpp"
#include "ui_sourceswindow.h"
#include <QFileDialog>
#include "context.hpp"
#include "settings/settings.hpp"
#include "settings/logger.hpp"

/**
 * @param parent Le QWidget parent de cette fenêtre
 *
 * Contructeur de la classe ParamSelectionWindow.@n
 * Ce constructeur hérite de celui de QMainWindow et utilise le système des fichiers
 * d'interface utilisateur.@n
 * Cette fenêtre contient 3 listes pour contenir:
 * @li Les sources dont les extensions sont définies dans Settings::m_sources_extensions
 * @li Les headers dont les extensions sont définies dans Settings::m_headers_extensions
 * @li Les ressources qui sont tous les autres fichiers
 *
 * Ce constructeur va appeler la fonction SourcesWindow::init pour s'initialiser.
 * Voir Settings, Context, Ui.
 */
SourcesWindow::SourcesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SourcesWindow)
{
    ui->setupUi(this);

    logger(__PRETTY_FUNCTION__);
    init();
}

/**
 * Destructeur de la classe SourcesWindow
 */
SourcesWindow::~SourcesWindow()
{
    logger(__PRETTY_FUNCTION__);
    delete ui;
}

/**
 * Initialise la fenêtre.@n
 * Cette fonction utilise les méthodes GET de l'instance Context pour ajouter
 * les listes de fichiers dans la liste leur correspondant à l'aide de la fonction
 * SourcesWindow::addItem.@n
 * Voir @ref CONTEXT_GET, Ui.
 */
void SourcesWindow::init()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    for(QString path : ctx->sources()) addItem(path, ui->listWidget_sources);
    for(QString path : ctx->headers()) addItem(path, ui->listWidget_headers);
    for(QString path : ctx->ressources()) addItem(path, ui->listWidget_ressources);
}

/**
 * Enregistre les modifications apportées par l'utilisateur.@n
 * Cette fonction utilise les méthodes SET de l'instance Context pour enregistrer
 * les élément présent dans la fenêtre dans les liste des fichiers. Puis elle appelle
 * la fonction Context::save pour enregistrer les modification apportées dans le
 * fichier de projet.
 * Voir @ref CONTEXT_SET, @ref FILE, Ui.
 */
void SourcesWindow::save()
{
    Context* ctx = Context::Instance();
    ctx->setSources(getSources());
    ctx->setHeaders(getHeaders());
    ctx->setRessources(getRessources());
    ctx->save();
}

/**
 * @return Liste des sources
 *
 * Cette fonction renvoie une liste des chemins absolus vers les
 * fichiers des sources.
 */
QStringList SourcesWindow::getSources()
{
    logger(__PRETTY_FUNCTION__);
    QStringList source_list;
    for(int i = 0; i < ui->listWidget_sources->count(); i++)
    {
        source_list.append(ui->listWidget_sources->item(i)->text());
    }
    return source_list;
}

/**
 * @return Liste des headers
 *
 * Cette fonction renvoie une liste des chemins absolus vers les
 * fichiers des headers.
 */
QStringList SourcesWindow::getHeaders()
{
    logger(__PRETTY_FUNCTION__);
    QStringList header_list;
    for(int i = 0; i < ui->listWidget_headers->count(); i++)
    {
        header_list.append(ui->listWidget_headers->item(i)->text());
    }
    return header_list;
}

/**
 * @return Liste des ressources
 *
 * Cette fonction renvoie une liste des chemins absolus vers les
 * fichiers des ressources.
 */
QStringList SourcesWindow::getRessources()
{
    logger(__PRETTY_FUNCTION__);
    QStringList ressource_list;
    for(int i = 0; i < ui->listWidget_ressources->count(); i++)
    {
        ressource_list.append(ui->listWidget_ressources->item(i)->text());
    }
    return ressource_list;
}

/**
 * Ce connecteur s'active lors d'un clic sur le bouton Ajouter par l'utilisateur.@n
 * Dans ce cas, une fenêtre s'ouvre pour que l'utilisateur sélectionne des fichiers.
 * Ces fichiers sont ensuite séprés en 3 catégories : les sources, les headers et
 * les ressources selon leur extension de fichier (voir SourcesWindow::SourcesWindow).
 * La fonction SourcesWindow::save est ensuite appelée.
 */
void SourcesWindow::on_pushButton_add_clicked()
{
    logger(__PRETTY_FUNCTION__);
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
        save();
    }
}

/**
 * Ce connecteur s'active lors d'un clic sur le bouton Supprimer par l'utilisateur.@n
 * Dans ce cas, tous les items coché par l'utilisateur sont supprimés.
 * La fonction SourcesWindow::save est ensuite appelée.
 */
void SourcesWindow::on_pushButton_remove_clicked()
{
    logger(__PRETTY_FUNCTION__);
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
    save();
}

/**
 * @param text Texte de l'élément à ajouter à la liste
 * @param widget Liste dans laquelle ajouter l'élément
 *
 * Cette fonction ajoute un nouvel item comportant le texte @c text dans la
 * liste @c widget. Ce nouvel élément pourra être sélectionné par une case
 * cochable du côté gauche ou par double-clic. Il est par défaut non-coché.@n
 * Voir SourcesWindow::on_listWidget_sources_itemDoubleClicked
 * SourcesWindow::on_listWidget_headers_itemDoubleClicked
 * SourcesWindow::on_listWidget_ressources_itemDoubleClicked
 */
void SourcesWindow::addItem(QString text, QListWidget* widget)
{
    logger("    add_item " + text);
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

/**
 * @param item Item double-cliqué par l'utilisateur
 *
 * Ce connecteur est appelé lors du double-clic sur un item de la liste des sources.@n
 * Appel la fonction SourcesWindow::itemDoubleClicked pour la gestion de cet item.
 */
void SourcesWindow::on_listWidget_sources_itemDoubleClicked(QListWidgetItem *item)
{
    itemDoubleClicked(item);
}

/**
 * @param item Item double-cliqué par l'utilisateur
 *
 * Ce connecteur est appelé lors du double-clic sur un item de la liste des headers.@n
 * Appel la fonction SourcesWindow::itemDoubleClicked pour la gestion de cet item.
 */
void SourcesWindow::on_listWidget_headers_itemDoubleClicked(QListWidgetItem *item)
{
    itemDoubleClicked(item);
}

/**
 * @param item Item double-cliqué par l'utilisateur
 *
 * Ce connecteur est appelé lors du double-clic sur un item de la liste des ressources.@n
 * Appel la fonction SourcesWindow::itemDoubleClicked pour la gestion de cet item.
 */
void SourcesWindow::on_listWidget_ressources_itemDoubleClicked(QListWidgetItem *item)
{
    itemDoubleClicked(item);
}

/**
 * @param item Item double-cliqué par l'utilisateur
 *
 * L'item @c item change d'état entre coché et non-coché.
 */
void SourcesWindow::itemDoubleClicked(QListWidgetItem *item)
{
    if(item->checkState() == Qt::Checked)
    {
        logger("    item uncheked");
        item->setCheckState(Qt::Unchecked);
    }
    else
    {
        logger("    item cheked");
        item->setCheckState(Qt::Checked);
    }
}
