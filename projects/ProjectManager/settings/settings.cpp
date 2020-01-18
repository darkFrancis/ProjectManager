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
        stream << "color_normal=" << m_color_normal << endl;
        stream << "color_success=" << m_color_success << endl;
        stream << "color_error=" << m_color_error << endl;
        stream << "sources_ext=" << m_sources_extensions.join(' ') << endl;
        stream << "headers_ext=" << m_headers_extensions.join(' ') << endl;
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
        m_color_normal = parser->get("color_normal");
        m_color_error = parser->get("color_error");
        m_color_success = parser->get("color_success");
        m_sources_extensions = parser->get("sources_ext").split(' ');
        m_headers_extensions = parser->get("headers_ext").split(' ');
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
        stream << "color_normal=Gold" << endl;
        stream << "color_success=Lime" << endl;
        stream << "color_error=Red" << endl;
        stream << "sources_ext=c i ii cc cp cxx cpp CPP c++ C" << endl;
        stream << "headers_ext=h hh H hp hxx hpp HPP h++ tcc" << endl;
        file.close();
    }
    else
    {
        throw(QString("Erreur, impossible d'ouvrir le fichier des options !"));
    }
}

void Settings::init_color()
{
    QFile color_file(COLORS_FILE);
    if(color_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int idx;
        int red;
        int green;
        int blue;
        bool ok_r = true;
        bool ok_g = true;
        bool ok_b = true;
        QString lign;
        QString text = color_file.readAll();
        QStringList ligns = text.split('\n');
        for(int i = 0; i < ligns.length(); i++)
        {
            QString lign = ligns[i];
            // Gestion commentaires ou ligne vide
            idx = lign.indexOf(QChar('#'));
            if(idx >= 0)
            {
                lign = lign.left(idx);
            }
            lign = lign.simplified();

            if(lign != QString(""))
            {
                QStringList data = lign.split(QChar(' '));
                if(data.length() != 4)
                {
                    throw(QString("Erreur : fichier " + COLORS_FILE + " corrompu ligne " + QString::number(i)));
                }
                red = data[1].toInt(&ok_r);
                green = data[2].toInt(&ok_g);
                blue = data[3].toInt(&ok_b);
                if(ok_b && ok_g && ok_r)
                {
                    add_color(data[0], red, green, blue);
                }
                else
                {
                    throw(QString("Erreur : fichier " + COLORS_FILE + " corrompu ligne " + QString::number(i)));
                }
            }
        }
    }
}

void Settings::add_color(QString name, int red, int green, int blue)
{
    Color color;
    color.name = name;
    color.red = red;
    color.green = green;
    color.blue = blue;
    m_colors.append(color);
}
