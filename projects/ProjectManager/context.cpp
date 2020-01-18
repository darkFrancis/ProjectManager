#include "context.hpp"
#include "parser.hpp"
#include <QFileInfo>

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

QString relativePath(QString absolute_path, QString ref_dir)
{
    QStringList ref_dirs = ref_dir.split('/');
    QStringList abs_dirs = absolute_path.split('/');
    // Remove empty
    while(ref_dirs.contains(""))
    {
        ref_dirs.removeAt(ref_dirs.indexOf(""));
    }
    while(abs_dirs.contains(""))
    {
        abs_dirs.removeAt(abs_dirs.indexOf(""));
    }

    // Remove same
    while(ref_dirs.length() > 0 &&
          abs_dirs.length() > 0 &&
          ref_dirs.first() == abs_dirs.first())
    {
        abs_dirs.removeFirst();
        ref_dirs.removeFirst();
    }
    // Add ..
    while(ref_dirs.length() > 0)
    {
        abs_dirs.prepend("..");
        ref_dirs.removeFirst();
    }
    return abs_dirs.join('/');
}

QString absolutePath(QString relative_path, QString ref_dir)
{
    if(ref_dir.at(ref_dir.length()-1) != QChar('/'))
    {
        ref_dir.append('/');
    }
    QFileInfo info(ref_dir + relative_path);
    return info.absoluteFilePath();
}
