/**
 * @file Context.cpp
 * @brief Definition de la classe Context
 * @author Dark Francis
 * @date 26/10/2020
 */
#include "Context.hpp"
#include "version.hpp"
#include "Logger.hpp"

#define KW_GRP_LAST "last"
#define KW_GRP_DOXYGEN "doxygen"

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

/**
 * @param val Nouvelle valeur de #m_lastSearch
 */
void Context::setLastSearch(const QString& val) { m_lastSearch = val; }


void Context::setProjectFile(const QString& file) { m_projectFile = file; }

void Context::setDoxyFile(const QString& file) { m_doxyfile = file; }

void Context::setDoxygenTemplateDir(const QString& dir) { m_doxygenTemplateDir = dir; }

/**
 * @return #m_lastSearch
 */
QString Context::lastSearch() const { return m_lastSearch; }

QString Context::projectFile() const { return m_projectFile; }

QString Context::doxyfile() const { return m_doxyfile; }

QString Context::doxygenTemplateDir() const { return m_doxygenTemplateDir; }

void Context::init()
{
    qLog->info("Initialisation du contexte");
    if(m_parser.loadIni(_APPLICATION_NAME_ + ".ini"))
    {
        InitGroup lastGroup = m_parser.get(KW_GRP_LAST);
        InitGroup doxyGroup = m_parser.get(KW_GRP_DOXYGEN);
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
}
