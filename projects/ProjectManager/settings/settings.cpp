#include "settings.hpp"
#include "parser.hpp"
#include <QFile>
#include <QTextStream>

Settings* Settings::m_instance = nullptr;

Settings* Settings::Instance()
{
    if(!m_instance)
        m_instance = new Settings();
    return m_instance;
}

void Settings::save()
{
    QFile file(SETTINGS_FILE);
    if(file.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        stream << "style=" << m_style << endl;
        stream << "keep_size=" << (m_keep_size ? "true" : "false") << endl;
        stream << "doxygen_template_dir=" << m_doxygen_template_dir << endl;
        stream << "clear_screen=" << (m_clear_screen ? "true" : "false") << endl;
        file.close();
    }
    else
    {
        throw(QString("Erreur, impossible d'ouvrir le fichier des options !"));
    }
}

void Settings::load()
{
    Parser* parser = Parser::Instance();
    QFile file(SETTINGS_FILE);
    if(!file.exists())
    {
        create();
    }

    if(parser->load(SETTINGS_FILE))
    {
        m_style = parser->get("style");
        m_keep_size = (parser->get("keep_size") == QString("true"));
        m_doxygen_template_dir = parser->get("doxygen_template_dir");
        m_clear_screen = (parser->get("clear_screen") == QString("true"));
    }
    else
    {
        throw(QString("Erreur, impossible d'ouvrir le fichier des options !"));
    }
}

void Settings::create()
{
    QFile file(SETTINGS_FILE);
    if(file.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        stream << "style=default" << endl;
        stream << "keep_size=true" << endl;
        stream << "doxygen_template_dir=doxygen_templates" << endl;
        stream << "clear_screen=true" << endl;
        file.close();
    }
    else
    {
        throw(QString("Erreur, impossible d'ouvrir le fichier des options !"));
    }
}

void Settings::init_color()
{
    add_color("IndianRed", "#CD5C5C");
    add_color("LightCoral", "#F08080");
}

void Settings::add_color(QString name, QString hex_name)
{
    Color color;
    color.name = name;
    color.hex_name = hex_name;
    m_colors.append(color);
}
