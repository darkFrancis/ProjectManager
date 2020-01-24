/**
 * @file context.hpp
 * @brief Description de la classe Context
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef CONTEXT_HPP
#define CONTEXT_HPP

    #include <QString>
    #include <QStringList>
    #include <QTextStream>

    #define INDENT_SPACES "    "
    #define DESC_WIDTH 80

    #define KW_PROJECT_NAME     QString("PROJECT_NAME")
    #define KW_PROJECT_TYPE     QString("PROJECT_TYPE")
    #define KW_PROJECT_VESRION  QString("PROJECT_VERSION")
    #define KW_PROJECT_DESC     QString("PROJECT_DESCRIPTION")
    #define KW_AUTHOR           QString("AUTHOR")
    #define KW_GIT_PATH         QString("GIT_PATH")
    #define KW_DOXYFILE         QString("DOXYFILE")
    #define KW_SOURCES          QString("SOURCES")
    #define KW_HEADERS          QString("HEADERS")
    #define KW_RESSOURCES       QString("RESSOURCES")

    #define KW_FLAG_OVERALL      QString("FLAG_OVERALL")
    #define KW_FLAG_LANGUAGE_C   QString("FLAG_C")
    #define KW_FLAG_LANGUAGE_CXX QString("FLAG_CXX")
    #define KW_FLAG_DIAGNOSTIC   QString("FLAG_DIAG")
    #define KW_FLAG_WARNINGS     QString("FLAG_WARN")
    #define KW_FLAG_DEBUG        QString("FLAG_DEBUG")
    #define KW_FLAG_OPTI         QString("FLAG_OPT")
    #define KW_FLAG_INSTRU       QString("FLAG_INST")
    #define KW_FLAG_PREPROCESSOR QString("FLAG_PREPROCESS")
    #define KW_FLAG_ASSEMBLER    QString("FLAG_ASSEMBLER")
    #define KW_FLAG_LINKER       QString("FLAG_LINKER")
    #define KW_FLAG_DIRS         QString("FLAG_DIRS")
    #define KW_FLAG_CODE_CONV    QString("FLAG_CONVENTION")
    #define KW_FLAG_OTHER        QString("FLAG_OTHER")

    #define TYPE_C              QString("c")
    #define TYPE_CXX            QString("cxx")
    #define TYPE_LIBC           QString("libc")
    #define TYPE_LIBCXX         QString("libcxx")
    #define TYPE_SHAREDC        QString("sharedc")
    #define TYPE_SHAREDCXX      QString("sharedcxx")

    class Context
    {
        public:
            static Context* Instance();
            void loadProject();
            void reloadProject(){loadProject();}
            void save();
            void close(){m_open = false;}
            // Set
            void setLastSearch(QString last_search){m_last_search = last_search;}
            void setProjectName(QString name){m_project_name = name;}
            void setProjectFile(QString file){m_project_file = file;}
            void setProjectType(QString type){m_project_type = type;}
            void setProjectVersion(QString version){m_project_version = version;}
            void setProjectDescription(QString description){m_project_desc = description;}
            void setProjectAuthor(QString author){m_author = author;}
            void setSources(QStringList sources){m_sources = sources;}
            void setHeaders(QStringList headers){m_headers = headers;}
            void setRessources(QStringList ressources){m_ressources = ressources;}
            void setDoxyfile(QString doxyfile){m_doxyfile = doxyfile;}
            void setGitPath(QString path){m_git_path = path;}
            void setFlagOverall(QStringList flag){m_flag_overall = flag;}
            void setFlagC(QStringList flag){m_flag_c = flag;}
            void setFlagCxx(QStringList flag){m_flag_cxx = flag;}
            void setFlagDiag(QStringList flag){m_flag_diag = flag;}
            void setFlagWarn(QStringList flag){m_flag_warn = flag;}
            void setFlagDebug(QStringList flag){m_flag_debug = flag;}
            void setFlagOpt(QStringList flag){m_flag_opt = flag;}
            void setFlagInst(QStringList flag){m_flag_inst = flag;}
            void setFlagPreprocess(QStringList flag){m_flag_preprocess = flag;}
            void setFlagAssembler(QStringList flag){m_flag_assembler = flag;}
            void setFlagLinker(QStringList flag){m_flag_linker = flag;}
            void setFlagDirs(QStringList flag){m_flag_dirs = flag;}
            void setFlagConvention(QStringList flag){m_flag_convention = flag;}
            void setFlagOther(QStringList flag){m_flag_other = flag;}
            // Get
            bool isOpen(){return m_open;}
            QString lastSearch(){return m_last_search;}
            QString projectName(){return m_project_name;}
            QString projectFile(){return m_project_file;}
            QString projectType(){return m_project_type;}
            QString projectVersion(){return m_project_version;}
            QString projectDescription(){return m_project_desc;}
            QString projectAuthor(){return m_author;}
            QStringList sources(){return m_sources;}
            QStringList headers(){return m_headers;}
            QStringList ressources(){return m_ressources;}
            QString doxyfile(){return m_doxyfile;}
            QString gitPath(){return m_git_path;}
            QStringList flagOverall(){return m_flag_overall;}
            QStringList flagC(){return m_flag_c;}
            QStringList flagCxx(){return m_flag_cxx;}
            QStringList flagDiag(){return m_flag_diag;}
            QStringList flagWarn(){return m_flag_warn;}
            QStringList flagDebug(){return m_flag_debug;}
            QStringList flagOpt(){return m_flag_opt;}
            QStringList flagInst(){return m_flag_inst;}
            QStringList flagPreprocess(){return m_flag_preprocess;}
            QStringList flagAssembler(){return m_flag_assembler;}
            QStringList flagLinker(){return m_flag_linker;}
            QStringList flagDirs(){return m_flag_dirs;}
            QStringList flagConvention(){return m_flag_convention;}
            QStringList flagOther(){return m_flag_other;}

        private:
            Context();
            static Context* m_instance;
            bool m_open;
            // Save functions
            QString indent();
            void save_description(QTextStream* stream);
            void save_sources(QString kw, QTextStream* stream);
            void save_flags(QString kw, QTextStream* stream);
            // Last
            QString m_last_search;
            // Files
            QString m_project_file;
            QString m_doxyfile;
            QString m_git_path;
            // Project
            QString m_project_name;
            QString m_project_type;
            QString m_project_version;
            QString m_project_desc;
            QString m_author;
            // Sources
            QStringList m_sources;
            QStringList m_headers;
            QStringList m_ressources;
            // Compiler
            QStringList m_flag_overall;
            QStringList m_flag_c;
            QStringList m_flag_cxx;
            QStringList m_flag_diag;
            QStringList m_flag_warn;
            QStringList m_flag_debug;
            QStringList m_flag_opt;
            QStringList m_flag_inst;
            QStringList m_flag_preprocess;
            QStringList m_flag_assembler;
            QStringList m_flag_linker;
            QStringList m_flag_dirs;
            QStringList m_flag_convention;
            QStringList m_flag_other;
    };

    QString relativePath(QString absolute_path, QString ref_dir);
    QString absolutePath(QString relative_path, QString ref_dir);

#endif // CONTEXT_HPP
