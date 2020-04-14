/**
 * @file settings.cpp
 * @brief Définition des fonctions de la classe Settings
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "settings.hpp"
#include "parser.hpp"
#include "logger.hpp"
#include <QFile>
#include <QTextStream>

Settings* Settings::m_instance = nullptr;

/**
 * @return Un pointeur vers l'unique instance de la classe Settings.
 *
 * Permet d'obtenir un pointeur vers l'instance Settings.@n
 * Si aucune instance de Settings n'a été créée, la créée.
 * Dans tout les cas, cette fonction renvoie un pointeur vers cette instance.
 */
Settings* Settings::Instance()
{
    if(!m_instance)
        m_instance = new Settings();
    return m_instance;
}

/**
 * Constructeur de la classe Settings.@n
 * Appelle la fonction d'initialisation Settings::init.
 */
Settings::Settings()
{
    logger(__PRETTY_FUNCTION__);
    init();
}

/**
 * Initialise l'instance de la classe Settings.@n
 * L'initialisation se fait par la lecture des différents fichiers de configuration :
 * @li #SETTINGS_FILE
 * @li #COLORS_FILE
 * @li #COMPILER_FILE
 */
void Settings::init()
{
    load();
    init_color();
    init_compiler_options();
}

/**
 * Enregistre les données dans le fichiers des options. @n
 * Cette fonction est appelée depuis la fenêtre SettingsWindow.
 * Les données suivante sont enregistrées dans le fichier #SETTINGS_FILE:
 * @li Settings::m_style
 * @li Settings::m_keep_size
 * @li Settings::m_doxygen_template_dir
 * @li Settings::m_clear_screen
 * @li Settings::m_color_normal
 * @li Settings::m_color_success
 * @li Settings::m_color_error
 * @li Settings::m_sources_extensions
 * @li Settings::m_headers_extensions
 */
void Settings::save()
{
    logger(__PRETTY_FUNCTION__);
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

/**
 * Charge les données du fichier #SETTINGS_FILE.@n
 * Les mots clés suivants sont utilisés pour obtenir des informations :
 * @li style
 * @li keep_size
 * @li doxygen_template_dir
 * @li clear_screen
 * @li color_normal
 * @li color_error
 * @li color_success
 * @li sources_ext
 * @li headers_ext
 *
 * Ces données sont ensuite visualisable depuis la fenêtre SettingsWindow.
 */
void Settings::load()
{
    logger(__PRETTY_FUNCTION__);
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
        parser->close();
    }
    else
    {
        throw(QString("Erreur, impossible d'ouvrir le fichier des options !"));
    }
}

/**
 * Créé le fichier d'options par défaut. @n
 * Initialise comme suit :
 * @li Settings::m_style = default
 * @li Settings::m_keep_size = true
 * @li Settings::m_doxygen_template_dir = doxygen_templates
 * @li Settings::m_clear_screen = true
 * @li Settings::m_color_normal = Gold
 * @li Settings::m_color_success = Lime
 * @li Settings::m_color_error = Red
 * @li Settings::m_sources_extensions = c i ii cc cp cxx cpp CPP c++ C
 * @li Settings::m_headers_extensions = h hh H hp hxx hpp HPP h++ tcc
 */
void Settings::create()
{
    logger(__PRETTY_FUNCTION__);
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

/**
 * Initialise les couleurs dans la liste Settings::m_colors.@n
 * Cette liste est remplie par les informations du fichier #COLORS_FILE.@n
 * Ce fichier doit comporter des lignes de la forme &lt;coulor> &lt;red> &lt;green> &lt;blue>.@n
 * @c red @c green et @c blue doivent être des entiers entre 0 et 255.@n
 * Si une ligne du fichier est incorrecte, une exception est levée.
 */
void Settings::init_color()
{
    logger(__PRETTY_FUNCTION__);
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
                if(ok_b && ok_g && ok_r &&
                   red >= 0 && red < 256 &&
                   green >= 0 && green < 256 &&
                   blue >= 0 && blue < 256)
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
    else
    {
        throw(QString("Erreur : fichier " + COLORS_FILE + " impossible à lire."));
    }
}

/**
 * Initialise les options possibles du compilateur.@n
 * Cette liste est remplie par les informations du fichier #COMPILER_FILE.@n
 * Ce fichier doit comporter des sections. Une section est identifiée par un
 * nom de section reconnu suivant les macros suivantes :
 * @li #COMPILE_OVERALL pour les options générales
 * @li #COMPILE_LANGUAGE_C pour les options de langage C
 * @li #COMPILE_LANGUAGE_CXX pour les options de langage C++
 * @li #COMPILE_DIAGNOSTIC pour les options de diagnostique
 * @li #COMPILE_WARNINGS pour les options des warnings
 * @li #COMPILE_DEBUG pour les options de debug
 * @li #COMPILE_OPTI pour les options d'optimisation
 * @li #COMPILE_INSTRU pour les options d'instrumentation
 * @li #COMPILE_PREPROCESSOR pour les options du préprocesseur
 * @li #COMPILE_ASSEMBLER pour les options de l'assembleur
 * @li #COMPILE_LINKER pour les options du linker
 * @li #COMPILE_DIRS pour les options des dossiers
 * @li #COMPILE_CODE_CONV pour les options de convention de code
 *
 * Dans une section, on fait apparaître les options de la forme suivante :
 * &lt;option>;&lt;description brève>;&lt;tooltip>. A noter que la @c description
 * @c brève et le @c tooltip sont optionnels. En revanche, il faut garder les
 * deux caractères séparateur ";" dans tous les cas.@n@n
 * Voir : @ref KW_COMPILE.
 */
void Settings::init_compiler_options()
{
    logger(__PRETTY_FUNCTION__);
    QStringList kw = QStringList() << COMPILE_OVERALL
                                   << COMPILE_LANGUAGE_C
                                   << COMPILE_LANGUAGE_CXX
                                   << COMPILE_DIAGNOSTIC
                                   << COMPILE_WARNINGS
                                   << COMPILE_DEBUG
                                   << COMPILE_OPTI
                                   << COMPILE_INSTRU
                                   << COMPILE_PREPROCESSOR
                                   << COMPILE_ASSEMBLER
                                   << COMPILE_LINKER
                                   << COMPILE_DIRS
                                   << COMPILE_CODE_CONV;

    QFile file(COMPILER_FILE);
    if(file.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        QString text = file.readAll();
        QStringList ligns = text.split(QChar('\n'));
        QString current_kw = "";
        QString lign;
        QStringList option;

        for(int i = 0; i < ligns.length(); i++)
        {
            lign = ligns[i].simplified();
            if(ligns[i].simplified() != "")
            {
                if(ligns.contains(lign))
                {
                    current_kw = lign;
                }
                else
                {
                    option = lign.split(QChar(';'));
                    if(option.length() == 3)
                    {
                        add_compiler_option(current_kw, option[0], option[1], option[2]);
                    }
                    else
                    {
                        throw(QString("Erreur : fichier " + COMPILER_FILE + " corrompu ligne " + QString::number(i)));
                    }
                }
            }
        }
    }
    else
    {
        throw(QString("Erreur : fichier " + COMPILER_FILE + " impossible à lire."));
    }
}

/**
 * @param name Nom de la couleur à ajouter
 * @param red Composante rouge de la couleur à ajouter (entre 0 et 255)
 * @param green Composante verte de la couleur à ajouter (entre 0 et 255)
 * @param blue Composante bleue de la couleur à ajouter (entre 0 et 255)
 *
 * Créé un objet de type Color et l'ajoute à la liste Settings::m_colors.
 */
void Settings::add_color(QString name, int red, int green, int blue)
{
    logger("    add_color " + name);
    Color color;
    color.name = name;
    color.red = red;
    color.green = green;
    color.blue = blue;
    m_colors.append(color);
}

/**
 * @param key_word Mot clé de la section
 * @param option Option à ajouter
 * @param brief Description brève de l'option
 * @param tooltip Description complète de l'option
 *
 * Créé un objet de type CompilerOption et l'ajoute à la liste correspondant au mot clé @c key_word.@n@n
 * Voir : @ref KW_COMPILE.
 */
void Settings::add_compiler_option(QString key_word, QString option, QString brief, QString tooltip)
{
    logger("    add_flag " + key_word + " | " + option);
    CompilerOption comp;
    comp.option = option;
    comp.brief = brief;
    comp.tooltip = tooltip;
    if(key_word == COMPILE_OVERALL)
    {
        m_overall_options.append(comp);
    }
    else if(key_word == COMPILE_LANGUAGE_C)
    {
        m_language_c_options.append(comp);
    }
    else if(key_word == COMPILE_LANGUAGE_CXX)
    {
        m_language_cxx_options.append(comp);
    }
    else if(key_word == COMPILE_DIAGNOSTIC)
    {
        m_diagnostic_options.append(comp);
    }
    else if(key_word == COMPILE_WARNINGS)
    {
        m_warnings_options.append(comp);
    }
    else if(key_word == COMPILE_DEBUG)
    {
        m_debug_options.append(comp);
    }
    else if(key_word == COMPILE_OPTI)
    {
        m_opti_options.append(comp);
    }
    else if(key_word == COMPILE_INSTRU)
    {
        m_instru_options.append(comp);
    }
    else if(key_word == COMPILE_PREPROCESSOR)
    {
        m_preprocessor_options.append(comp);
    }
    else if(key_word == COMPILE_ASSEMBLER)
    {
        m_assembler_options.append(comp);
    }
    else if(key_word == COMPILE_LINKER)
    {
        m_linker_options.append(comp);
    }
    else if(key_word == COMPILE_DIRS)
    {
        m_dirs_options.append(comp);
    }
    else if(key_word == COMPILE_CODE_CONV)
    {
        m_code_conv_options.append(comp);
    }
    else
    {
        throw(QString("Erreur de paramètre pour l'ajout d'option de compilateur."));
    }
}
