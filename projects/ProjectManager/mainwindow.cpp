/**
 * @file mainwindow.cpp
 * @brief Définition des fonctions de la classe MainWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QProcess>

#include "parser.hpp"
#include "context.hpp"
#include "newproject.hpp"
#include "settings/settingswindow.hpp"
#include "settings/settings.hpp"
#include "settings/logger.hpp"

/**
 * @param parent Le QWidget parent de cette fenêtre
 *
 * Contructeur de la classe MainWindow.@n
 * Ce constructeur hérite de celui de QMainWindow et utilise le système des fichiers
 * d'interface utilisateur.@n
 * Ce constructeur va appeler la fonction MainWindow::initApp pour s'initialiser. En
 * cas d'erreur lors de cette initialisation, affiche un message d'erreur pour
 * l'utilisateur à la fois dans la barre de status en bas de la fenêtre mais aussi
 * par une popup.@n
 * Voir Ui.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    logger(__PRETTY_FUNCTION__);

    this->setWindowTitle("Project Manager");
    try
    {
        initApp();
        status("Initialisation terminée avec succès", STATUS_DEFAULT_TIMEOUT);
    }
    catch(QString msg)
    {
        status(msg);
        QMessageBox::critical(this,
                              QString("Erreur"),
                              msg);
    }
}

/**
 * Destructeur de la classe MainWindow.@n
 * Appel la fonction MainWindow::saveInit pour enregistrer l'état de la fenêtre.
 */
MainWindow::~MainWindow()
{
    logger(__PRETTY_FUNCTION__);
    saveInit();
    delete ui;
}

/**
 * Fonction d'initialisation de la fenêtre.@n
 * Cette fenêtre étant la fenêtre principale, c'est ici que sont initialisées les
 * instances de ce programme dans cet ordre:
 * @li Initialisation de l'instance Setting avec l'appel Setting::init
 * @li Si le fichier #INIT_FILE n'éxiste pas, l'initialise en appelant la fonction
 * MainWindow::createInit
 * @li Lecture du fichier #INIT_FILE pour mettre en forme cette fenêtre et pour
 * renseigner les variables Context::m_project_file et Context::m_last_search
 * @li Créé et ajoute les différents onglets issus de la classe Tab
 * @li Si un projet a été renseigné lors de cette initialisation par le fichier
 * #INIT_FILE, le charge avec la fonction MainWindow::loadProject, sinon, rend
 * innaccessible au clic de l'utilisateur
 */
void MainWindow::initApp()
{
    logger(__PRETTY_FUNCTION__);
    Settings::Instance()->init();
    QDir::setCurrent(qApp->applicationDirPath());
    if(!QFile::exists(INIT_FILE))
    {
        status("Génaration du fichier d'initialisation", STATUS_DEFAULT_TIMEOUT);
        createInit();
    }
    Parser* parser = Parser::Instance();
    if(parser->load(INIT_FILE))
    {
        // Init Window
        bool ok = true;
        int x = parser->get("x").toInt(&ok);if(!ok) x = INIT_X;
        int y = parser->get("y").toInt(&ok);if(!ok) y = INIT_Y;
        int w = parser->get("width").toInt(&ok);if(!ok) w = INIT_W;
        int h = parser->get("height").toInt(&ok);if(!ok) h = INIT_H;
        this->setGeometry(x, y, w, h);

        // Init Context
        Context* ctx = Context::Instance();
        ctx->setProjectFile(parser->get("project"));
        ctx->setLastSearch(parser->get("last_search"));

        parser->close();
    }
    else
    {
        throw(QString("Erreur, impossible d'ouvrir le fichier d'initialisation"));
    }

    // Init Tab Widget
    m_tabWidget = new QTabWidget(this);
    Tab *tab_project = new TabProject();
    m_tabWidget->addTab(tab_project, "Configuration du projet");
    m_tablist.append(tab_project);
    Tab *tab_doxygen = new TabDoxygen();
    m_tabWidget->addTab(tab_doxygen, "Configuration Doxygen");
    m_tablist.append(tab_doxygen);
    Tab *tab_compiler = new TabCompiler();
    m_tabWidget->addTab(tab_compiler, "Configuration du compilateur");
    m_tablist.append(tab_compiler);
    Tab *tab_git = new TabGit();
    m_tabWidget->addTab(tab_git, "Git");
    m_tablist.append(tab_git);
    ui->centralWidget->layout()->addWidget(m_tabWidget);

    // Last Session
    if(QFile::exists(Context::Instance()->projectFile()))
    {
        try
        {
            loadProject();
        }
        catch (QString msg)
        {
            QMessageBox::critical(this,
                                  QString("Erreur"),
                                  msg);
        }
    }
    else
    {
        m_tabWidget->setEnabled(false);
    }
}

/**
 * Fonction de nettoyage générale.@n
 * Appel les fonctions de nettoyage de chaque onglet.@n
 * Voir Tab::clean.
 */
void MainWindow::clean()
{
    logger(__PRETTY_FUNCTION__);
    for(int i = 0; i < m_tablist.length(); i++)
    {
        m_tablist[i]->clean();
    }
}

/**
 * Fonction d'initialisation générale.@n
 * Appel les fonctions d'initialisation de chaque onglet puis
 * les rend accessible au clic.@n
 * Voir Tab::init.
 */
void MainWindow::init()
{
    logger(__PRETTY_FUNCTION__);
    for(int i = 0; i < m_tablist.length(); i++)
    {
        m_tablist[i]->init();
    }
    m_tabWidget->setEnabled(true);
}

/**
 * Fonction d'enregistrement générale.@n
 * Appel les fonctions d'enregistrement de chaque onglet.@n
 * Voir Tab::save.
 */
void MainWindow::save()
{
    logger(__PRETTY_FUNCTION__);
    for(int i = 0; i < m_tablist.length(); i++)
    {
        m_tablist[0]->save();
    }
}

/**
 * Fonction de génération du fichier d'initialisation.@n
 * Génère un fichier d'initialisation #INIT_FILE avec des paramètres par défaut :
 * @li x = #INIT_X
 * @li y = #INIT_Y
 * @li width = #INIT_W
 * @li height = #INIT_H
 * @li project = @e vide
 * @li last_search = @e vide
 */
void MainWindow::createInit()
{
    logger(__PRETTY_FUNCTION__);
    QDir::setCurrent(qApp->applicationDirPath());
    QFile file(INIT_FILE);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        // Window
        stream << "# Window" << endl;
        stream << "x=" << INIT_X << endl;
        stream << "y=" << INIT_Y << endl;
        stream << "width=" << INIT_W << endl;
        stream << "height=" << INIT_H << endl;
        stream << endl;
        // Project
        stream << "# Project" << endl;
        stream << "project=" << endl;
        stream << endl;
        // Last
        stream << "# Last" << endl;
        stream << "last_search=" << endl;
        file.close();
    }
    else
    {
        throw(QString("Impossible de créer le fichier d'initialisation"));
    }
}

/**
 * Fonction d'enregistrement d'état.@n
 * Enregistre dans le fichier #INIT_FILE les paramètres d'utilisation en cours.
 * Utilise les fonctions native de la classe QMainWindow pour obtenir les valeurs
 * des caractéristiques de la fenêtre. Appel les fonctions GET de l'instance Context
 * pour obtenir le projet ouvert et la dernière recherche effectuée.@n
 * Voir @ref CONTEXT_GET.
 */
void MainWindow::saveInit()
{
    logger(__PRETTY_FUNCTION__);
    QDir::setCurrent(qApp->applicationDirPath());
    QFile file(INIT_FILE);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        // Window
        stream << "# Window" << endl;
        stream << "x=" << this->x() << endl;
        stream << "y=" << this->y() << endl;
        stream << "width=" << this->width() << endl;
        stream << "height=" << this->height() << endl;
        stream << endl;
        // Project
        stream << "# Project" << endl;
        stream << "project=" << Context::Instance()->projectFile() << endl;
        stream << endl;
        // Last
        stream << "# Last" << endl;
        stream << "last_search=" << Context::Instance()->lastSearch() << endl;
        file.close();
    }
    else
    {
        throw(QString("Impossible de sauvegarder le fichier d'initialisation"));
    }
}

/**
 * @param msg Message à afficher
 * @param timeout Timeout en secondes
 *
 * Affiche le message @c msg dans la barre de status en bas de la fenêtre principale
 * pendant @c timeout secondes. Si un autre message est affiché, celui-ci disparait.@n
 * Voir Ui.
 */
void MainWindow::status(QString msg, int timeout)
{
    logger(__PRETTY_FUNCTION__);
    ui->statusBar->showMessage(msg, timeout * 1000);
}

/**
 * Shortcut : @b Ctrl+N.@n
 * Action de création de nouveau projet.@n
 * Si un projet est déjà ouvert, demande à l'utilisateur de confirmer son action.
 * S'il confirme, une fenêtre NewProject est ouverte. Cette fenêtre bloque
 * les autres fenêtres de l'application tant qu'elle est présente pour forcer
 * l'utilisateur à finir la sélection (ou fermer cette même fenêtre).
 */
void MainWindow::on_actionNouveau_triggered()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    if(ctx->isOpen())
    {
        QMessageBox::StandardButton res;
        res = QMessageBox::question(this, "Attention", "Attention ! Si un nouveau fichier est ouvert, tout ce qui n'est pas enregistré sera supprimé.\nVoulez vous continuer ?");
        if(res != QMessageBox::Yes)
        {
            return;
        }
    }
    NewProject* p = new NewProject(this);
    connect(p, &NewProject::created, this, &MainWindow::loadProject);
    p->setAttribute(Qt::WA_QuitOnClose, false);
    p->setWindowModality(Qt::ApplicationModal);
    p->show();
}

/**
 * Fonction générale de chargement de projet.@n
 * Prépare l'IHM avec la fonction MainWindow::init, puis charge le projet
 * avec la fonction Context::loadProject, et enfin initialise l'IHM avec
 * la fonction MainWindow::init.
 */
void MainWindow::loadProject()
{
    logger(__PRETTY_FUNCTION__);
    try
    {
        clean();
        Context::Instance()->loadProject();
        init();
    }
    catch(QString msg)
    {
        QMessageBox::critical(this, "Erreur", msg);
    }
}

/**
 * Shortcut : @b Ctrl+O.@n
 * Action d'ouverture de projet.@n
 * Si un projet est déjà ouvert, demande à l'utilisateur de confirmer son action.
 * S'il confirme, une fenêtre de sélection de fichier projet est ouverte. Si un
 * fichier est sélectionné, le projet en cours en fermé puis le nouveau projet est
 * chargé avec la fonction MainWindow::loadProject.
 */
void MainWindow::on_actionOuvrir_triggered()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    if(ctx->isOpen())
    {
        QMessageBox::StandardButton res;
        res = QMessageBox::question(this, "Attention", "Attention ! Si un nouveau fichier est ouvert, tout ce qui n'est pas enregistré sera supprimé.\nVoulez vous continuer ?");
        if(res != QMessageBox::Yes)
        {
            return;
        }
    }
    QString file = QFileDialog::getOpenFileName(this,
                                                "Ouvrir",
                                                ctx->lastSearch(),
                                                "ProjectFile *." + FILE_EXTENSION);
    if(file != "")
    {
        QFileInfo info(file);
        ctx->setLastSearch(info.absoluteDir().absolutePath());
        ctx->close();
        loadProject();
    }
}

/**
 * Shortcut : @b Ctrl+S.@n
 * Action d'enregistrement de projet.@n
 * Appelle la fonction MainWindow::save.
 */
void MainWindow::on_actionEnregistrer_triggered()
{
    logger(__PRETTY_FUNCTION__);
    save();
}

/**
 * Action de fermeture de projet.@n
 * Si un projet est déjà ouvert, demande à l'utilisateur de confirmer son action.
 * S'il confirme, les fenêtre sont nettoyées avec la fonction MainWindow::clean et
 * les onglets sont rendus innaccessible aux actions de l'utilisateur. La fonction
 * Context::close est appelée.
 */
void MainWindow::on_actionFermer_triggered()
{
    logger(__PRETTY_FUNCTION__);
    Context* ctx = Context::Instance();
    if(ctx->isOpen())
    {
        QMessageBox::StandardButton res;
        res = QMessageBox::question(this, "Attention", "Attention ! Si vous fermez ce fichier, tout ce qui n'est pas enregistré sera supprimé.\nVoulez vous continuer ?");
        if(res == QMessageBox::Yes)
        {
            clean();
            m_tabWidget->setEnabled(false);
            ctx->close();
        }
    }
}


/**
 * Shortcut : @b Ctrl+Q.@n
 * Action d'arrêt du programme.@n
 * Arrête le programme ProjectManager.
 */
void MainWindow::on_actionQuitter_triggered()
{
    logger(__PRETTY_FUNCTION__);
    qApp->quit();
}

/**
 * Action d'ouverture des options.@n
 * Ouvre une fenêtre SettingsWindow. Cette fenêtre bloque les autres fenêtres de
 * l'application tant qu'elle est présente pour forcer l'utilisateur à finir la
 * sélection (ou fermer cette même fenêtre).
 */
void MainWindow::on_actionOptions_triggered()
{
    logger(__PRETTY_FUNCTION__);
    SettingsWindow* w = new SettingsWindow(this);
    w->setAttribute(Qt::WA_QuitOnClose, false);
    w->setWindowModality(Qt::ApplicationModal);
    w->show();
}

/**
 * Action "A Propos".@n
 * Affiche les informations sur le projet ProjectManager.
 */
void MainWindow::on_actionA_propos_triggered()
{
    logger(__PRETTY_FUNCTION__);
    QMessageBox::about(this,
                       "A propos de ProjectManager",
                       QString("Version : ") + VERSION + "\n"
                       "Auteur : Dark Francis\n"
                       "Date de création : " + CREATE_DATE + "\n"
                       "Date de release : " + BUILD_DATE + "\n\n"
                       "Ce logiciel sert à la gestion de projets C/C++ "
                       "à l'aide des outils externe Doxygen et GitKraken.");
}

/**
 * Action "A Propos de Qt".@n
 * Affiche les informations sur l'API Qt.
 */
void MainWindow::on_actionA_propos_de_Qt_triggered()
{
    logger(__PRETTY_FUNCTION__);
    QMessageBox::aboutQt(this, "A propos de Qt");
}
