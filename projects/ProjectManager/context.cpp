#include "context.hpp"
#include "parser.hpp"

Context* Context::m_instance = nullptr;

Context* Context::Instance()
{
    if(!m_instance)
        m_instance = new Context();
    return m_instance;
}

Context::Context() :
    m_project_file(""),
    m_doxyfile("")
{
    m_open = false;
}

void Context::setProject(QString project_file)
{
    m_project_file = project_file;
}

void Context::setLastSearch(QString last_search)
{
    m_last_search = last_search;
}

void Context::loadProject()
{
    Parser* parser = Parser::Instance();
    if(parser->load(m_project_file))
    {
        parser->close();
        m_open = true;
    }
    else
    {
        throw(QString("Impossible de charger le fichier de projet"));
    }
}

QString Context::project()
{
    return m_project_file;
}

QString Context::lastSearch()
{
    return m_last_search;
}

QString Context::doxyfile()
{
    return m_doxyfile;
}

bool Context::isOpen()
{
    return m_open;
}
