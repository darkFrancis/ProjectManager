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

        private:
            Context();
            static Context* m_instance;
            bool m_open;
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
            QStringList m_sources;
            QStringList m_headers;
            QStringList m_ressources;
    };

    QString relativePath(QString absolute_path, QString ref_dir);
    QString absolutePath(QString relative_path, QString ref_dir);

#endif // CONTEXT_HPP
