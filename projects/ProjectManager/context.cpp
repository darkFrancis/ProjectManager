#include "context.hpp"
#include "parser.hpp"
#include "settings/logger.hpp"
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
    logger(__PRETTY_FUNCTION__);
    m_open = false;
}

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
        m_git_path = parser->get(KW_GIT_PATH);
        m_doxyfile = parser->get(KW_DOXYFILE);
        m_sources = parser->get(KW_SOURCES).split(' ');
        m_headers = parser->get(KW_HEADERS).split(' ');
        m_ressources = parser->get(KW_RESSOURCES).split(' ');
        m_flag_overall = parser->get(KW_FLAG_OVERALL).split(' ');
        m_flag_c = parser->get(KW_FLAG_LANGUAGE_C).split(' ');
        m_flag_cxx = parser->get(KW_FLAG_LANGUAGE_CXX).split(' ');
        m_flag_diag = parser->get(KW_FLAG_DIAGNOSTIC).split(' ');
        m_flag_warn = parser->get(KW_FLAG_WARNINGS).split(' ');
        m_flag_debug = parser->get(KW_FLAG_DEBUG).split(' ');
        m_flag_opt = parser->get(KW_FLAG_OPTI).split(' ');
        m_flag_inst = parser->get(KW_FLAG_INSTRU).split(' ');
        m_flag_preprocess = parser->get(KW_FLAG_PREPROCESSOR).split(' ');
        m_flag_assembler = parser->get(KW_FLAG_ASSEMBLER).split(' ');
        m_flag_linker = parser->get(KW_FLAG_LINKER).split(' ');
        m_flag_dirs = parser->get(KW_FLAG_DIRS).split(' ');
        m_flag_convention = parser->get(KW_FLAG_CODE_CONV).split(' ');
        m_flag_other = parser->get(KW_FLAG_OTHER).split(' ');
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

        stream << "# Gestion Git et Doxygen" << endl
               << KW_GIT_PATH << "=" << m_git_path << endl
               << KW_DOXYFILE << "=" << m_doxyfile << endl
               << endl;

        stream << "# Gestion de sortie du compilateur" << endl
               << KW_BUILD_DIR << "=" << m_build_dir << endl
               << KW_OUTPUT << "=" << m_output << endl
               << endl;

        stream << "# FLAGS pour compilateur GCC" << endl;
        save_flags(KW_FLAG_OVERALL, &stream);
        save_flags(KW_FLAG_LANGUAGE_C, &stream);
        save_flags(KW_FLAG_LANGUAGE_CXX, &stream);
        save_flags(KW_FLAG_DIAGNOSTIC, &stream);
        save_flags(KW_FLAG_WARNINGS, &stream);
        save_flags(KW_FLAG_DEBUG, &stream);
        save_flags(KW_FLAG_OPTI, &stream);
        save_flags(KW_FLAG_INSTRU, &stream);
        save_flags(KW_FLAG_PREPROCESSOR, &stream);
        save_flags(KW_FLAG_ASSEMBLER, &stream);
        save_flags(KW_FLAG_LINKER, &stream);
        save_flags(KW_FLAG_DIRS, &stream);
        save_flags(KW_FLAG_CODE_CONV, &stream);
        save_flags(KW_FLAG_OTHER, &stream);
    }
}

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
    *stream << endl;
}

void Context::save_sources(QString kw, QTextStream* stream)
{
    logger(__PRETTY_FUNCTION__);
    QStringList* tmp_list;
    if(kw == KW_SOURCES) tmp_list = &m_sources;
    else if(kw == KW_HEADERS) tmp_list = &m_headers;
    else tmp_list = &m_ressources;

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

void Context::save_flags(QString kw, QTextStream* stream)
{
    logger(__PRETTY_FUNCTION__);
    QStringList* tmp_list;
    if(kw == KW_FLAG_OVERALL) tmp_list = &m_flag_overall;
    else if(kw == KW_FLAG_LANGUAGE_C) tmp_list = &m_flag_c;
    else if(kw == KW_FLAG_LANGUAGE_CXX) tmp_list = &m_flag_cxx;
    else if(kw == KW_FLAG_DIAGNOSTIC) tmp_list = &m_flag_diag;
    else if(kw == KW_FLAG_WARNINGS) tmp_list = &m_flag_warn;
    else if(kw == KW_FLAG_DEBUG) tmp_list = &m_flag_debug;
    else if(kw == KW_FLAG_OPTI) tmp_list = &m_flag_opt;
    else if(kw == KW_FLAG_INSTRU) tmp_list = &m_flag_inst;
    else if(kw == KW_FLAG_PREPROCESSOR) tmp_list = &m_flag_preprocess;
    else if(kw == KW_FLAG_ASSEMBLER) tmp_list = &m_flag_assembler;
    else if(kw == KW_FLAG_LINKER) tmp_list = &m_flag_linker;
    else if(kw == KW_FLAG_DIRS) tmp_list = &m_flag_dirs;
    else if(kw == KW_FLAG_CODE_CONV) tmp_list = &m_flag_convention;
    else /* KW_FLAG_OTHER */ tmp_list = &m_flag_other;

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
        *stream << endl << endl;
    }
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

void initComboType(QComboBox* combo)
{
    combo->addItem(LABEL_C);
    combo->addItem(LABEL_CXX);
    combo->addItem(LABEL_LIBC);
    combo->addItem(LABEL_LIBCXX);
    combo->addItem(LABEL_SHAREDC);
    combo->addItem(LABEL_SHAREDCXX);
}
