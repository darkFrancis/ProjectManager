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
    #define KW_DOXYFILE         QString("DOXYFILE")/**< Flag du fichier Doxygen projet */
    #define KW_SOURCES          QString("SOURCES")/**< Flag des sources du projet */
    #define KW_HEADERS          QString("HEADERS")/**< Flag des headers du projet */
    #define KW_RESSOURCES       QString("RESSOURCES")/**< Flag des ressources du projet */

    #define KW_DEFINES          QString("DEFINES")/**< Flag des defines du projet */
    #define KW_INCLUDEPATH      QString("INCLUDEPATH")/**< Flag des chemin à inclure au projet */
    #define KW_LINKS            QString("LIBS")/**< Flag des librairies à lier au projet */
    #define KW_COMPILER_FLAGS   QString("COMPILER_FLAGS")/**< Flag des options de compilation */
    #define KW_CMD_PRE_BUILD    QString("PRE_BUILD")/**< Flag des commandes à exécuter avant le build */
    #define KW_CMD_POST_BUILD   QString("POST_BUILD")/**< Flag des commandes à exécuter après le build */
    #define KW_CMD_EXTRA_CLEAN  QString("EXTRA_CLEAN")/**< Flag des commandes à exécuter après le nettoyage des fichiers objets */

    #define KW_FLAG_OVERALL      QString("FLAG_OVERALL")/**< @deprecated Flag des options générales du compilateur */
    #define KW_FLAG_LANGUAGE_C   QString("FLAG_C")/**< @deprecated Flag des options de langage C du compilateur */
    #define KW_FLAG_LANGUAGE_CXX QString("FLAG_CXX")/**< @deprecated Flag des options de langage C++ du compilateur */
    #define KW_FLAG_DIAGNOSTIC   QString("FLAG_DIAG")/**< @deprecated Flag des options de diagnostique du compilateur */
    #define KW_FLAG_WARNINGS     QString("FLAG_WARN")/**< @deprecated Flag des options de warnings du compilateur */
    #define KW_FLAG_DEBUG        QString("FLAG_DEBUG")/**< @deprecated Flag des options de debug du compilateur */
    #define KW_FLAG_OPTI         QString("FLAG_OPT")/**< @deprecated Flag des options d'optimisation du compilateur */
    #define KW_FLAG_INSTRU       QString("FLAG_INST")/**< @deprecated Flag des options d'instrumentation du compilateur */
    #define KW_FLAG_PREPROCESSOR QString("FLAG_PREPROCESS")/**< @deprecated Flag des options de préprocesseur du compilateur */
    #define KW_FLAG_ASSEMBLER    QString("FLAG_ASSEMBLER")/**< @deprecated Flag des options d'assembleur du compilateur */
    #define KW_FLAG_LINKER       QString("FLAG_LINKER")/**< @deprecated Flag des options de linker du compilateur */
    #define KW_FLAG_DIRS         QString("FLAG_DIRS")/**< @deprecated Flag des options des dossiers du compilateur */
    #define KW_FLAG_CODE_CONV    QString("FLAG_CONVENTION")/**< @deprecated Flag des options de convention de code du compilateur */
    #define KW_FLAG_OTHER        QString("FLAG_OTHER")/**< @deprecated Flag des autres options du compilateur */
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
     * Cette classe permet aussi de lire les fichiers projets pour en extraire les informations.@n
     * Voir @ref CONTEXT_GET, @ref CONTEXT_SET.
     * @n Header : context.hpp.
     */
    class Context
    {
        public:
            static Context* Instance();
            void loadProject();
            void reloadProject(){loadProject();}/**< Recharge le projet avec la fonction Context::loadProject */
            void save();
            void close(){m_open = false;}/**< Passe la variable Context::m_open à @b false pour signifier que le projet est fermé et enregistré */
            // Set
            /** @addtogroup CONTEXT_SET
             * @{ */
            void setLastSearch(QString last_search){m_last_search = last_search;}/**< SET : Context::m_last_search */
            void setProjectName(QString name){m_project_name = name;}/**< SET : Context::m_project_name */
            void setProjectFile(QString file){m_project_file = file;}/**< SET : Context::m_project_file */
            void setProjectType(QString type){m_project_type = type;}/**< SET : Context::m_project_type */
            void setProjectVersion(QString version){m_project_version = version;}/**< SET : Context::m_project_version */
            void setProjectDescription(QString description){m_project_desc = description;}/**< SET : Context::m_project_desc */
            void setProjectAuthor(QString author){m_author = author;}/**< SET : Context::m_author */
            void setBuildDir(QString dir){m_build_dir = dir;}/**< SET : Context::m_build_dir */
            void setOutput(QString dir){m_output = dir;}/**< SET : Context::m_output */
            void setSources(QStringList sources){m_sources = sources;}/**< SET : Context::m_sources */
            void setHeaders(QStringList headers){m_headers = headers;}/**< SET : Context::m_headers */
            void setRessources(QStringList ressources){m_ressources = ressources;}/**< SET : Context::m_ressources */
            void setDoxyfile(QString doxyfile){m_doxyfile = doxyfile;}/**< SET : Context::m_doxyfile */
            void setDefines(QStringList defines){m_defines = defines;}/**< SET : Context::m_defines */
            void setIncludePath(QStringList include_paths){m_include_path = include_paths;}/**< SET : Context::m_include_path */
            void setLibs(QStringList libs){m_lib_link = libs;}/**< SET : Context::m_lib_link */
            void setCompilerFlags(QStringList flags){m_compiler_flags = flags;}/**< SET : Context::m_compiler_flags */
            void setCmdPreBuild(QStringList cmds){m_cmd_pre_build = cmds;}/**< SET : Context::m_cmd_pre_build */
            void setCmdPostBuild(QStringList cmds){m_cmd_post_build = cmds;}/**< SET : Context::m_cmd_post_build */
            void setCmdExtraClean(QStringList cmds){m_cmd_extra_clean = cmds;}/**< SET : Context::m_cmd_extra_clean */
            /** @} */
            // Get
            /** @addtogroup CONTEXT_GET
             * @{ */
            bool isOpen(){return m_open;}/**< GET : Context::m_open */
            QString lastSearch(){return m_last_search;}/**< GET : Context::m_last_search */
            QString projectName(){return m_project_name;}/**< GET : Context::m_project_name */
            QString projectFile(){return m_project_file;}/**< GET : Context::m_project_file */
            QString projectType(){return m_project_type;}/**< GET : Context::m_project_type */
            QString projectVersion(){return m_project_version;}/**< GET : Context::m_project_version */
            QString projectDescription(){return m_project_desc;}/**< GET : Context::m_project_desc */
            QString projectAuthor(){return m_author;}/**< GET : Context::m_author */
            QString buildDir(){return m_build_dir;}/**< GET : Context::m_build_dir */
            QString output(){return m_output;}/**< GET : Context::m_output */
            QStringList sources(){return m_sources;}/**< GET : Context::m_sources */
            QStringList headers(){return m_headers;}/**< GET : Context::m_headers */
            QStringList ressources(){return m_ressources;}/**< GET : Context::m_ressources */
            QString doxyfile(){return m_doxyfile;}/**< GET : Context::m_doxyfile */
            QStringList defines(){return m_defines;}/**< GET : Context::m_defines */
            QStringList includePath(){return m_include_path;}/**< GET : Context::m_include_path */
            QStringList libs(){return m_lib_link;}/**< GET : Context::m_lib_link */
            QStringList compilerFlags(){return m_compiler_flags;}/**< GET : Context::m_compiler_flags */
            QStringList cmdPreBuild(){return m_cmd_pre_build;}/**< GET : Context::m_cmd_pre_build */
            QStringList cmdPostBuild(){return m_cmd_post_build;}/**< GET : Context::m_cmd_post_build */
            QStringList cmdExtraClean(){return m_cmd_extra_clean;}/**< GET : Context::m_cmd_extra_clean */
            /** @} */

        private:
            Context();
            static Context* m_instance;/**< Pointeur vers l'instance de la classe Context */
            bool m_open;/**< Booléen d'ouverture de projet */
            // Save functions
            void save_description(QTextStream* stream);
            void save_sources(QString kw, QTextStream* stream);
            void save_flags(QString kw, QTextStream* stream);
            void save_cmd(QString kw, QTextStream* stream);
            // Last
            QString m_last_search;/**< Dossier de la dernière recherche effectuée */
            // Files
            QString m_project_file;/**< Chemin vers le fichier du projet */
            QString m_doxyfile;/**< Chemin vers le fichier Doxyfile */
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
            QStringList m_defines;/**< Liste des defines définis lors de la compilation */
            QStringList m_include_path;/**< Liste des chemins à inclure lors de la compilation */
            QStringList m_lib_link;/**< Liste des librairies à lier lors de la compilation */
            QStringList m_compiler_flags;/**< Liste des option de compilation */
            QStringList m_cmd_pre_build;/**< Liste des commandes à exécuter avant le build */
            QStringList m_cmd_post_build;/**< Liste des commandes à exécuter après le build */
            QStringList m_cmd_extra_clean;/**< Liste des commandes à exécuter après un nettoyage des fichier objet */
    };

    QString relativePath(QString absolute_path, QString ref_dir);
    QString absolutePath(QString relative_path, QString ref_dir);
    QString type2label(QString type);
    QString label2type(QString label);
    void initComboType(QComboBox* combo);
    void trimList(QStringList* list);

#endif // CONTEXT_HPP
