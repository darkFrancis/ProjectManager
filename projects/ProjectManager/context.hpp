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
    #include <QComboBox>

    #define INDENT_SPACES "    "/**< Espaces pour les indentations (= 4 espaces) */
    #define DESC_WIDTH 80/**< Nombre de caractères maximum par ligne de description */

    /** @addtogroup PROJECT_FLAGS
      * @{ */
    #define KW_PROJECT_NAME     QString("PROJECT_NAME")/**< Flag du nom de projet */
    #define KW_PROJECT_TYPE     QString("PROJECT_TYPE")/**< Flag du type de projet */
    #define KW_PROJECT_VESRION  QString("PROJECT_VERSION")/**< Flag de version du projet */
    #define KW_PROJECT_DESC     QString("PROJECT_DESCRIPTION")/**< Flag de description du projet */
    #define KW_AUTHOR           QString("AUTHOR")/**< Flag de l'auteur du projet */
    #define KW_BUILD_DIR        QString("BUILD_DIR")/**< Flag du répertoire de compilation du projet */
    #define KW_OUTPUT           QString("OUTPUT")/**< Flag du répertoire de sortie du projet */
    #define KW_GIT_PATH         QString("GIT_PATH")/**< Flag du répertoire GIT du projet */
    #define KW_DOXYFILE         QString("DOXYFILE")/**< Flag du fichier Doxygen projet */
    #define KW_SOURCES          QString("SOURCES")/**< Flag des sources du projet */
    #define KW_HEADERS          QString("HEADERS")/**< Flag des headers du projet */
    #define KW_RESSOURCES       QString("RESSOURCES")/**< Flag des ressources du projet */

    #define KW_FLAG_OVERALL      QString("FLAG_OVERALL")/**< Flag des options générales du compilateur */
    #define KW_FLAG_LANGUAGE_C   QString("FLAG_C")/**< Flag des options de langage C du compilateur */
    #define KW_FLAG_LANGUAGE_CXX QString("FLAG_CXX")/**< Flag des options de langage C++ du compilateur */
    #define KW_FLAG_DIAGNOSTIC   QString("FLAG_DIAG")/**< Flag des options de diagnostique du compilateur */
    #define KW_FLAG_WARNINGS     QString("FLAG_WARN")/**< Flag des options de warnings du compilateur */
    #define KW_FLAG_DEBUG        QString("FLAG_DEBUG")/**< Flag des options de debug du compilateur */
    #define KW_FLAG_OPTI         QString("FLAG_OPT")/**< Flag des options d'optimisation du compilateur */
    #define KW_FLAG_INSTRU       QString("FLAG_INST")/**< Flag des options d'instrumentation du compilateur */
    #define KW_FLAG_PREPROCESSOR QString("FLAG_PREPROCESS")/**< Flag des options de préprocesseur du compilateur */
    #define KW_FLAG_ASSEMBLER    QString("FLAG_ASSEMBLER")/**< Flag des options d'assembleur du compilateur */
    #define KW_FLAG_LINKER       QString("FLAG_LINKER")/**< Flag des options de linker du compilateur */
    #define KW_FLAG_DIRS         QString("FLAG_DIRS")/**< Flag des options des dossiers du compilateur */
    #define KW_FLAG_CODE_CONV    QString("FLAG_CONVENTION")/**< Flag des options de convention de code du compilateur */
    #define KW_FLAG_OTHER        QString("FLAG_OTHER")/**< Flag des autres options du compilateur */
    /** @} */

    /** @addtogroup PROJECT_TYPE
      * @{ */
    #define TYPE_C              QString("c")/**< Format pour les applications C */
    #define TYPE_CXX            QString("cxx")/**< Format pour les applications C++ */
    #define TYPE_LIBC           QString("libc")/**< Format pour les librairies statiques C */
    #define TYPE_LIBCXX         QString("libcxx")/**< Format pour les librairies statiques C++ */
    #define TYPE_SHAREDC        QString("sharedc")/**< Format pour les librairies dynamiques C */
    #define TYPE_SHAREDCXX      QString("sharedcxx")/**< Format pour les librairies dynamiques C++ */
    #define LABEL_C             QString("Application C")/**< Label pour les applications C */
    #define LABEL_CXX           QString("Application C++")/**< Label pour les applications C++ */
    #define LABEL_LIBC          QString("Librairie Statique C")/**< Label pour les librairies statiques C */
    #define LABEL_LIBCXX        QString("Librairie Statique C++")/**< Label pour les librairies statiques C++ */
    #define LABEL_SHAREDC       QString("Librairie Dynamique C")/**< Label pour les librairies dynamiques C */
    #define LABEL_SHAREDCXX     QString("Librairie Dynamique C++")/**< Label pour les librairies dynamiques C++ */
    /** @} */

    /**
     * @class Context
     * @brief La classe Context permet de stocker les informations en cours.
     *
     * Cette classe est un singleton.
     * Les informations contenues sont accessibles par un jeu de fonctions get/set.
     * Cette classe permet aussi de lire les fichiers projets pour en extraire les informations.
     * @n Header : context.hpp
     */
    class Context
    {
        public:
            static Context* Instance();
            void loadProject();
            void reloadProject(){loadProject();}
            void save();
            void close(){m_open = false;}
            // Set
            /** @addtogroup CONTEXT_SET
             * @{ */
            void setLastSearch(QString last_search){m_last_search = last_search;}/**< GET : Context::m_last_search */
            void setProjectName(QString name){m_project_name = name;}
            void setProjectFile(QString file){m_project_file = file;}
            void setProjectType(QString type){m_project_type = type;}
            void setProjectVersion(QString version){m_project_version = version;}
            void setProjectDescription(QString description){m_project_desc = description;}
            void setProjectAuthor(QString author){m_author = author;}
            void setBuildDir(QString dir){m_build_dir = dir;}
            void setOutput(QString dir){m_output = dir;}
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
            /** @} */
            // Get
            /** @addtogroup CONTEXT_GET
             * @{ */
            bool isOpen(){return m_open;}/**< GET : Context::m_open */
            QString lastSearch(){return m_last_search;}
            QString projectName(){return m_project_name;}
            QString projectFile(){return m_project_file;}
            QString projectType(){return m_project_type;}
            QString projectVersion(){return m_project_version;}
            QString projectDescription(){return m_project_desc;}
            QString projectAuthor(){return m_author;}
            QString buildDir(){return m_build_dir;}
            QString output(){return m_output;}
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
            /** @} */

        private:
            Context();
            static Context* m_instance;/**< Pointeur vers l'instance de la classe Context */
            bool m_open;/**< Booléen d'ouverture de projet */
            // Save functions
            QString indent();
            void save_description(QTextStream* stream);
            void save_sources(QString kw, QTextStream* stream);
            void save_flags(QString kw, QTextStream* stream);
            // Last
            QString m_last_search;/**< Dossier de la dernière recherche effectuée */
            // Files
            QString m_project_file;/**< Chemin vers le fichier du projet */
            QString m_doxyfile;/**< Chemin vers le fichier Doxyfile */
            QString m_git_path;/**< Chemin vers le dossier contenant .git */
            // Project
            QString m_project_name;/**< Nom du projet */
            QString m_project_type;/**< Type de projet */
            QString m_project_version;/**< Version du projet */
            QString m_project_desc;/**< Description du projet */
            QString m_author;/**< Auteur du projet */
            QString m_build_dir;/**< Dossier de build pour le compilateur */
            QString m_output;/**< Dossier de sortie du compilateur */
            // Sources
            QStringList m_sources;/**< Liste des sources */
            QStringList m_headers;/**< Liste des headers */
            QStringList m_ressources;/**< Listes des fichiers ressources (ni sources, ni headers) */
            // Compiler
            QStringList m_flag_overall;/**< Liste des flags généraux du compilateur */
            QStringList m_flag_c;/**< Liste des flags C du compilateur */
            QStringList m_flag_cxx;/**< Liste des flags C++ du compilateur */
            QStringList m_flag_diag;/**< Liste des flags de diagnostique du compilateur */
            QStringList m_flag_warn;/**< Liste des flags de warnings du compilateur */
            QStringList m_flag_debug;/**< Liste des flags de debug du compilateur */
            QStringList m_flag_opt;/**< Liste des flags d'optimisation du compilateur */
            QStringList m_flag_inst;/**< Liste des flags d'instrumentation du compilateur */
            QStringList m_flag_preprocess;/**< Liste des flags du préprocesseur du compilateur */
            QStringList m_flag_assembler;/**< Liste des flags de l'assembleur du compilateur */
            QStringList m_flag_linker;/**< Liste des flags du linker du compilateur */
            QStringList m_flag_dirs;/**< Liste des flags des répertoires du compilateur */
            QStringList m_flag_convention;/**< Liste des flags de convention de code du compilateur */
            QStringList m_flag_other;/**< Liste des autres flags du compilateur */
    };

    QString relativePath(QString absolute_path, QString ref_dir);
    QString absolutePath(QString relative_path, QString ref_dir);
    QString type2label(QString type);
    QString label2type(QString label);
    void initComboType(QComboBox* combo);
    void trimList(QStringList* list);

#endif // CONTEXT_HPP
