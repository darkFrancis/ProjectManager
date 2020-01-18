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

void Context::loadProject()
{
    Parser* parser = Parser::Instance();
    if(parser->load(m_project_file))
    {
        m_project_name = parser->get(KW_PROJECT_NAME);
        m_project_type = parser->get(KW_PROJECT_TYPE);
        m_project_version = parser->get(KW_PROJECT_VESRION);
        m_project_desc = parser->get(KW_PROJECT_DESC);
        m_author = parser->get(KW_AUTHOR);
        m_git_path = parser->get(KW_GIT_PATH);
        m_doxyfile = parser->get(KW_DOXYFILE);
        m_sources = parser->get(KW_SOURCES).split(' ');
        m_headers = parser->get(KW_HEADERS).split(' ');
        m_ressources = parser->get(KW_RESSOURCES).split(' ');
        parser->close();
        m_open = true;
    }
    else
    {
        throw(QString("Impossible de charger le fichier de projet"));
    }
}

void Context::save()
{
    /**
      @todo
      */
}
