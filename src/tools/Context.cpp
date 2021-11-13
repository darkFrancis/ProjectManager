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

#define PROJECTMANAGER_DIR ".projectmanager" /**< Nom du dossier caché de projet. */
#define PROJECT_FILE "project.list" /**< Nom du fichier contenant la liste des sous-projets du projet. */
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
 * Charge la liste des fichiers de sous-projets du projet.
 * @sa #PROJECT_FILE.
 */
void Context::loadSubProjects()
{
    QFile f(fileInProjectDir(PROJECT_FILE));
    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream s(&f);
        s.setCodec("UTF-8");
        QStringList lines = s.readAll().split('\n');
        f.close();

        m_subProjectList.clear();
        for(const QString& line : lines)
        {
            if(line.trimmed() != "")
            {
                int idx = line.indexOf('\t');
                QDir projectDir = QDir(qCtx->projectDir());
                if( idx >= 0)
                {
                    QString projectName = projectDir.absoluteFilePath(line.left(idx).trimmed());
                    QString description = line.mid(idx).trimmed();
                    m_subProjectList[qCtx->pathFromProject(projectName)] = description;
                }
                else
                {
                    QString projectName = projectDir.absoluteFilePath(line.trimmed());
                    m_subProjectList[qCtx->pathFromProject(projectName)] = "";
                }
            }
        }
    }
}

/**
 * @brief Context::saveSubProjects
 * @return @li @b false en cas d'erreur
 *         @li @b true sinon
 *
 * Enregistre la liste des sous-projets.
 * @sa #PROJECT_FILE.
 */
bool Context::saveSubProjects() const
{
    QFile f(fileInProjectDir(PROJECT_FILE));
    if(f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream s(&f);
        s.setCodec("UTF-8");
        for(const QString& pro : m_subProjectList.keys())
        {
             s << pro
               << (m_subProjectList[pro].trimmed() == "" ? "" : '\t' + m_subProjectList[pro])
               << endl;
        }
        f.close();
        return true;
    }
    return false;
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
 * @param val Nom du projet à ajouter
 *
 * Ajoute le projet à la liste des sous-projets sans doublon.
 * @sa #m_subProjectList.
 */
void Context::addSubProject(const QString& val)
{
    m_subProjectList[val] = "";
}

/**
 * @param project Nom de projet auquel on souhaite ajouter une description
 * @param description Description du projet
 */
void Context::setProjectDescription(const QString& project, const QString& description)
{
    if(m_subProjectList.contains(project))
    {
        m_subProjectList[project] = description;
    }
}

/**
 * @param val Nom du sous-projet à supprimer
 * @return @li @b true si le sous-projets était effectivement présent
 *         @li @b false sinon
 *
 * Supprime le sous-projet de la liste.
 * @sa #m_subProjectList.
 */
bool Context::removeSubProject(const QString& val)
{
    if(m_subProjectList.contains(val))
    {
        return m_subProjectList.remove(val) > 0;
    }
    return false;
}

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
 * @return #m_subProjectList
 */
QStringList Context::subProjects() const { return m_subProjectList.keys(); }

/**
 * @param project Projet recherché
 * @return Description du projet
 */
QString Context::projectDescription(const QString& project) const
{
    return m_subProjectList.value(project, "");
}

/**
 * @return #PROJECTMANAGER_DIR
 */
QString Context::projectHiddenDirName() const { return PROJECTMANAGER_DIR; }

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
    return QDir(QDir(m_projectDir).absoluteFilePath(PROJECTMANAGER_DIR)).absoluteFilePath(file);
}
