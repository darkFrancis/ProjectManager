/**
 * @file Context.cpp
 * @brief Definition de la classe Context
 * @author Dark Francis
 * @date 26/10/2020
 */
#include "Context.hpp"

#include <QFileInfo>
#include <QDir>
#include <QApplication>
#include <QTextStream>

#include "version.hpp"
#include "Logger.hpp"

#define PROJECTMANAGER_DIR ".projectmanager"
#define PROJECT_FILE "project.list"
#define INIT_FILE QDir(qApp->applicationDirPath()).absoluteFilePath(_APPLICATION_NAME_ + ".ini")

#define KW_LASTSEARCH   "last-search"
#define KW_LASTDIR      "last-dir"

Context* Context::m_instance = nullptr;

/**
 * Constructeur de la classe Context.@n
 * Initialise le contexte et rend accessible l'instance.@n
 * Voir #qCtx.
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
                m_subProjectList << QFileInfo(line).absoluteFilePath();
        }
    }
}

bool Context::saveSubProjects() const
{
    QFile f(fileInProjectDir(PROJECT_FILE));
    if(f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream s(&f);
        s.setCodec("UTF-8");
        for(const QString& pro : m_subProjectList)
        {
             s << pro << endl;
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

void Context::setProjectDir(const QString& dir) { m_projectDir = dir; }

void Context::addSubProject(const QString& val)
{
    m_subProjectList << val;
    m_subProjectList.removeDuplicates();
}

bool Context::removeSubProject(const QString& val)
{
    if(m_subProjectList.contains(val))
    {
        return m_subProjectList.removeAll(val) > 0;
    }
    return false;
}

/**
 * @return #m_lastSearch
 */
QString Context::lastSearch() const { return m_lastSearch; }

QString Context::projectDir() const { return m_projectDir; }

QString Context::doxyfile() const { return fileInProjectDir("Doxyfile"); }

QString Context::doxygenTemplateDir() const { return fileInProjectDir("doxygen-templates"); }

QStringList Context::subProjects() const { return m_subProjectList; }

QString Context::projectHiddenDirName() const { return PROJECTMANAGER_DIR; }

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

QString Context::fileInProjectDir(const QString file) const
{
    return QDir(QDir(m_projectDir).absoluteFilePath(PROJECTMANAGER_DIR)).absoluteFilePath(file);
}
