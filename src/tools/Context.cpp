/**
 * @file Context.cpp
 * @brief Source du contexte d'utilisation
 * @author Dark Francis
 * @date 26/10/2020
 */
#include "tools/Context.hpp"

#include <QFileInfo>
#include <QDir>
#include <QApplication>
#include <QTextStream>

#include "version/version.hpp"
#include "Logger/Logger.hpp"

#define DOXYGEN_DIR ".doxygen" /**< Nom du dossier caché de projet. */
#define INIT_FILE QDir(qApp->applicationDirPath()).absoluteFilePath(_APPLICATION_NAME_ + ".ini") /**< Checmin vers le fichier d'initialisation de l'application. */

#define KW_LASTSEARCH   "last-search" /**< Mot clé du fichier d'initialisation pour la dernière recherche */
#define KW_LASTDIR      "last-dir" /**< Mot clé du fichier d'initialisation pour le dernier dossier de projet */

Context* Context::m_instance = nullptr;

/**
 * Constructeur de la classe Context.@n
 * Initialise le contexte et rend accessible l'instance.@n
 * @sa #qCtx.
 */
Context::Context()
{
    if(m_instance != nullptr)
    {
        throw "Une instance de Context éxiste déjà !";
    }
    init();
    m_instance = this;
}

/**
 * Destructeur de la classe Context.@n
 * Enregistre le contexte.
 */
Context::~Context()
{
    save();
}

/**
 * @return Pointeur vers l'instance de Context #m_instance
 */
Context* Context::Instance()
{
    return m_instance;
}

/**
 * @param val Nouvelle valeur de #m_lastSearch
 */
void Context::setLastSearch(const QString& val) { m_lastSearch = val; }

/**
 * @param dir Nouvelle valeur de #m_projectDir
 */
void Context::setProjectDir(const QString& dir) { m_projectDir = dir; }

/**
 * @return #m_lastSearch
 */
QString Context::lastSearch() const { return m_lastSearch; }

/**
 * @return #m_projectDir
 */
QString Context::projectDir() const { return m_projectDir; }

/**
 * @param absolutePath Chemin absolu
 * @return Chemin relatif par rapport au chemin du dossier projet en cours
 */
QString Context::pathFromProject(const QString& absolutePath) const
{
    return QDir(m_projectDir).relativeFilePath(absolutePath);
}

/**
 * @return Chemin vers le fichier Doxyfile du projet
 */
QString Context::doxyfile() const { return fileInProjectDir("Doxyfile"); }

/**
 * @return Chemin vers le dossier des templates Doxygen du projet
 */
QString Context::doxygenTemplateDir() const { return fileInProjectDir("doxygen-templates"); }

/**
 * @return #PROJECTMANAGER_DIR
 */
QString Context::projectHiddenDirName() const { return DOXYGEN_DIR; }

/**
 * Initialise le contexte en lisant le fichier INI de l'application.
 * @note Si le fichier n'existe pas, le créé avec la méthode save().
 * @sa #INIT_FILE, #KW_LASTSEARCH, #KW_LASTDIR.
 */
void Context::init()
{
    qLog->info("Initialisation du contexte");
    if(m_parser.loadIni(INIT_FILE))
    {
        InitGroup group = m_parser.get("");
        m_lastSearch = group.get(KW_LASTSEARCH);
        m_projectDir = group.get(KW_LASTDIR);
    }
    else
    {
        qLog->warning("Fichier INI non trouvé");
        qLog->info("Création du fichier INI par défaut");
        save();
    }
}

/**
 * Enregistre le contexte dans le fichier INI.
 * @sa #INIT_FILE, #KW_LASTSEARCH, #KW_LASTDIR.
 */
void Context::save()
{
    qLog->info("Enregistrement du fichier INI");
    m_parser.reset();
    InitGroup group;
    group.add(KW_LASTSEARCH, m_lastSearch);
    group.add(KW_LASTDIR, m_projectDir);
    m_parser.setGroup(group);
    if(m_parser.saveIni(INIT_FILE))
    {
        qLog->info("Fichier INI généré");
    }
    else
    {
        qLog->error("Impossible de générer le fichier INI !");
    }
}

/**
 * @param file Nom du fichier à trouver
 * @return Chemin absolu vers le fichier dans le dosier du projet.
 * @sa #PROJECTMANAGER_DIR.
 */
QString Context::fileInProjectDir(const QString file) const
{
    return QDir(QDir(m_projectDir).absoluteFilePath(DOXYGEN_DIR)).absoluteFilePath(file);
}
