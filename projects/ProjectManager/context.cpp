/**
 * @file context.cpp
 * @brief Définition des fonctions de la classe Context
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "context.hpp"
#include "parser.hpp"
#include "logger.hpp"
#include <QFileInfo>

Context* Context::m_instance = nullptr;

/**
 * @return Un pointeur vers l'unique instance de la classe Context.
 *
 * Permet d'obtenir un pointeur vers l'instance Context.@n
 * Si aucune instance de Context n'a été créée, la créée.
 * Dans tout les cas, cette fonction renvoie un pointeur vers cette instance.
 */
Context* Context::Instance()
{
    if(!m_instance)
        m_instance = new Context();
    return m_instance;
}

/**
 * Constructeur de la classe Context.@n
 * Initialise la varible Context::m_open à @c false.
 */
Context::Context()
{
    logger(__PRETTY_FUNCTION__);
    m_open = false;
}

/**
 * Fonction de chargement de projet.@n
 * Utilise l'instance Parser pour analyser le fichier Context::m_project_file
 * et récupérer les valeurs des différentes options présentes dans le fichier
 * de projet.@n
 * Voir @ref FILE, @ref PROJECT_FLAGS.
 */
void Context::loadProject()
{
    logger(__PRETTY_FUNCTION__);
    Parser* parser = Parser::Instance();
    if(parser->load(m_project_file))
    {
        m_project_name = parser->get(KW_PROJECT_NAME);
        m_project_type = parser->get(KW_PROJECT_TYPE);
        m_project_version = parser->get(KW_PROJECT_VESRION);
        m_project_desc = parser->get(KW_PROJECT_DESC);
        m_author = parser->get(KW_AUTHOR);
        m_build_dir = parser->get(KW_BUILD_DIR);
        m_output = parser->get(KW_OUTPUT);
        m_doxyfile = parser->get(KW_DOXYFILE);
        m_sources = parser->get(KW_SOURCES).split(' ');
        m_headers = parser->get(KW_HEADERS).split(' ');
        m_ressources = parser->get(KW_RESSOURCES).split(' ');
        m_defines = parser->get(KW_DEFINES).split(' ');
        m_include_path = parser->get(KW_INCLUDEPATH).split(' ');
        m_lib_link = parser->get(KW_LINKS).split(' ');
        m_compiler_flags = parser->get(KW_COMPILER_FLAGS).split(' ');
        m_cmd_pre_build = parser->get(KW_CMD_PRE_BUILD).split(';');
        m_cmd_post_build = parser->get(KW_CMD_POST_BUILD).split(';');
        m_cmd_extra_clean = parser->get(KW_CMD_EXTRA_CLEAN).split(';');
        parser->close();
        trimList(&m_sources);
        trimList(&m_headers);
        trimList(&m_ressources);
        trimList(&m_defines);
        trimList(&m_include_path);
        trimList(&m_lib_link);
        trimList(&m_compiler_flags);
        trimList(&m_cmd_pre_build);
        trimList(&m_cmd_post_build);
        trimList(&m_cmd_extra_clean);
        m_open = true;
    }
    else
    {
        throw(QString("Impossible de charger le fichier de projet"));
    }
}

/**
 * Fonction d'enregistrement de projet.@n
 * Enregistre les différentes options renseignées par l'utilisateur en s'aidant
 * des fonctions Context::save_description et Context::save_sources.@n
 * Voir @ref FILE, @ref PROJECT_FLAGS.
 */
void Context::save()
{
    logger(__PRETTY_FUNCTION__);
    QFile file(m_project_file);
    if(file.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        stream << "# Fichier de configuration de projet" << endl
               << "# Produit automatiquement par ProjectManager" << endl
               << endl
               << "# Projet " << m_project_name << endl
               << KW_PROJECT_NAME << "=" << m_project_name << endl
               << KW_PROJECT_TYPE << "=" << m_project_type << endl
               << KW_AUTHOR << "=" << m_author << endl
               << KW_PROJECT_VESRION << "=" << m_project_version << endl;
        save_description(&stream);
        stream << endl;

        stream << "# Gestion Doxygen" << endl
               << KW_DOXYFILE << "=" << m_doxyfile << endl
               << endl;

        stream << "# Gestion de sortie du compilateur" << endl
               << KW_BUILD_DIR << "=" << m_build_dir << endl
               << KW_OUTPUT << "=" << m_output << endl
               << endl;

        stream << "# FLAGS pour compilateur GCC" << endl;
        save_flags(KW_DEFINES, &stream);
        save_flags(KW_INCLUDEPATH, &stream);
        save_flags(KW_LINKS, &stream);
        save_flags(KW_COMPILER_FLAGS, &stream);
        stream << endl;

        stream << "# Commandes spéciales" << endl;
        save_cmd(KW_CMD_PRE_BUILD, &stream);
        save_cmd(KW_CMD_POST_BUILD, &stream);
        save_cmd(KW_CMD_EXTRA_CLEAN, &stream);
        stream << endl;

        stream << "# Fichiers" << endl;
        save_sources(KW_SOURCES, &stream);
        save_sources(KW_HEADERS, &stream);
        save_sources(KW_RESSOURCES, &stream);
    }
}

/**
 * @param stream Flux vers le fichier pour enregistrement
 *
 * Fonction d'enregistrement de la description de projet.@n
 * Enregistre la description du projet grâce au flux @c stream passé en
 * argument. Des retour à la ligne sont effectués pour éviter que cette
 * description ne dépasse #DESC_WIDTH caractères de large. Chaque retour
 * à la ligne est précédé d'un espace et du caractère '\' pour que le
 * Parser puisse l'analyser au prochain chargement du projet.@n
 * Voir @ref FILE, @ref PROJECT_FLAGS.
 */
void Context::save_description(QTextStream *stream)
{
    logger(__PRETTY_FUNCTION__);
    *stream << KW_PROJECT_DESC << "=";
    int idx;
    QString desc = m_project_desc.simplified();
    while(desc.length() > 0)
    {
        if(desc.length() <= DESC_WIDTH)
        {
            *stream << desc << endl;
            desc = "";
        }
        else
        {
            idx = desc.left(DESC_WIDTH).lastIndexOf(' ');
            if(idx > -1)
            {
                *stream << desc.left(idx) << " \\" << endl << INDENT_SPACES;
                desc = desc.right(desc.length() - idx).simplified();
            }
            else
            {
                *stream << desc << endl;
                desc = "";
            }
        }
    }
}

/**
 * @param kw Mot clé du type de source
 * @param stream Flux vers le fichier pour enregistrement
 *
 * Fonction d'enregistrement des sources.@n
 * Enregistre la liste de sources du type @c kw passé en argument avec
 * un seul fichier par ligne. Chaque retour à la ligne est précédé d'un
 * espace et du caractère '\' pour que le Parser puisse l'analyser au
 * prochain chargement du projet.@n
 * Voir @ref FILE, @ref PROJECT_FLAGS.
 */
void Context::save_sources(QString kw, QTextStream* stream)
{
    logger(__PRETTY_FUNCTION__);
    QStringList* tmp_list;
    if(kw == KW_SOURCES) tmp_list = &m_sources;
    else if(kw == KW_HEADERS) tmp_list = &m_headers;
    else /* KW_RESSOURCES */ tmp_list = &m_ressources;

    trimList(tmp_list);
    tmp_list->sort();
    if(tmp_list->length() > 0)
    {
        *stream << kw << " = " << tmp_list->first();
        for(int i = 1; i < tmp_list->length(); i++)
        {
            *stream << " \\" << endl << INDENT_SPACES << tmp_list->at(i);
        }
        *stream << endl << endl;
    }
}

/**
 * @param kw Mot clé de l'option de compilateur
 * @param stream Flux vers le fichier pour enregistrement
 *
 * Fonction d'enregistrement des options de compilation.@n
 * Enregistre la liste d'options de compilation du type @c kw passé en
 * argument avec une seule option par ligne. Chaque retour à la ligne
 * est précédé d'un espace et du caractère '\' pour que le Parser puisse
 * l'analyser au prochain chargement du projet.@n
 * Voir @ref FILE, @ref PROJECT_FLAGS.
 */
void Context::save_flags(QString kw, QTextStream* stream)
{
    logger(__PRETTY_FUNCTION__);
    QStringList* tmp_list;
    if(kw == KW_DEFINES) tmp_list = &m_defines;
    else if(kw == KW_INCLUDEPATH) tmp_list = &m_include_path;
    else if(kw == KW_LINKS) tmp_list = &m_lib_link;
    else /* KW_COMPILER_FLAGS */ tmp_list = &m_compiler_flags;

    trimList(tmp_list);
    if(tmp_list->length() > 0)
    {
        *stream << kw << " = " << tmp_list->first();
        for(int i = 1; i < tmp_list->length(); i++)
        {
            if(tmp_list->at(i).length() > 0 &&
               tmp_list->at(i).at(0) == QChar('-'))
            {
                *stream << " \\" << endl << INDENT_SPACES << tmp_list->at(i);
            }
            else
            {
                *stream << " " << tmp_list->at(i);
            }
        }
        *stream << endl;
    }
}

void Context::save_cmd(QString kw, QTextStream *stream)
{
    logger(__PRETTY_FUNCTION__);
    QStringList* tmp_list;
    if(kw == KW_CMD_PRE_BUILD) tmp_list = &m_cmd_pre_build;
    else if(kw == KW_CMD_POST_BUILD) tmp_list = &m_cmd_post_build;
    else /* KW_CMD_EXTRA_CLEAN */ tmp_list = &m_cmd_extra_clean;

    trimList(tmp_list);
    if(tmp_list->length() > 0)
    {
        *stream << kw << " = " << tmp_list->first();
        for(QString cmd : *tmp_list)
        {
            *stream << "; \\" << endl << cmd;
        }
        *stream << endl;
    }
}

/**
 * @param absolute_path Chemin absolu d'un fichier/dossier
 * @param ref_dir Répertoire de référence
 * @return Chemin relatif
 *
 * Permet d'obtenir le chemin relatif d'un fichier/dossier de chemin absolu
 * @c absolute_path par rapport à un répertoire de référence @c ref_dir.
 * Des caractères ".." peuvent apparaitre lors de ce processus.
 * @warning Sur un système de type Windows, des chemins sur des disques
 * différents ne fonctionneront pas.
 */
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

/**
 * @param relative_path Chemin relatif vers un fichier/dossier
 * @param ref_dir Répertoire de référence pour le chemin relatif
 * @return Chemin absolu
 *
 * Permet d'obtenir le chemin absolu d'un fichier/dossier de chemin @c relative_path
 * par rapport au dossier @c ref_dir.
 */
QString absolutePath(QString relative_path, QString ref_dir)
{
    if(ref_dir.at(ref_dir.length()-1) != QChar('/'))
    {
        ref_dir.append('/');
    }
    QFileInfo info(ref_dir + relative_path);
    return info.absoluteFilePath();
}

/**
 * @param type Le type de projet
 * @return Label correspondant à @c type
 *
 * Permet d'obtenir le label pour un type de projet donné. Si @c type n'est
 * pas un type de projet valide, renvoi une chaine de caractères QString vide.@n
 * Voir @ref PROJECT_TYPE.
 */
QString type2label(QString type)
{
    if(type == TYPE_C) return LABEL_C;
    else if(type == TYPE_CXX) return LABEL_CXX;
    else if(type == TYPE_LIBC) return LABEL_LIBC;
    else if(type == TYPE_LIBCXX) return LABEL_LIBCXX;
    else if(type == TYPE_SHAREDC) return LABEL_SHAREDC;
    else if(type == TYPE_SHAREDCXX) return LABEL_SHAREDCXX;
    else return "";
}

/**
 * @param label Le label du type de projet
 * @return Type correspondant à @c label
 *
 * Permet d'obtenir le type de projet pour un label donné. Si @c label n'est
 * pas un label de projet valide, renvoi une chaine de caractères QString vide.@n
 * Voir @ref PROJECT_TYPE.
 */
QString label2type(QString label)
{
    logger(__PRETTY_FUNCTION__);
    if(label == LABEL_C) return TYPE_C;
    else if(label == LABEL_CXX) return TYPE_CXX;
    else if(label == LABEL_LIBC) return TYPE_LIBC;
    else if(label == LABEL_LIBCXX) return TYPE_LIBCXX;
    else if(label == LABEL_SHAREDC) return TYPE_SHAREDC;
    else if(label == LABEL_SHAREDCXX) return TYPE_SHAREDCXX;
    else return "";
}

/**
 * @param combo Liste déroulante à initialiser
 *
 * Initialise la liste déroulante @c combo en ajoutant les labels des types
 * possibles de projets.
 * @warning @c combo doit être vide
 *
 * Voir @ref PROJECT_TYPE.
 */
void initComboType(QComboBox* combo)
{
    combo->addItem(LABEL_C);
    combo->addItem(LABEL_CXX);
    combo->addItem(LABEL_LIBC);
    combo->addItem(LABEL_LIBCXX);
    combo->addItem(LABEL_SHAREDC);
    combo->addItem(LABEL_SHAREDCXX);
}

/**
 * @param list Liste à simplifier
 *
 * Retire tout élément vide (ou ne contenant que des espaces) de la liste @c list
 * passé en argument.
 */
void trimList(QStringList* list)
{
    for(int i = 0; i < list->length(); i++)
    {
        if(list->at(i).simplified() == "")
        {
            list->removeAt(i);
        }
    }
}
