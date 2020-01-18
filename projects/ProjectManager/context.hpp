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

    #define KW_PROJECT_NAME QString("PROJECT_NAME")
    #define KW_PROJECT_TYPE QString("PROJECT_TYPE")
    #define KW_GIT_PATH     QString("GIT_PATH")
    #define KW_DOXYFILE     QString("DOXYFILE")
    #define KW_SOURCES      QString("SOURCES")
    #define KW_HEADERS      QString("HEADERS")
    #define KW_RESSOURCES   QString("RESSOURCES")

    class Context
    {
        public:
            static Context* Instance();
            void setProject(QString project_file);
            void setLastSearch(QString last_search);
            void loadProject();
            void reloadProject();
            QString project();
            QString lastSearch();
            QString doxyfile();
            QString gitPath();
            bool isOpen();
            void close();

        private:
            Context();
            static Context* m_instance;
            // Files
            QString m_project_file;
            bool m_open;
            QString m_doxyfile;
            QString m_git_path;
            // Project
            QString m_project_name;
            QString m_project_type;
            QStringList m_sources;
            QStringList m_headers;
            QStringList m_ressources;
            // Last
            QString m_last_search;
    };

#endif // CONTEXT_HPP
