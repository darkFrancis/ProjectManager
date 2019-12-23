#include "context.hpp"

Context* Context::m_instance = nullptr;

Context* Context::Instance()
{
    if(!m_instance)
        m_instance = new Context();
    return m_instance;
}

Context::Context() :
    m_project_file("")
{}

void Context::setProject(QString project_file)
{
    m_project_file = project_file;
}

QString Context::project()
{
    return m_project_file;
}

QString Context::doxyfile()
{
    return m_doxyfile;
}
